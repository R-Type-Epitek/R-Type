//
// Created by Xavier VINCENT on 24/12/23.
//

#include "network/commands/JoinRoom.hpp"

#include <spdlog/spdlog.h>

namespace Client
{
  JoinRoomCommandHandler::JoinRoomCommandHandler(Network &network)
    : network(network)
  {
  }

  void JoinRoomCommandHandler::setRoomId(int roomId)
  {
    this->roomId = roomId;
  }

  int JoinRoomCommandHandler::getRoomId() const
  {
    return this->roomId;
  }

  void JoinRoomCommandHandler::send()
  {
    JoinRoomData data;
    data.roomId = this->roomId;
    char dataBuffer[sizeof(data)];
    memcpy(dataBuffer, &data, sizeof(data));

    this->network.sendMessage(JOIN_ROOM_COMMAND, dataBuffer, sizeof(data));
  }

  void JoinRoomCommandHandler::onResponse(Response *response)
  {
    JoinRoomData *data = (JoinRoomData *)response->data;
    this->network.setRoomId(data->roomId);

    spdlog::info("Joined room: {}", data->roomId);
  }
};
