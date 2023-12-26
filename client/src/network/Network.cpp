//
// Created by Xavier VINCENT on 14/12/2023.
//

#include "RTypeClient.hpp"

Client::Network::Network(std::string ip, std::string port)
  : socket(io)
{
  boost::asio::ip::udp::resolver resolver(this->io);
  this->remoteEndpoint = *resolver.resolve(boost::asio::ip::udp::v4(), ip, port).begin();
  this->socket.open(boost::asio::ip::udp::v4());
  this->clientId = -1;
  this->registerCommandHandlers();
  this->startReceive();
  this->io.run();
}

Client::Network::~Network()
{
  this->socket.close();

  if (this->receiveThread.joinable())
    this->receiveThread.join();
}

void Client::Network::registerCommandHandlers()
{
  this->commandHandlers[CONNECT_TO_SERVER_COMMAND] = std::make_shared<ConnectToServerCommandHandler>(*this);
  this->commandHandlers[UPDATE_NAME_COMMAND] = std::make_shared<UpdateNameCommandHandler>(*this);
  this->commandHandlers[JOIN_ROOM_COMMAND] = std::make_shared<JoinRoomCommandHandler>(*this);
  this->commandHandlers[INPUT_COMMAND] = std::make_shared<InputCommandHandler>(*this);
  this->commandHandlers[START_GAME_COMMAND] = std::make_shared<StartGameCommandHandler>(*this);
}

std::shared_ptr<Client::ICommandHandler> Client::Network::getCommandHandler(const std::string &name)
{
  auto it = this->commandHandlers.find(name);
  if (it != this->commandHandlers.end()) {
    return it->second;
  }
  throw std::runtime_error("Invalid command name");
}

void Client::Network::send(boost::asio::const_buffer const &buffer)
{
  this->socket.send_to(buffer, this->remoteEndpoint);
}

void Client::Network::sendMessage(std::string const &command, char const data[], int dataSize)
{
  int commandId = this->nextCommandId++;
  this->commandTrackers[commandId] = std::make_shared<CommandTracker>(command);

  MessageType type = MessageType::Message;

  MessageHeader header;
  header.clientId = this->clientId;
  strcpy(header.command, command.c_str());
  header.dataLength = dataSize;
  header.commandId = commandId;

  size_t totalSize = sizeof(type) + sizeof(header) + dataSize;
  std::vector<char> messageBuffer(totalSize);

  memcpy(messageBuffer.data(), &type, sizeof(type));
  memcpy(messageBuffer.data() + sizeof(type), &header, sizeof(header));
  if (data != nullptr)
    memcpy(messageBuffer.data() + sizeof(type) + sizeof(header), data, dataSize);

  Message *message = (Message *)messageBuffer.data();
  logMessage("Client message", message);

  this->send(boost::asio::buffer(messageBuffer.data(), messageBuffer.size()));

  std::thread([this, commandId, command]() {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    if (!commandTrackers[commandId]->getIsCompleted()) {
      std::cout << "Command " << command << " timed out" << std::endl;
    }
    commandTrackers.erase(commandId);
  }).detach();
}

void Client::Network::sendResponse(
  std::string const &command,
  std::string const &statusMessage,
  char const data[],
  int dataSize,
  int status)
{
  MessageType type = MessageType::Response;

  ResponseHeader header;
  header.clientId = this->clientId;
  strcpy(header.command, command.c_str());
  header.dataLength = dataSize;
  header.status = status;
  strcpy(header.statusMessage, statusMessage.c_str());

  size_t totalSize = sizeof(type) + sizeof(header) + dataSize;
  std::vector<char> messageBuffer(totalSize);

  memcpy(messageBuffer.data(), &type, sizeof(type));
  memcpy(messageBuffer.data() + sizeof(type), &header, sizeof(header));
  if (data != nullptr)
    memcpy(messageBuffer.data() + sizeof(type) + sizeof(header), data, dataSize);

  this->send(boost::asio::buffer(messageBuffer.data(), messageBuffer.size()));
}

void Client::Network::startReceive()
{
  this->receiveThread = std::thread([this]() {
    while (true) {
      this->io.reset();
      this->socket.async_receive_from(
        boost::asio::buffer(this->recvBuffer),
        this->remoteEndpoint,
        boost::bind(
          &Network::onReceive,
          this,
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));

      this->io.run();
    }
  });
}

