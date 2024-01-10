//
// Created by raphael on 1/10/24.
//

#pragma once
#include "gameEngine/network/INetworkController.hpp"
#include <memory>

namespace Rtype::SceneController
{
  class NetworkController {
   public:
    NetworkController(std::shared_ptr<GameEngine::Network::INetworkController> networkController);
    ~NetworkController() = default;

   private:
    std::shared_ptr<GameEngine::Network::INetworkController> m_networkController;
  };
} // namespace Rtype::SceneController
