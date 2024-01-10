//
// Created by Xavier VINCENT on 24/12/23.
//

#include "network/commands/KickPlayer.hpp"

#include <spdlog/spdlog.h>

namespace Client
{
  KickPlayerCommandHandler::KickPlayerCommandHandler(Network &network)
    : network(network)
  {
  }

  void KickPlayerCommandHandler::setClientId(int clientId)
  {
    this->clientId = clientId;
  }

  int KickPlayerCommandHandler::getClientId() const
  {
    return this->clientId;
  }

  void KickPlayerCommandHandler::send()
  {
    KickPlayerData data;
    data.clientId = this->clientId;
    char dataBuffer[sizeof(data)];
    memcpy(dataBuffer, &data, sizeof(data));

    this->network.sendMessage(KICK_PLAYER_COMMAND, dataBuffer, sizeof(data));
  }

  void KickPlayerCommandHandler::onResponse(Response *response)
  {
    KickPlayerData *data = (KickPlayerData *)response->data;

    spdlog::info("Player kicked: {}", data->clientId);
  }
};
