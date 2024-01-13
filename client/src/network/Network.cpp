//
// Created by Xavier VINCENT on 14/12/2023.
//

#include "network/Network.hpp"

#include "gameEngine/constants/Keybinds.hpp"
#include "gameEngine/network/Commands.hpp"
#include "gameEngine/network/MessageType.hpp"
#include "gameEngine/network/Messages.hpp"
#include "gameEngine/network/Responses.hpp"
#include "gameEngine/network/Statuses.hpp"
#include "network/commands/ConnectToServer.hpp"
#include "network/commands/IHandler.hpp"
#include "network/commands/Input.hpp"
#include "network/commands/GodMode.hpp"
#include "network/commands/JoinRoom.hpp"
#include "network/commands/JoinRoomAuto.hpp"
#include "network/commands/JoinGame.hpp"
#include "network/commands/KickPlayer.hpp"
#include "network/commands/Spectate.hpp"
#include "network/commands/Tracker.hpp"
#include "network/commands/UpdateName.hpp"
#include "network/tools/EndianConverter.hpp"
#include "network/tools/Logs.hpp"

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <memory>
#include <spdlog/spdlog.h>
#include <string>
#include <thread>
#include <vector>

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
  stopReceiveThread = true;
  if (receiveThread.joinable()) {
    receiveThread.join();
  }
  socket.close();
  io.stop();
}

void Client::Network::registerCommandHandlers()
{
  this->commandHandlers[CONNECT_TO_SERVER_COMMAND] = std::make_shared<ConnectToServerCommandHandler>(*this);
  this->commandHandlers[UPDATE_NAME_COMMAND] = std::make_shared<UpdateNameCommandHandler>(*this);
  this->commandHandlers[JOIN_ROOM_COMMAND] = std::make_shared<JoinRoomCommandHandler>(*this);
  this->commandHandlers[JOIN_ROOM_AUTO_COMMAND] = std::make_shared<JoinRoomAutoCommandHandler>(*this);
  this->commandHandlers[INPUT_COMMAND] = std::make_shared<InputCommandHandler>(*this);
  this->commandHandlers[JOIN_GAME_COMMAND] = std::make_shared<JoinGameCommandHandler>(*this);
  this->commandHandlers[KICK_PLAYER_COMMAND] = std::make_shared<KickPlayerCommandHandler>(*this);
  this->commandHandlers[GOD_MODE_COMMAND] = std::make_shared<GodModeCommandHandler>(*this);
  this->commandHandlers[SPECTATE_COMMAND] = std::make_shared<SpectateCommandHandler>(*this);
}

std::shared_ptr<Client::ICommandHandler> Client::Network::getCommandHandler(const std::string &name)
{
  auto it = this->commandHandlers.find(name);
  if (it != this->commandHandlers.end()) {
    return it->second;
  }
  throw std::runtime_error("Invalid command name: " + name);
}

void Client::Network::send(boost::asio::const_buffer const &buffer)
{
  Tools::EndianConverter converter(buffer);
  auto bufferLittleEndian = converter.getLittleEndian();

  this->socket.async_send_to(
    bufferLittleEndian,
    this->remoteEndpoint,
    boost::bind(
      &Client::Network::handleSend,
      this,
      boost::asio::placeholders::error,
      boost::asio::placeholders::bytes_transferred));
}

