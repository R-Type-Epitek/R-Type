//
// Created by raphael on 1/10/24.
//

#pragma once
#include "gameEngine/network/INetworkController.hpp"
#include <memory>

namespace Rtype::Controller
{
  class NetworkController {
   public:
    explicit NetworkController(std::shared_ptr<GameEngine::Network::INetworkController> networkController)
      : m_networkController(std::move(networkController)) {};
    ~NetworkController() = default;

    GameEngine::Network::INetworkController& getNetwork()
    {
      return *m_networkController;
    }

   private:
    std::shared_ptr<GameEngine::Network::INetworkController> m_networkController;
  };
} // namespace Rtype::SceneController
