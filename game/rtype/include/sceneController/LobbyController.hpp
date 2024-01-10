//
// Created by raphael on 1/10/24.
//

#pragma once
#include "NetworkController.hpp"

namespace Rtype::SceneController
{
  class LobbyController : public NetworkController {
   public:
    LobbyController(GameEngine::Network::INetworkController &networkController)
      : NetworkController(networkController) {};
    ~LobbyController() = default;
  };
} // namespace Rtype::SceneController
