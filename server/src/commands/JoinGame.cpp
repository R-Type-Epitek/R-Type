//
// Created by Xavier VINCENT on 20/12/2023.
//

#include "RTypeNetwork.hpp"

Network::JoinGameCommandHandler::JoinGameCommandHandler(Network::UDPServer &server)
  : server(server)
{
}

bool Network::JoinGameCommandHandler::isAuthorized(int clientId)
{
  auto clientOpt = this->server.getClientById(clientId);
  if (clientOpt.has_value())
    return true;
  return false;
}

std::vector<char> Network::JoinGameCommandHandler::handleCommand(Message *message)
{
  JoinGameData *data = (JoinGameData *)message->data;

  Room &room = this->server.getRooms()[data->roomId];
  auto clientOpt = this->server.getClientById(message->header.clientId);
  if (!clientOpt.has_value())
    return this->server.createResponseBuffer(
      message->header.clientId,
      message->header,
      "Client not found",
      nullptr,
      0,
      RES_UNAUTHORIZED);
  Client &client = clientOpt.value();
  int clientRoomId = client.getRoomId();

  if (client.getIsInGame())
    return this->server.createResponseBuffer(
      message->header.clientId,
      message->header,
      "Client is already in a game",
      nullptr,
      0,
      RES_UNAUTHORIZED);

  if (room.getId() != client.getRoomId() || clientRoomId == -1)
    return this->server.createResponseBuffer(
      message->header.clientId,
      message->header,
      clientRoomId == -1 ? "Client not in a room" : "Client not in the same room",
      nullptr,
      0,
      RES_UNAUTHORIZED);

  client.setIsInGame(true);
  client.setIsSpectator(false);

  Server::Game::Player player = {.id = static_cast<size_t>(client.getId()), .name = client.getName()};
  room.getHostedGame().pushEvent(Server::Game::Event::Connect, player);

  if (room.getState() != FINISHED)
    room.setState(RUNNING);

  std::vector<char> dataToSend(sizeof(*data));
  memcpy(dataToSend.data(), data, sizeof(*data));

  return this->server.createResponseBuffer(
    message->header.clientId,
    message->header,
    "Client is playing in room " + std::to_string(data->roomId),
    dataToSend.data(),
    dataToSend.size());
}
