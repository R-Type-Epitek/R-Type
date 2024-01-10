//
// Created by raphael on 1/10/24.
//

#include "sceneController/GraphicController.hpp"

namespace Rtype::Controller
{
  GraphicController::GraphicController(
    std::shared_ptr<GameEngine::Gfx::IRenderer> renderer,
    std::shared_ptr<GameEngine::Network::INetworkController> network)
    : RendererController(std::move(renderer))
    , NetworkController(std::move(network)) {};

} // namespace Rtype::Controller
