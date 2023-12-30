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

  // Update player position
  std::cout << "Player " << message->header.clientId << " pressed key: " << data->key << std::endl;

  std::vector<char> dataToSend(sizeof(*data));
  memcpy(dataToSend.data(), data, sizeof(*data));

  return this->server.createResponseBuffer(
    message->header.clientId,
    message->header,
    "Get key: \"" + std::string(data->key) + "\"",
    dataToSend.data(),
    dataToSend.size());
}
