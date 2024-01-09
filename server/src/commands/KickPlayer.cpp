//
// Created by Xavier VINCENT on 09/01/2024.
//

#include "RTypeNetwork.hpp"

Network::KickPlayerCommandHandler::KickPlayerCommandHandler(Network::UDPServer &server)
  : server(server)
{
}

bool Network::KickPlayerCommandHandler::isAuthorized(int clientId)
{
  auto clientOpt = this->server.getClientById(clientId);
  if (clientOpt.has_value())
    return true;
  return false;
}

std::vector<char> Network::KickPlayerCommandHandler::handleCommand(Message *message)
{
  KickPlayerData *data = (KickPlayerData *)message->data;
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

  auto clientToKickOpt = this->server.getClientById(data->clientId);
  if (clientToKickOpt.has_value()) {
    Client const clientToKick = clientToKickOpt.value();

    if (clientToKick.getRoomId() != sender.getRoomId()) {
      status = RES_UNAUTHORIZED;
      statusMessage = "Player not in the same room";
    } else {
      this->server.notifyAndRemoveClient(clientToKick.getId());
      statusMessage = "Player " + std::to_string(clientToKick.getId()) + " kicked";
    }
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
