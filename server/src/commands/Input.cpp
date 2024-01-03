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
  for (auto &client : this->server.getClients())
    if (client.getId() == clientId)
      return true;
  return false;
}

std::vector<char> Network::InputCommandHandler::handleCommand(Message *message)
{
  InputData *data = (InputData *)message->data;
  // Client &client = this->server.getClientById(message->header.clientId);
  // Room &room = this->server.getRooms()[client.getRoomId()];

  //Server::Game::Player player = {.id = static_cast<size_t>(client.getId()), .name = client.getName(), .input = data->key};
  // room.getHostedGame().pushEvent(Server::Game::Event::Input, player);

  spdlog::info("Player {} pressed key: {}", message->header.clientId, data->key);

  std::vector<char> dataToSend(sizeof(*data));
  memcpy(dataToSend.data(), data, sizeof(*data));

  return this->server.createResponseBuffer(
    message->header.clientId,
    message->header,
    "Get key: \"" + std::string(data->key) + "\"",
    dataToSend.data(),
    dataToSend.size());
}
