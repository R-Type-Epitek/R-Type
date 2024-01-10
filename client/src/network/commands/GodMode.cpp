//
// Created by Xavier VINCENT on 24/12/23.
//

#include "network/commands/GodMode.hpp"

#include <spdlog/spdlog.h>

namespace Client
{
  GodModeCommandHandler::GodModeCommandHandler(Network &network)
    : network(network)
  {
  }

  void GodModeCommandHandler::setClientId(int clientId)
  {
    this->clientId = clientId;
  }

  int GodModeCommandHandler::getClientId() const
  {
    return this->clientId;
  }

  void GodModeCommandHandler::send()
  {
    GodModeData data;
    data.clientId = this->clientId;
    char dataBuffer[sizeof(data)];
    memcpy(dataBuffer, &data, sizeof(data));

    this->network.sendMessage(GOD_MODE_COMMAND, dataBuffer, sizeof(data));
  }

  void GodModeCommandHandler::onResponse(Response *response)
  {
    GodModeData *data = (GodModeData *)response->data;

    spdlog::info("Player {} is now in god mode", data->clientId);
  }
};
