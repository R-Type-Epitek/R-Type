//
// Created by Xavier VINCENT on 12/12/2023.
//

#include "RTypeNetwork.hpp"

Network::UDPServer::UDPServer(boost::asio::io_context &io)
  : socket(io, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), std::stoi(DEFAULT_PORT)))
  , nextClientId(0)
  , clientsConnectionTimer(io)
{
  this->initServer(std::stoi(DEFAULT_PORT));
}

Network::UDPServer::UDPServer(boost::asio::io_context &io, int port)
  : socket(io, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port))
  , nextClientId(0)
  , clientsConnectionTimer(io)
{
  this->initServer(port);
}

Network::UDPServer::~UDPServer()
{
  this->socket.close();
  this->clientsConnectionTimer.cancel();

  for (auto &worker : this->workers) {
    if (worker.joinable()) {
      worker.join();
    }
  }
}

boost::asio::ip::udp::socket &Network::UDPServer::getSocket()
{
  return this->socket;
}

std::vector<Network::Client> &Network::UDPServer::getClients()
{
  return this->clients;
}

std::optional<Network::Client> Network::UDPServer::getClientById(int id)
{
  for (auto &client : this->clients)
    if (client.getId() == id)
      return client;

  return std::nullopt;
}

boost::array<char, 65536> Network::UDPServer::getRecvBuffer() const
{
  return this->recvBuffer;
}

boost::asio::ip::udp::endpoint Network::UDPServer::getRemoteEndpoint() const
{
  return this->remoteEndpoint;
}

std::vector<Network::Room> &Network::UDPServer::getRooms()
{
  return this->rooms;
}

int Network::UDPServer::getNextClientIdAndIncrement()
{
  return this->nextClientId++;
}

void Network::UDPServer::addClient(Network::Client client)
{
  this->clients.push_back(client);
}

void Network::UDPServer::initServer(int port)
{
  spdlog::info("Server listening on port {}", port);
  this->initRooms(NUMBER_OF_ROOMS);
  this->registerCommandHandlers();
  this->startReceive();
  this->startClientTimerCheck();
  this->gameLoop();

  int num_threads = std::thread::hardware_concurrency();

  for (int i = 0; i < num_threads; ++i) {
    workers.emplace_back(&Network::UDPServer::workerFunction, this);
  }
}

void Network::UDPServer::initRooms(int count)
{
  for (int i = 0; i < count; i++) {
    Network::Room room(i, DEFAULT_ROOM_SIZE);

    this->rooms.push_back(room);
  }
  spdlog::info("{} rooms initialized", count);
}

void Network::UDPServer::startReceive()
{
  this->socket.async_receive_from(
    boost::asio::buffer(this->recvBuffer),
    this->remoteEndpoint,
    boost::bind(
      &Network::UDPServer::handleReceive,
      this,
      boost::asio::placeholders::error,
      boost::asio::placeholders::bytes_transferred));
}

void Network::UDPServer::handleReceive(boost::system::error_code const &error, std::size_t bytesTransferred)
{
  if (error && error == boost::asio::error::message_size)
    return spdlog::error("handleReceive: Error: {} ({} bytes)", error.message(), bytesTransferred);

  char *data = this->recvBuffer.data();
  MessageType *type = (MessageType *)data;

  this->updateClientLastMessageTimeFromData(data);

  switch (*type) {
    case MessageType::Response:
      return this->processResponse((Response *)data);
    case MessageType::Message:
      return this->messageQueue.push(
        (TimedMessage) {(Message *)data, std::chrono::high_resolution_clock::now()});
    default:
      throw std::runtime_error("Invalid message type");
  }
}

void Network::UDPServer::updateClientLastMessageTimeFromData(char *data)
{
  Message *message = (Message *)data;

  for (auto &client : this->clients) {
    if (client.getId() == message->header.clientId)
      return client.updateLastMessageTime();
  }
}

