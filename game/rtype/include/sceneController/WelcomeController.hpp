//
// Created by raphael on 1/10/24.
//

#pragma once
#include "NetworkController.hpp"

namespace Rtype::SceneController
{
  class WelcomeController : public NetworkController {
   public:
    WelcomeController(GameEngine::Network::INetworkController &networkController)
      : NetworkController(networkController) {};
    ~WelcomeController() = default;
  };
} // namespace Rtype::SceneController
