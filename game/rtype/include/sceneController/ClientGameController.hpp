//
// Created by raphael on 1/10/24.
//

#pragma once
#include <utility>

#include "NetworkController.hpp"

namespace Rtype::SceneController
{
  class ClientGameController : public NetworkController {
   public:
    explicit ClientGameController(std::shared_ptr<GameEngine::Network::INetworkController> networkController)
      : NetworkController(std::move(networkController)) {};
    ~ClientGameController() = default;
  };
} // namespace Rtype::SceneController
