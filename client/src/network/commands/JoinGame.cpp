//
// Created by Xavier VINCENT on 24/12/23.
//

#include "network/commands/JoinGame.hpp"

#include <spdlog/spdlog.h>

namespace Client
{
  JoinGameCommandHandler::JoinGameCommandHandler(Network &network)
    : network(network)
  {
  }

  void JoinGameCommandHandler::setRoomId(int roomId)
  {
    this->roomId = roomId;
  }

  int JoinGameCommandHandler::getRoomId() const
  {
    return this->roomId;
  }

  void JoinGameCommandHandler::send()
  {
    JoinGameData data;
    data.roomId = this->roomId;
    char dataBuffer[sizeof(data)];
    memcpy(dataBuffer, &data, sizeof(data));

    this->network.sendMessage(JOIN_GAME_COMMAND, dataBuffer, sizeof(data));
  }

  void JoinGameCommandHandler::onResponse(Response *response)
  {
    JoinGameData *data = (JoinGameData *)response->data;

    spdlog::info("Game started in room {}", data->roomId);
  }
};
