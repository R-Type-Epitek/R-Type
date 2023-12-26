//
// Created by Xavier VINCENT on 24/12/23.
//

#include "RTypeClient.hpp"

namespace Client
{
  ConnectToServerCommandHandler::ConnectToServerCommandHandler(Network& network)
    : network(network)
  {
  }

  void ConnectToServerCommandHandler::send()
  {
    this->network.sendMessage(CONNECT_TO_SERVER_COMMAND);
  }

  void ConnectToServerCommandHandler::onResponse(Response* response)
  {
    this->network.setClientId(response->header.clientId);

    std::string address =
      this->network.getRemoteEndpoint().address().to_string();
    std::string port = std::to_string(this->network.getRemoteEndpoint().port());
    spdlog::info("Connected to server: {}:{}", address, port);
    spdlog::info("Client id: {}", this->network.getClientId());
  }
};
