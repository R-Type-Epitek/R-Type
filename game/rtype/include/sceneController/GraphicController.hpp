//
// Created by raphael on 1/10/24.
//

#pragma once
#include "RendererController.hpp"
#include "NetworkController.hpp"
#include "SceneController.hpp"

namespace Rtype::Controller
{
  class GraphicController
    : public RendererController
    , public NetworkController
    , public SceneController {
   public:
    explicit GraphicController(
      std::shared_ptr<GameEngine::Gfx::IRenderer> renderer,
      std::shared_ptr<GameEngine::Network::INetworkController> network,
      std::shared_ptr<GameEngine::Scene::ISceneManager> sceneManager);

    GraphicController() = default;
  };
} // namespace Rtype::GraphicController
