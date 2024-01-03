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
  for (auto &client : this->server.getClients())
    if (client.getId() == clientId)
      return true;
  return false;
}

std::vector<char> Network::JoinGameCommandHandler::handleCommand(Message *message)
{
  JoinGameData *data = (JoinGameData *)message->data;

  Room &room = this->server.getRooms()[data->roomId];
  Client &client = this->server.getClientById(message->header.clientId);

  Server::Game::Player player = {.id = static_cast<size_t>(client.getId()), .name = client.getName()};
  room.getHostedGame().pushEvent(Server::Game::Event::Connect, player);

  if (room.getState() != FINISHED)
    room.setState(RUNNING);

  std::vector<char> dataToSend(sizeof(*data));
  memcpy(dataToSend.data(), data, sizeof(*data));

  return this->server.createResponseBuffer(
    message->header.clientId,
    message->header,
    "Joined game (room " + std::to_string(data->roomId) + ")",
    dataToSend.data(),
    dataToSend.size());
}
