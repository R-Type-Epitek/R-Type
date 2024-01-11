//
// Created by raphael on 1/10/24.
//

#pragma once
#include "gameEngine/gfx/IRenderer.hpp"
#include "SFML/Graphics.hpp"

namespace GameEngine::Gfx::Sfml
{
  class Renderer : public IRenderer {
   public:
    Renderer(int width, int height, const std::string& name)
      : m_window(sf::VideoMode(width, height), name) {};

    void clear() final
    {
      m_window.clear();
    };

    void display() final
    {
      m_window.display();
    };

    bool isActive() final
    {
      return m_window.isOpen();
    };

    void setFramerateLimit(unsigned int limit) final
    {
      m_window.setFramerateLimit(limit);
    };

    IRenderer& getRenderer() final
    {
      return *this;
    };

    void draw(const sf::Drawable& drawable)
    {
      m_window.draw(drawable);
    };

    sf::RenderWindow& getWindow()
    {
      return m_window;
    };

   private:
    sf::RenderWindow m_window;
  };
} // namespace GameEngine::Gfx::Sfml
