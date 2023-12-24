//
// Created by Xavier VINCENT on 20/12/2023.
//

#include "RTypeNetwork.hpp"

Network::UpdateNameCommandHandler::UpdateNameCommandHandler(
  Network::UDPServer &server)
  : server(server)
{
}

bool Network::UpdateNameCommandHandler::isAuthorized(int clientId)
{
  for (auto &client : this->server.getClients())
    if (client.getId() == clientId)
      return true;
  return false;
}

std::vector<char> Network::UpdateNameCommandHandler::handleCommand(
  Message *message)
{
  UpdateNameData *data = (UpdateNameData *)message->data;

  this->server.getClients()[message->header.clientId].setName(data->name);

  UpdateNameData dataToSend;
  strcpy(dataToSend.name, data->name);
  char dataBuffer[sizeof(dataToSend)];
  memcpy(dataBuffer, &dataToSend, sizeof(dataToSend));

  return this->server.createResponseBuffer(
    message->header.clientId,
    message->header,
    "Name correctly set: " + std::string(data->name),
    dataBuffer,
    sizeof(dataToSend));
}