void Network::UDPServer::sendToAll(boost::asio::const_buffer const &buffer)
{
  for (auto &client : this->clients)
    this->socket.async_send_to(
      buffer,
      client.getEndpoint(),
      boost::bind(
        &Network::UDPServer::handleSend,
        this,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
}

void Network::UDPServer::sendToAllClientsInRoom(boost::asio::const_buffer const &buffer, int roomId)
{
  if (roomId < 0 || roomId >= static_cast<int>(this->rooms.size()))
    throw std::runtime_error("Invalid room id: " + std::to_string(roomId));
  for (auto &clientId : this->rooms[roomId].getPlayers())
    this->socket.async_send_to(
      buffer,
      this->clients[clientId].getEndpoint(),
      boost::bind(
        &Network::UDPServer::handleSend,
        this,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
}

void Network::UDPServer::sendToAllClientsInRoomInGame(boost::asio::const_buffer const &buffer, int roomId)
{
  if (roomId < 0 || roomId >= static_cast<int>(this->rooms.size()))
    throw std::runtime_error("Invalid room id: " + std::to_string(roomId));
  for (auto &clientId : this->rooms[roomId].getPlayers()) {
    if (!this->clients[clientId].getIsInGame())
      continue;
    this->socket.async_send_to(
      buffer,
      this->clients[clientId].getEndpoint(),
      boost::bind(
        &Network::UDPServer::handleSend,
        this,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
  }
}

void Network::UDPServer::sendToClient(boost::asio::const_buffer const &buffer, int id)
{
  std::vector<char> messageBuffer(buffer.size());
  memcpy(messageBuffer.data(), buffer.data(), buffer.size());

  if (!this->isClientRegistered(id))
    return spdlog::warn("Client {} is not connected", id);
  if (!this->socket.is_open())
    throw std::runtime_error("Socket is not open");
  this->socket.async_send_to(
    buffer,
    this->clients[id].getEndpoint(),
    boost::bind(
      &Network::UDPServer::handleSend,
      this,
      boost::asio::placeholders::error,
      boost::asio::placeholders::bytes_transferred));
}

void Network::UDPServer::handleSend(boost::system::error_code const &error, std::size_t bytesTransferred)
{
  if (error && error == boost::asio::error::message_size)
    return spdlog::error("handleSend: Error: {} ({} bytes)", error.message(), bytesTransferred);
}

void Network::UDPServer::processMessage(TimedMessage timedMessage)
{
  Message *message = timedMessage.message;

  auto it = this->commandHandlers.find(message->header.command);
  if (it != this->commandHandlers.end()) {
    if (!it->second->isAuthorized(message->header.clientId))
      return this->handleInvalidClient(timedMessage);
    std::vector<char> responseBuffer = it->second->handleCommand(message);
    this->sendResponseAndLog(timedMessage, responseBuffer);
  } else {
    return this->handleInvalidCommand(timedMessage);
  }
}

void Network::UDPServer::processResponse(Response *response)
{
  auto clientOpt = this->getClientById(response->header.clientId);
  Client client;
  if (clientOpt.has_value()) {
    client = clientOpt.value();
  } else {
    this->startReceive();
    return spdlog::error("Client not found");
  }

  if (strcmp(response->header.command, SERVER_COMMAND_UPDATE_GAME) != 0)
    logResponse("Client response", response, client);

  if (!strcmp(response->header.command, SERVER_COMMAND_CHECK_CONNECTION))
    client.updateLastMessageTime();

  this->startReceive();
}

void Network::UDPServer::workerFunction()
{
  while (true) {
    TimedMessage timedMessage = this->messageQueue.pop();
    Message *message = timedMessage.message;
    auto clientOpt = this->getClientById(message->header.clientId);
    Client client;
    if (!clientOpt.has_value())
      client = Client();
    else
      client = clientOpt.value();

    logMessage("Client message", message, client);

    this->processMessage(timedMessage);
  }
}

std::vector<char> Network::UDPServer::createMessageBuffer(
  int clientId,
  std::string const &command,
  char const data[],
  int dataSize)
{
  MessageType type = MessageType::Message;

  MessageHeader header;
  header.clientId = clientId;
  strcpy(header.command, command.c_str());
  header.commandId = 0;
  header.dataLength = dataSize;

  size_t totalSize = sizeof(type) + sizeof(header) + dataSize;
  std::vector<char> messageBuffer(totalSize);

  memcpy(messageBuffer.data(), &type, sizeof(type));
  memcpy(messageBuffer.data() + sizeof(type), &header, sizeof(header));
  if (data != nullptr)
    memcpy(messageBuffer.data() + sizeof(type) + sizeof(header), data, dataSize);

  return messageBuffer;
}

std::vector<char> Network::UDPServer::createResponseBuffer(
  int clientId,
  MessageHeader const &messageHeader,
  std::string const &statusMessage,
  char const data[],
  int dataSize,
  int status)
{
  MessageType type = MessageType::Response;

  ResponseHeader header;
  header.clientId = clientId;
  strcpy(header.command, messageHeader.command);
  header.commandId = messageHeader.commandId;
  header.dataLength = dataSize;
  header.status = status;
  strcpy(header.statusMessage, statusMessage.c_str());

  size_t totalSize = sizeof(type) + sizeof(header) + dataSize;
  std::vector<char> messageBuffer(totalSize);

  memcpy(messageBuffer.data(), &type, sizeof(type));
  memcpy(messageBuffer.data() + sizeof(type), &header, sizeof(header));
  if (data != nullptr)
    memcpy(messageBuffer.data() + sizeof(type) + sizeof(header), data, dataSize);

  return messageBuffer;
}

void Network::UDPServer::sendResponseAndLog(TimedMessage timedMessage, std::vector<char> responseBuffer)
{
  Response response = *(Response *)responseBuffer.data();
  auto clientOpt = this->getClientById(response.header.clientId);
  Client client;
  if (clientOpt.has_value())
    client = clientOpt.value();
  else
    return spdlog::error("Client not found");

  logTimedMessage("Server response", timedMessage, response, client);

  this->sendToClient(boost::asio::buffer(responseBuffer.data(), responseBuffer.size()), client.getId());
  this->startReceive();
}

bool Network::UDPServer::isClientRegistered(int clientId)
{
  for (auto const &client : this->clients)
    if (client.getId() == clientId)
      return true;
  return false;
}

void Network::UDPServer::registerCommandHandlers()
{
  this->commandHandlers[CONNECT_TO_SERVER_COMMAND] = std::make_unique<ConnectToServerCommandHandler>(*this);
  this->commandHandlers[UPDATE_NAME_COMMAND] = std::make_unique<UpdateNameCommandHandler>(*this);
  this->commandHandlers[JOIN_ROOM_COMMAND] = std::make_unique<JoinRoomCommandHandler>(*this);
  this->commandHandlers[JOIN_ROOM_AUTO_COMMAND] = std::make_unique<JoinRoomAutoCommandHandler>(*this);
  this->commandHandlers[INPUT_COMMAND] = std::make_unique<InputCommandHandler>(*this);
  this->commandHandlers[JOIN_GAME_COMMAND] = std::make_unique<JoinGameCommandHandler>(*this);
  this->commandHandlers[KICK_PLAYER_COMMAND] = std::make_unique<KickPlayerCommandHandler>(*this);
}

void Network::UDPServer::checkClientTimers()
{
  for (auto &client : this->clients) {
    if (client.isInactiveFor(CLIENT_INACTIVE_TIMEOUT)) {
      this->notifyAndRemoveClient(client.getId());
      continue;
    }
    if (client.isInactiveFor(CLIENT_INACTIVE_CHECK_INTERVAL)) {
      this->sendCheckConnection(client.getId());
      continue;
    }
  }
}

void Network::UDPServer::startClientTimerCheck()
{
  this->clientsConnectionTimer.expires_from_now(std::chrono::milliseconds(CLIENT_INACTIVE_CHECK_INTERVAL));
  this->clientsConnectionTimer.async_wait([this](boost::system::error_code const &error) {
    if (!error) {
      this->checkClientTimers();
      this->startClientTimerCheck();
    }
  });
}

void Network::UDPServer::gameLoop()
{
  std::thread gameLoopThread([this]() {
    while (true) {
      {
        std::lock_guard<std::mutex> lock(this->roomsMutex);

        for (auto &room : this->rooms) {
          if (room.getState() != RUNNING)
            continue;
          std::vector<std::vector<char>> entities = room.getHostedGame().getEntities();
          if (entities.empty())
            return;
          std::vector<char> entitiesBuffer;
          const std::string delimiter = "\x1F";

          for (auto &entity : entities) {
            entitiesBuffer.insert(entitiesBuffer.end(), entity.begin(), entity.end());
            entitiesBuffer.insert(entitiesBuffer.end(), delimiter.begin(), delimiter.end());
          }

          if (!entitiesBuffer.empty() && !entities.empty())
            entitiesBuffer.erase(entitiesBuffer.end() - delimiter.size(), entitiesBuffer.end());

          std::vector<char> messageBuffer = this->createMessageBuffer(
            -1,
            SERVER_COMMAND_UPDATE_GAME,
            entitiesBuffer.data(),
            entitiesBuffer.size());
          boost::asio::const_buffer buffer = boost::asio::buffer(messageBuffer.data(), messageBuffer.size());

          this->sendToAllClientsInRoomInGame(buffer, room.getId());
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
      }
    }
  });

  gameLoopThread.detach();
}

void Network::UDPServer::notifyAndRemoveClient(int clientId)
{
  auto clientOpt = this->getClientById(clientId);
  if (!clientOpt.has_value())
    return;
  Client client = clientOpt.value();

  if (client.getRoomId() == -1) {
    for (size_t i = 0; i < this->clients.size(); i++) {
      if (this->clients[i].getId() == clientId) {
        this->clients.erase(this->clients.begin() + i);
        return;
      }
    }
  }

  ServerClientDisconnectedData data = {.clientId = clientId};
  char dataToSend[sizeof(data)];
  memcpy(dataToSend, &data, sizeof(data));

  std::vector<char> messageBuffer =
    this->createMessageBuffer(clientId, SERVER_COMMAND_CLIENT_DISCONNECTED, dataToSend, sizeof(data));

  spdlog::info("Client {} disconnected", clientId);
  this->rooms[client.getRoomId()].removePlayer(clientId);
  logMessage("Server message", (Message *)messageBuffer.data(), client);
  this->sendToAllClientsInRoom(
    boost::asio::buffer(messageBuffer.data(), messageBuffer.size()),
    client.getRoomId());

  for (size_t i = 0; i < this->clients.size(); i++) {
    if (this->clients[i].getId() == clientId) {
      this->clients.erase(this->clients.begin() + i);
      break;
    }
  }
}

void Network::UDPServer::sendCheckConnection(int clientId)
{
  std::vector<char> messageBuffer =
    this->createMessageBuffer(clientId, SERVER_COMMAND_CHECK_CONNECTION, nullptr, 0);
  auto clientOpt = this->getClientById(clientId);
  if (!clientOpt.has_value())
    return;
  Client client = clientOpt.value();

  logMessage("Server message", (Message *)messageBuffer.data(), client);

  this->sendToClient(boost::asio::buffer(messageBuffer.data(), messageBuffer.size()), clientId);
}

void Network::UDPServer::handleInvalidClient(TimedMessage timedMessage)
{
  int clientId = timedMessage.message->header.clientId;
  std::string statusMessage = clientId < 0 ? "Invalid client ID"
                                           : "Client not connected. Use " CONNECT_TO_SERVER_COMMAND
                                             " command to connect";

  std::vector<char> responseBuffer = this->createResponseBuffer(
    clientId,
    timedMessage.message->header,
    statusMessage,
    nullptr,
    0,
    RES_UNAUTHORIZED);

  spdlog::error("{}", statusMessage);
  // return this->sendResponseAndLog(timedMessage, responseBuffer);
}

void Network::UDPServer::handleInvalidCommand(TimedMessage timedMessage)
{
  std::vector<char> responseBuffer = this->createResponseBuffer(
    timedMessage.message->header.clientId,
    timedMessage.message->header,
    "Invalid command",
    nullptr,
    0,
    RES_BAD_REQUEST);

  return this->sendResponseAndLog(timedMessage, responseBuffer);
}
