//
// Created by raphael on 1/10/24.
//

#pragma once
#include "RendererController.hpp"
#include "NetworkController.hpp"

namespace Rtype::Controller
{
  class GraphicController
    : public RendererController
    , public NetworkController {
   public:
    explicit GraphicController(
      std::shared_ptr<GameEngine::Gfx::IRenderer> renderer,
      std::shared_ptr<GameEngine::Network::INetworkController> network);

    GraphicController() = default;
  };
} // namespace Rtype::GraphicController
