//
// Created by raphael on 1/10/24.
//

#include "sceneController/RendererController.hpp"

namespace Rtype::Controller
{
  RendererController::RendererController(std::shared_ptr<GameEngine::Gfx::IRenderer> renderer)
    : m_renderer(std::move(renderer)) {};

  GameEngine::Gfx::IRenderer& RendererController::getRenderer()
  {
    return *m_renderer;
  }

} // namespace Rtype::Controller
