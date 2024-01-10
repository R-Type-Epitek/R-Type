//
// Created by raphael on 1/10/24.
//

#pragma once
#include <utility>

#include "NetworkController.hpp"

namespace Rtype::SceneController
{
  class WelcomeController : public NetworkController {
   public:
    WelcomeController(std::shared_ptr<GameEngine::Network::INetworkController> networkController)
      : NetworkController(std::move(networkController)) {};
    ~WelcomeController() = default;
  };
} // namespace Rtype::SceneController
