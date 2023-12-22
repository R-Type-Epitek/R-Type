//
// Created by Xavier VINCENT on 20/12/2023.
//

#include "RTypeNetwork.hpp"

Network::UpdateNameCommandHandler::UpdateNameCommandHandler(Network::UDPServer& server) : server(server) {}

bool Network::UpdateNameCommandHandler::isAuthorized(int clientId) {
  for (auto& client : this->server.getClients())
    if (client.getId() == clientId) return true;
  return false;
}

Response Network::UpdateNameCommandHandler::handleCommand(Message* message) {
  UpdateNameData* data = (UpdateNameData*)message->data;

  this->server.getClients()[message->header.clientId].setName(data->name);

  return this->server.createResponse(message->header.clientId, UPDATE_NAME_COMMAND,
                                     "Name correctly set: " + std::string(data->name));
}
