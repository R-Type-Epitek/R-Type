//
// Created by raphael on 1/10/24.
//

#pragma once
#include "gameEngine/network/INetworkController.hpp"

namespace Rtype::SceneController
{
  class NetworkController {
   public:
    NetworkController(GameEngine::Network::INetworkController &networkController);
    ~NetworkController() = default;

   private:
    GameEngine::Network::INetworkController &m_networkController;
  };
} // namespace Rtype::SceneController
