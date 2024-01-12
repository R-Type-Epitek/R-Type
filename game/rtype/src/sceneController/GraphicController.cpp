//
// Created by raphael on 1/10/24.
//

#include "sceneController/GraphicController.hpp"

namespace Rtype::Controller
{
  GraphicController::GraphicController(
    std::shared_ptr<GameEngine::Gfx::IRenderer> renderer,
    std::shared_ptr<GameEngine::Network::INetworkController> network,
    std::shared_ptr<GameEngine::Scene::ISceneManager> sceneManager)
    : RendererController(std::move(renderer))
    , NetworkController(std::move(network))
    , SceneController(std::move(sceneManager)) {};

} // namespace Rtype::Controller
