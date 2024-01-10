//
// Created by raphael on 1/10/24.
//

#pragma once
#include "gameEngine/constants/Keybinds.hpp"

namespace GameEngine::Network
{
  class INetworkController {
   public:
    virtual ~INetworkController() = default;

    virtual void sendKey(GameEngine::Keybinds key) = 0;

    virtual void connect() = 0;
  };
} // namespace GameEngine::Network
