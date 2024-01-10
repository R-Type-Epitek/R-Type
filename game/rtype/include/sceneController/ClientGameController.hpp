//
// Created by raphael on 1/10/24.
//

#pragma once
#include "NetworkController.hpp"

namespace Rtype::SceneController
{
  class ClientGameController : public NetworkController {
   public:
    explicit ClientGameController(GameEngine::Network::INetworkController &networkController)
      : NetworkController(networkController) {};
    ~ClientGameController() = default;
  };
} // namespace Rtype::SceneController
