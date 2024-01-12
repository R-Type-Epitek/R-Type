//
// Created by raphael on 1/10/24.
//

#pragma once
#include "gameEngine/constants/Keybinds.hpp"
#include <vector>
#include <string>

namespace GameEngine::Network
{
  class INetworkController {
   public:
    virtual ~INetworkController() = default;

    virtual void sendKey(GameEngine::Keybinds key) = 0;

    virtual void connect() = 0;

    virtual void joinRoomAuto() = 0;

    virtual void joinRoom(int roomId) = 0;

    virtual void spectate(int roomId) = 0;

    virtual void joinGame(int roomId) = 0;

    virtual void updateName(std::string name) = 0;

    virtual std::vector<std::vector<char>> getSerializedEcsState() = 0;
  };
} // namespace GameEngine::Network
