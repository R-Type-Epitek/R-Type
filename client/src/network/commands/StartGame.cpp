//
// Created by Xavier VINCENT on 24/12/23.
//

#include "network/commands/StartGame.hpp"

#include <spdlog/spdlog.h>

namespace Client
{
  StartGameCommandHandler::StartGameCommandHandler(Network &network)
    : network(network)
  {
  }

  void StartGameCommandHandler::setRoomId(int roomId)
  {
    this->roomId = roomId;
  }

  int StartGameCommandHandler::getRoomId() const
  {
    return this->roomId;
  }

  void StartGameCommandHandler::send()
  {
    StartGameData data;
    data.roomId = this->roomId;
    char dataBuffer[sizeof(data)];
    memcpy(dataBuffer, &data, sizeof(data));

    this->network.sendMessage(START_GAME_COMMAND, dataBuffer, sizeof(data));
  }

  void StartGameCommandHandler::onResponse(Response *response)
  {
    StartGameData *data = (StartGameData *)response->data;

    spdlog::info("Game started in room {}", data->roomId);
  }
};
