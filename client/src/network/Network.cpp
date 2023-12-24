//
// Created by Xavier VINCENT on 14/12/2023.
//

#include "network/Network.hpp"

Client::Network::Network(std::string ip, std::string port)
  : socket(io)
{
  boost::asio::ip::udp::resolver resolver(this->io);
  this->remoteEndpoint =
    *resolver.resolve(boost::asio::ip::udp::v4(), ip, port).begin();
  this->socket.open(boost::asio::ip::udp::v4());
  this->clientId = -1;
  this->startReceive();
  this->io.run();
}

Client::Network::~Network()
{
  this->socket.close();

  if (this->receiveThread.joinable())
    this->receiveThread.join();
}

void Client::Network::send(boost::asio::const_buffer const &buffer)
{
  this->socket.send_to(buffer, this->remoteEndpoint);
}

void Client::Network::sendMessage(
  std::string const &command,
  char const data[],
  int dataSize)
{
  MessageType type = MessageType::Message;

  MessageHeader header;
  header.clientId = this->clientId;
  strcpy(header.command, command.c_str());
  header.dataLength = dataSize;

  size_t totalSize = sizeof(type) + sizeof(header) + dataSize;
  std::vector<char> messageBuffer(totalSize);

  memcpy(messageBuffer.data(), &type, sizeof(type));
  memcpy(messageBuffer.data() + sizeof(type), &header, sizeof(header));
  if (data != nullptr)
    memcpy(
      messageBuffer.data() + sizeof(type) + sizeof(header),
      data,
      dataSize);

  this->send(boost::asio::buffer(messageBuffer.data(), messageBuffer.size()));
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
    memcpy(
      messageBuffer.data() + sizeof(type) + sizeof(header),
      data,
      dataSize);

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
          &Client::Network::onReceive,
          this,
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));

      this->io.run();
    }
  });
}

void Client::Network::onReceive(
  boost::system::error_code const &error,
  std::size_t bytesTransferred)
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
  int const width = 20;

  std::stringstream ss;
  ss << "\n" << CYAN << std::string(60, '=') << RESET << "\n";
  ss << GREEN << "Server response: " << std::this_thread::get_id() << RESET
     << "\n";
  ss << CYAN << std::string(60, '-') << RESET << "\n";
  ss << YELLOW << std::left << std::setw(width) << "Command:" << RESET
     << response->header.command << "\n";
  ss << YELLOW << std::left << std::setw(width) << "Data Length:" << RESET
     << response->header.dataLength << "\n";
  ss << YELLOW << std::left << std::setw(width) << "Client ID:" << RESET
     << response->header.clientId << "\n";
  ss << YELLOW << std::left << std::setw(width) << "Status:" << RESET
     << response->header.status << "\n";
  ss << YELLOW << std::left << std::setw(width) << "Status Message:" << RESET
     << response->header.statusMessage << "\n";
  ss << CYAN << std::string(60, '-') << RESET << "\n";
  std::cout << ss.str();

  switch (response->header.status) {
    case RES_SUCCESS:
      break;
    case RES_BAD_REQUEST:
    case RES_UNAUTHORIZED:
    case RES_NOT_FOUND:
    case RES_INTERNAL_ERROR:
      throw std::runtime_error(response->header.statusMessage);
    default:
      throw std::runtime_error(
        "Invalid response status: " + std::to_string(response->header.status));
  }

  if (!strcmp(response->header.command, CONNECT_TO_SERVER_COMMAND))
    return this->onConnectToServerResponse(response);
  else if (!strcmp(response->header.command, UPDATE_NAME_COMMAND))
    return this->onUpdateNameResponse(response);
  else if (!strcmp(response->header.command, JOIN_ROOM_COMMAND))
    return this->onJoinRoomResponse(response);
  else if (!strcmp(response->header.command, START_GAME_COMMAND))
    return this->onStartGameResponse(response);
  else if (!strcmp(response->header.command, INPUT_COMMAND))
    return this->onSendKeyResponse(response);
  else
    throw std::runtime_error("Invalid response command");

  this->startReceive();
}

void Client::Network::onServerMessage(Message *message)
{
  int const width = 20;

  std::stringstream ss;
  ss << "\n" << CYAN << std::string(60, '=') << RESET << "\n";
  ss << GREEN << "Worker Thread: " << std::this_thread::get_id() << RESET
     << "\n";
  ss << CYAN << std::string(60, '-') << RESET << "\n";
  ss << YELLOW << std::left << std::setw(width) << "Command:" << RESET
     << message->header.command << "\n";
  ss << YELLOW << std::left << std::setw(width) << "Data Length:" << RESET
     << message->header.dataLength << "\n";
  ss << YELLOW << std::left << std::setw(width) << "Client ID:" << RESET
     << message->header.clientId << "\n";
  ss << CYAN << std::string(60, '-') << RESET << "\n";
  std::cout << ss.str();

  if (!strcmp(message->header.command, SERVER_COMMAND_CHECK_CONNECTION))
    return this->onCheckConnectionMessage(message);
  else
    throw std::runtime_error("Invalid message command");

  this->startReceive();
}

