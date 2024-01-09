//
// Created by Xavier VINCENT on 09/01/23.
//

#include "network/commands/Spectate.hpp"

#include <spdlog/spdlog.h>

namespace Client
{
  SpectateCommandHandler::SpectateCommandHandler(Network &network)
    : network(network)
  {
  }

  void SpectateCommandHandler::setRoomId(int roomId)
  {
    this->roomId = roomId;
  }

  int SpectateCommandHandler::getRoomId() const
  {
    return this->roomId;
  }

  void SpectateCommandHandler::send()
  {
    SpectateData data;
    data.roomId = this->roomId;
    char dataBuffer[sizeof(data)];
    memcpy(dataBuffer, &data, sizeof(data));

    this->network.sendMessage(SPECTATE_COMMAND, dataBuffer, sizeof(data));
  }

  void SpectateCommandHandler::onResponse(Response *response)
  {
    SpectateData *data = (SpectateData *)response->data;

    spdlog::info("Spectating room {}", data->roomId);
  }
};
