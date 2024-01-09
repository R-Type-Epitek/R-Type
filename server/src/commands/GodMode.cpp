//
// Created by Xavier VINCENT on 09/01/2024.
//

#include "RTypeNetwork.hpp"

Network::GodModeCommandHandler::GodModeCommandHandler(Network::UDPServer &server)
  : server(server)
{
}

bool Network::GodModeCommandHandler::isAuthorized(int clientId)
{
  auto clientOpt = this->server.getClientById(clientId);
  if (clientOpt.has_value())
    return true;
  return false;
}

std::vector<char> Network::GodModeCommandHandler::handleCommand(Message *message)
{
  GodModeData *data = (GodModeData *)message->data;
  std::string statusMessage;
  int status = RES_SUCCESS;

  auto senderOpt = this->server.getClientById(message->header.clientId);
  Client sender;
  if (senderOpt)
    sender = senderOpt.value();
  else
    return this->server.createResponseBuffer(
      message->header.clientId,
      message->header,
      "Client not found",
      nullptr,
      0,
      RES_UNAUTHORIZED);

  auto clientOpt = this->server.getClientById(data->clientId);
  if (clientOpt.has_value()) {
    Client client = clientOpt.value();

    client.setIsGodMode(true);
    statusMessage = "Player " + std::to_string(client.getId()) + " is now in god mode";
  } else {
    status = RES_UNAUTHORIZED;
    statusMessage = "Player not found";
  }

  std::vector<char> dataToSend(sizeof(*data));
  memcpy(dataToSend.data(), data, sizeof(*data));

  return this->server.createResponseBuffer(
    message->header.clientId,
    message->header,
    statusMessage,
    dataToSend.data(),
    dataToSend.size(),
    status);
}
