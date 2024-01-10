//
// Created by raphael on 1/10/24.
//

#include "sceneController/NetworkController.hpp"

namespace Rtype::SceneController
{
  NetworkController::NetworkController(
    std::shared_ptr<GameEngine::Network::INetworkController> networkController)
    : m_networkController(std::move(networkController))
  {
  }

} // namespace Rtype::SceneControllers
