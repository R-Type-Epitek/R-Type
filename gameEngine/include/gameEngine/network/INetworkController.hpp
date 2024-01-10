//
// Created by raphael on 1/10/24.
//

#pragma once

namespace GameEngine::Network
{
  class INetworkController {
   public:
    virtual ~INetworkController() = default;

    virtual void sendKey() = 0;

    virtual void connect() = 0;
  };
} // namespace GameEngine::Network
