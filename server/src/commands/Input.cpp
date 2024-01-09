//
// Created by Xavier VINCENT on 20/12/2023.
//

#include "RTypeNetwork.hpp"

Network::InputCommandHandler::InputCommandHandler(Network::UDPServer &server)
  : server(server)
{
}

bool Network::InputCommandHandler::isAuthorized(int clientId)
{
  auto clientOpt = this->server.getClientById(clientId);
  if (clientOpt.has_value())
    return true;
  return false;
}

std::vector<char> Network::InputCommandHandler::handleCommand(Message *message)
{
  InputData *data = (InputData *)message->data;
  auto clientOpt = this->server.getClientById(message->header.clientId);
  Client client;
  if (clientOpt.has_value())
    client = clientOpt.value();
  else
    return this->server.createResponseBuffer(
      message->header.clientId,
      message->header,
      "Client not found",
      nullptr,
      0,
      RES_UNAUTHORIZED);
  Room &room = this->server.getRooms()[client.getRoomId()];

  if (room.getState() != RUNNING)
    return this->server.createResponseBuffer(
      message->header.clientId,
      message->header,
      "Room is not running",
      nullptr,
      0,
      RES_UNAUTHORIZED);

  if (!client.getIsInGame())
    return this->server.createResponseBuffer(
      message->header.clientId,
      message->header,
      "Client is not in game",
      nullptr,
      0,
      RES_UNAUTHORIZED);

  if (client.getIsSpectator())
    return this->server.createResponseBuffer(
      message->header.clientId,
      message->header,
      "Client is a spectator",
      nullptr,
      0,
      RES_UNAUTHORIZED);

  Server::Game::Player player = {
    .id = static_cast<size_t>(client.getId()),
    .name = client.getName(),
    .key = static_cast<GameEngine::Keybinds>(data->key)};
  room.getHostedGame().pushEvent(Server::Game::Event::Input, player);

  spdlog::info("Player {} pressed key: {}", message->header.clientId, data->key);

  std::vector<char> dataToSend(sizeof(*data));
  memcpy(dataToSend.data(), data, sizeof(*data));

  return this->server.createResponseBuffer(
    message->header.clientId,
    message->header,
    "Get key: " + std::to_string(data->key),
    dataToSend.data(),
    dataToSend.size());
}
