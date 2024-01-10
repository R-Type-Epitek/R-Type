//
// Created by raphael on 12/20/23.
//

#pragma once

#include "gameEngine/gfx/IRenderer.hpp"

#include <memory>

namespace GameEngine::UI
{

  class Window {
   public:
    Window(std::shared_ptr<Gfx::IRenderer> renderer)
      : m_renderer {std::move(renderer)} {};

    void setFramerateLimit(unsigned int limit)
    {
      m_renderer->setFramerateLimit(limit);
    };

    Gfx::IRenderer &getRenderer()
    {
      return m_renderer->getRenderer();
    };

    bool isOpen()
    {
      return m_renderer->isActive();
    };

    void display()
    {
      m_renderer->display();
    };

    void clear()
    {
      m_renderer->clear();
    };

   private:
    std::shared_ptr<Gfx::IRenderer> m_renderer;
    //    Gfx::IEvent m_event;
  };

} // namespace GameEngine::UI