void Client::Network::onReceive(boost::system::error_code const &error, std::size_t bytesTransferred)
{
  (void)bytesTransferred;
  if (error && error == boost::asio::error::message_size) {
    std::cout << "Error: " << error << std::endl;
    return;
  }

  MessageType *type = (MessageType *)this->recvBuffer.data();

  switch (*type) {
    case MessageType::Response:
      return this->onServerResponse((Response *)this->recvBuffer.data());
    case MessageType::Message:
      return this->onServerMessage((Message *)this->recvBuffer.data());
    default:
      throw std::runtime_error("Invalid message type");
  }
}

void Client::Network::onServerResponse(Response *response)
{
  logResponse("Server response", response);

  switch (response->header.status) {
    case RES_SUCCESS:
      break;
    case RES_BAD_REQUEST:
    case RES_UNAUTHORIZED:
    case RES_NOT_FOUND:
    case RES_INTERNAL_ERROR:
      throw std::runtime_error(response->header.statusMessage);
    default:
      throw std::runtime_error("Invalid response status: " + std::to_string(response->header.status));
  }

  for (auto &handler : this->commandHandlers) {
    if (handler.first == std::string(response->header.command)) {
      int commandId = response->header.commandId;

      if (commandTrackers.find(commandId) != commandTrackers.end()) {
        commandTrackers[commandId]->setIsCompleted(true);
      }

      return handler.second->onResponse(response);
    }
  }

  throw std::runtime_error("Invalid response command");
}

void Client::Network::onServerMessage(Message *message)
{
  logMessage("Server message", message);

  if (!strcmp(message->header.command, SERVER_COMMAND_CHECK_CONNECTION))
    return this->onCheckConnectionMessage(message);
  else
    throw std::runtime_error("Invalid message command");

  this->startReceive();
}

void Client::Network::onCheckConnectionMessage(Message *message)
{
  return this->sendResponse(message->header.command, "OK");
}

void Client::Network::setClientId(int id)
{
  this->clientId = id;
}

int Client::Network::getClientId() const
{
  return this->clientId;
}

void Client::Network::setRoomId(int id)
{
  this->roomId = id;
}

int Client::Network::getRoomId() const
{
  return this->roomId;
}

void Client::Network::setName(std::string name)
{
  this->name = name;
}

std::string Client::Network::getName() const
{
  return this->name;
}

void Client::Network::setRemoteEndpoint(std::string &ip, std::string &port)
{
  boost::asio::ip::udp::resolver resolver(io);
  this->remoteEndpoint = *resolver.resolve(boost::asio::ip::udp::v4(), ip, port).begin();
  this->socket.open(boost::asio::ip::udp::v4());
  this->clientId = -1;
}

boost::asio::ip::udp::endpoint Client::Network::getRemoteEndpoint() const
{
  return this->remoteEndpoint;
}

/* -------------------------------------------------- */
/* --------------------- commands ------------------- */
/* -------------------------------------------------- */
template<typename T, typename Func>
void Client::Network::executeCommand(const std::string &commandName, Func action)
{
  auto command = this->getCommandHandler(commandName);
  auto specificCommandHandler = std::dynamic_pointer_cast<T>(command);

  if (specificCommandHandler == nullptr)
    throw std::runtime_error("Invalid command handler");

  action(specificCommandHandler);
}

void Client::Network::connectToServer()
{
  this->executeCommand<ConnectToServerCommandHandler>(CONNECT_TO_SERVER_COMMAND, [](auto commandHandler) {
    commandHandler->send();
  });
}

void Client::Network::updateName(std::string name)
{
  this->executeCommand<UpdateNameCommandHandler>(UPDATE_NAME_COMMAND, [name](auto commandHandler) {
    commandHandler->setName(name);
    commandHandler->send();
  });
}

void Client::Network::joinRoom(int roomId)
{
  this->executeCommand<JoinRoomCommandHandler>(JOIN_ROOM_COMMAND, [roomId](auto commandHandler) {
    commandHandler->setRoomId(roomId);
    commandHandler->send();
  });
}

void Client::Network::sendKey(std::string key)
{
  this->executeCommand<InputCommandHandler>(INPUT_COMMAND, [key](auto commandHandler) {
    commandHandler->setKey(key);
    commandHandler->send();
  });
}

void Client::Network::startGame(int roomId)
{
  this->executeCommand<StartGameCommandHandler>(START_GAME_COMMAND, [roomId](auto commandHandler) {
    commandHandler->setRoomId(roomId);
    commandHandler->send();
  });
}
