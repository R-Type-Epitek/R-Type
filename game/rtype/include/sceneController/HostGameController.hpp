//
// Created by raphael on 1/10/24.
//

#pragma once
#include "NetworkController.hpp"

namespace Rtype::SceneController
{
  class HostGameController : public NetworkController {
   public:
    HostGameController(GameEngine::Network::INetworkController &networkController)
      : NetworkController(networkController) {};
    ~HostGameController() = default;
  };
} // namespace Rtype::SceneController
