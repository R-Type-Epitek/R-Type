//
// Created by Xavier VINCENT on 20/12/2023.
//

#include "RTypeNetwork.hpp"

Network::UpdateNameCommandHandler::UpdateNameCommandHandler(Network::UDPServer &server)
  : server(server)
{
}

bool Network::UpdateNameCommandHandler::isAuthorized(int clientId)
{
  auto clientOpt = this->server.getClientById(clientId);
  if (clientOpt.has_value())
    return true;
  return false;
}

std::vector<char> Network::UpdateNameCommandHandler::handleCommand(Message *message)
{
  UpdateNameData *data = (UpdateNameData *)message->data;

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

  client.setName(data->name);

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
