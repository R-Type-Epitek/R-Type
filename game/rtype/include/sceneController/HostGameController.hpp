//
// Created by raphael on 1/10/24.
//

#pragma once
#include <utility>

#include "NetworkController.hpp"

namespace Rtype::SceneController
{
  class HostGameController : public NetworkController {
   public:
    HostGameController(std::shared_ptr<GameEngine::Network::INetworkController> networkController)
      : NetworkController(std::move(networkController)) {};
    ~HostGameController() = default;
  };
} // namespace Rtype::SceneController
