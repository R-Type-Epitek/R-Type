//
// Created by raphael on 1/10/24.
//

#pragma once
#include <utility>

#include "NetworkController.hpp"

namespace Rtype::SceneController
{
  class LobbyController : public NetworkController {
   public:
    LobbyController(std::shared_ptr<GameEngine::Network::INetworkController> networkController)
      : NetworkController(std::move(networkController)) {};
    ~LobbyController() = default;
  };
} // namespace Rtype::SceneController