/* --------------------------------------------------- */
/* ---------------- Connect to server ---------------- */
/* --------------------------------------------------- */
void Client::Network::connectToServer()
{
  this->sendMessage(CONNECT_TO_SERVER_COMMAND);
}

void Client::Network::onConnectToServerResponse(Response *response)
{
  this->clientId = response->header.clientId;

  std::cout << "Connected to server: " << this->remoteEndpoint << std::endl;
  std::cout << "Client id: " << this->clientId << std::endl << std::endl;
}
/* --------------------------------------------------- */
/* --------------------------------------------------- */
/* --------------------------------------------------- */

/* --------------------------------------------------- */
/* ------------------ Update  Name ------------------- */
/* --------------------------------------------------- */
void Client::Network::updateName(std::string name)
{
  if (name.length() > MAX_NAME_LENGTH)
    throw std::runtime_error("The name is too long");

  UpdateNameData data;
  strcpy(data.name, name.c_str());
  char dataBuffer[sizeof(data)];
  memcpy(dataBuffer, &data, sizeof(data));

  this->sendMessage(UPDATE_NAME_COMMAND, dataBuffer, sizeof(data));
}

void Client::Network::onUpdateNameResponse(Response *response)
{
  UpdateNameData *data = (UpdateNameData *)response->data;
  this->name = data->name;

  std::cout << "Name successfully updated: " << data->name << std::endl;
}
/* --------------------------------------------------- */
/* --------------------------------------------------- */
/* --------------------------------------------------- */

/* --------------------------------------------------- */
/* ------------------- Join  Room -------------------- */
/* --------------------------------------------------- */
void Client::Network::joinRoom(int roomId)
{
  JoinRoomData data;
  data.roomId = roomId;
  char dataBuffer[sizeof(data)];
  memcpy(dataBuffer, &data, sizeof(data));

  this->sendMessage(JOIN_ROOM_COMMAND, dataBuffer, sizeof(data));
}

void Client::Network::onJoinRoomResponse(Response *response)
{
  JoinRoomData *data = (JoinRoomData *)response->data;
  this->roomId = data->roomId;

  std::cout << "Joined room: " << this->roomId << std::endl;
}
/* --------------------------------------------------- */
/* --------------------------------------------------- */
/* --------------------------------------------------- */

/* --------------------------------------------------- */
/* -------------------- Send Key --------------------- */
/* --------------------------------------------------- */
void Client::Network::sendKey(std::string key)
{
  InputData data;
  strcpy(data.key, key.c_str());
  char dataBuffer[sizeof(data)];
  memcpy(dataBuffer, &data, sizeof(data));

  this->sendMessage(INPUT_COMMAND, dataBuffer, sizeof(data));
}

void Client::Network::onSendKeyResponse(Response *response)
{
  InputData *data = (InputData *)response->data;

  std::cout << "Key successfully received: " << data->key << std::endl;
}
/* --------------------------------------------------- */
/* --------------------------------------------------- */
/* --------------------------------------------------- */

/* --------------------------------------------------- */
/* ------------------ Check Connection --------------- */
/* --------------------------------------------------- */
void Client::Network::startGame(int roomId)
{
  StartGameData data;
  data.roomId = roomId;
  char dataBuffer[sizeof(data)];
  memcpy(dataBuffer, &data, sizeof(data));

  this->sendMessage(START_GAME_COMMAND, dataBuffer, sizeof(data));
}

void Client::Network::onStartGameResponse(Response *response)
{
  StartGameData *data = (StartGameData *)response->data;

  std::cout << "Game started in room: " << data->roomId << std::endl
            << std::endl;
}
/* --------------------------------------------------- */
/* --------------------------------------------------- */
/* --------------------------------------------------- */

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

void Client::Network::setEndpoint(std::string &ip, std::string &port)
{
  boost::asio::ip::udp::resolver resolver(io);
  this->remoteEndpoint =
    *resolver.resolve(boost::asio::ip::udp::v4(), ip, port).begin();
  this->socket.open(boost::asio::ip::udp::v4());
  this->clientId = -1;
}
