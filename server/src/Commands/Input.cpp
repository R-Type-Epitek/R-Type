//
// Created by Xavier VINCENT on 20/12/2023.
//

#include "RTypeNetwork.hpp"

Network::InputCommandHandler::InputCommandHandler(Network::UDPServer& server) : server(server) {}

bool Network::InputCommandHandler::isAuthorized(int clientId) {
  for (auto& client : this->server.getClients())
    if (client.getId() == clientId) return true;
  return false;
}

Response Network::InputCommandHandler::handleCommand(Message* message) {
  InputData* data = (InputData*)message->data;

  // Update player position
  std::cout << "Player " << message->header.clientId << " pressed key: " << data->key << std::endl;

  return this->server.createResponse(message->header.clientId, INPUT_COMMAND,
                                     "Get key: \"" + std::string(data->key) + "\"");
}
