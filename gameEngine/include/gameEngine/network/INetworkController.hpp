//
// Created by raphael on 1/10/24.
//

#pragma once

namespace GameEngine::Network
{
  struct NetworkController {
    virtual ~NetworkController() = default;

    virtual void sendKey() = 0;

    virtual void connect() = 0;
  };
} // namespace GameEngine::Network
