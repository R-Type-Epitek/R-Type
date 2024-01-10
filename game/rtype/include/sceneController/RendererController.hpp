//
// Created by raphael on 1/10/24.
//

#pragma once
#include <memory>
#include "gameEngine/gfx/IRenderer.hpp"

namespace Rtype::Controller
{
  class RendererController {
   public:
    explicit RendererController(std::shared_ptr<GameEngine::Gfx::IRenderer> window);
    RendererController() = default;

    GameEngine::Gfx::IRenderer& getRenderer();

   private:
    std::shared_ptr<GameEngine::Gfx::IRenderer> m_renderer;
  };
} // namespace Rtype::Controller
