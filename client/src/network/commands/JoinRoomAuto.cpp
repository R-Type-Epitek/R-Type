//
// Created by Xavier VINCENT on 24/12/23.
//

#include "network/commands/JoinRoomAuto.hpp"

#include <spdlog/spdlog.h>

namespace Client
{
  JoinRoomAutoCommandHandler::JoinRoomAutoCommandHandler(Network &network)
    : network(network)
  {
  }

  void JoinRoomAutoCommandHandler::send()
  {
    this->network.sendMessage(JOIN_ROOM_AUTO_COMMAND, nullptr, 0);
  }

  void JoinRoomAutoCommandHandler::onResponse(Response *response)
  {
    JoinRoomData *data = (JoinRoomData *)response->data;
    this->network.setRoomId(data->roomId);

    spdlog::info("Joined room: {}", data->roomId);
  }
};