void Client::Network::handleSend(boost::system::error_code const &error, std::size_t bytesTransferred)
{
  if (error && error == boost::asio::error::message_size)
    return spdlog::error("handleSend: Error: {} ({} bytes)", error.message(), bytesTransferred);
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
  if (strcmp(message->header.command, SERVER_COMMAND_UPDATE_GAME) != 0)
    logMessage("Client message", message);

  this->send(boost::asio::buffer(messageBuffer.data(), messageBuffer.size()));

  std::thread([this, commandId, command]() {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    if (!commandTrackers[commandId]->getIsCompleted())
      spdlog::error("Command {} timed out", command);
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
    while (!this->stopReceiveThread) {
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
  if (error && error == boost::asio::error::message_size)
    return spdlog::error("Error: {} ({} bytes)", error.message(), bytesTransferred);

  MessageType *type = (MessageType *)this->recvBuffer.data();

  Tools::EndianConverter converter(boost::asio::const_buffer(this->recvBuffer.data(), bytesTransferred));
  auto nativeEndianBuffer = converter.getNativeEndian();

  char *data = (char *)nativeEndianBuffer.data();

  switch (*type) {
    case MessageType::Response:
      return this->onServerResponse((Response *)data);
    case MessageType::Message:
      return this->onServerMessage((Message *)data);
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
      spdlog::error("Error {}: {}", response->header.status, response->header.statusMessage);
      return;
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
  uint32_t timestamp = message->header.timestamp;
  uint32_t currentTimestamp =
    std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())
      .count();
  uint32_t diff = currentTimestamp - timestamp;
  this->ping = diff;

  spdlog::info("Ping: {} ms", this->ping);

  if (strcmp(message->header.command, SERVER_COMMAND_UPDATE_GAME) != 0)
    logMessage("Server message", message);

  if (!strcmp(message->header.command, SERVER_COMMAND_CHECK_CONNECTION))
    return this->onCheckConnectionMessage(message);
  else if (!strcmp(message->header.command, SERVER_COMMAND_CLIENT_DISCONNECTED))
    return;
  else if (!strcmp(message->header.command, SERVER_COMMAND_UPDATE_GAME))
    return this->onUpdateGameMessage(message);
  else
    throw std::runtime_error("Invalid message command");
}

void Client::Network::onCheckConnectionMessage(Message *message)
{
  return this->sendResponse(message->header.command, "OK");
}

void Client::Network::onUpdateGameMessage(Message *message)
{
  std::vector<char> data(message->data, message->data + message->header.dataLength);
  std::vector<std::vector<char>> entities;

  std::string dataString(data.begin(), data.end());
  const std::string delimiter = "\x1F";
  size_t pos = 0;
  std::string token;

  while ((pos = dataString.find(delimiter)) != std::string::npos) {
    token = dataString.substr(0, pos);
    entities.push_back(std::vector<char>(token.begin(), token.end()));
    dataString.erase(0, pos + delimiter.length());
  }

  entities.push_back(std::vector<char>(dataString.begin(), dataString.end()));

  this->m_serializedEcsDataQueue = entities;

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

int Client::Network::getRoomId()
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

void Client::Network::joinRoomAuto()
{
  this->executeCommand<JoinRoomAutoCommandHandler>(JOIN_ROOM_AUTO_COMMAND, [](auto commandHandler) {
    commandHandler->send();
  });
}

void Client::Network::kickPlayer(int clientId)
{
  this->executeCommand<KickPlayerCommandHandler>(KICK_PLAYER_COMMAND, [clientId](auto commandHandler) {
    commandHandler->setClientId(clientId);
    commandHandler->send();
  });
}

void Client::Network::godMode(int clientId)
{
  this->executeCommand<GodModeCommandHandler>(GOD_MODE_COMMAND, [clientId](auto commandHandler) {
    commandHandler->setClientId(clientId);
    commandHandler->send();
  });
}

void Client::Network::sendKey(GameEngine::Keybinds key)
{
  this->executeCommand<InputCommandHandler>(INPUT_COMMAND, [key](auto commandHandler) {
    commandHandler->setKey(key);
    commandHandler->send();
  });
}

void Client::Network::joinGame(int roomId)
{
  this->executeCommand<JoinGameCommandHandler>(JOIN_GAME_COMMAND, [roomId](auto commandHandler) {
    commandHandler->setRoomId(roomId);
    commandHandler->send();
  });
}

void Client::Network::spectate(int roomId)
{
  this->executeCommand<SpectateCommandHandler>(SPECTATE_COMMAND, [roomId](auto commandHandler) {
    commandHandler->setRoomId(roomId);
    commandHandler->send();
  });
}

void Client::Network::connect()
{
  spdlog::info("Establishing Network connection...");
  connectToServer();
  spdlog::info("Done connection established");
  spdlog::info("Getting player id...");
  while (getClientId() == -1) {
  };
  spdlog::info("Done");
}

std::vector<std::vector<char>> Client::Network::getSerializedEcsState()
{
  return m_serializedEcsDataQueue;
}
