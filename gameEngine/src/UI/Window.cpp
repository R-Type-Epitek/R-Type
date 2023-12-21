//
// Created by raphael on 12/20/23.
//

#include "gameEngine/UI/Window.hpp"
#include <functional>
#include <utility>

namespace GameEngine::UI {
Window::Window(int width, int height, std::string& name, float screenRatio)
    : m_windowContext{
          .window = sf::RenderWindow(sf::VideoMode(width, height), name),
          .event = sf::Event(),
          .deltaClock = sf::Clock(),
          .screenRatio = screenRatio,
      } {}

void Window::setFrameRate(int limit) { m_windowContext.window.setFramerateLimit(limit); }

void Window::subscribeEvent(std::function<void(WindowContext&)> closure) { m_closureEvent = std::move(closure); }
void Window::unsubscribeEvent() { m_closureEvent = {}; }

void Window::subscribeUpdate(std::function<void(WindowContext&)> closure) { m_closureUpdate = std::move(closure); };
void Window::unsubscribeUpdate() { m_closureUpdate = {}; };

void Window::subscribeDisplay(std::function<void(WindowContext&)> closure) { m_closureDisplay = std::move(closure); };
void Window::unsubscribeDisplay() { m_closureDisplay = {}; };

void Window::launch() {
  while (m_windowContext.window.isOpen()) {
    handleEvent();
    invokeClosure(m_closureUpdate);
    display();
  }
}

void Window::handleEvent() {
  while (m_windowContext.window.pollEvent(m_windowContext.event)) {
    switch (m_windowContext.event.type) {
      case sf::Event::Closed:
        return m_windowContext.window.close();
      case sf::Event::Resized:
        return this->onResize();
      default:
        invokeClosure(m_closureEvent);
    }
  }
}

void Window::onResize() {
  float targetRatio = m_windowContext.screenRatio;
  float currentRatio = static_cast<float>(m_windowContext.window.getSize().x) / m_windowContext.window.getSize().y;
  int newWidth = 0;
  int newHeight = 0;

  if (currentRatio > targetRatio) {
    newWidth = static_cast<int>(m_windowContext.window.getSize().y * targetRatio);
    newHeight = m_windowContext.window.getSize().y;
  } else {
    newWidth = m_windowContext.window.getSize().x;
    newHeight = static_cast<int>(m_windowContext.window.getSize().x / targetRatio);
  }

  int offsetX = static_cast<int>(m_windowContext.window.getSize().x - newWidth) / 2;
  int offsetY = static_cast<int>(m_windowContext.window.getSize().y - newHeight) / 2;

  sf::View view(sf::FloatRect(0.f, 0.f, static_cast<float>(newWidth), static_cast<float>(newHeight)));
  m_windowContext.window.setView(view);
  m_windowContext.window.setPosition(sf::Vector2i(offsetX, offsetY));
}

void Window::display() {
  m_windowContext.window.clear();
  invokeClosure(m_closureDisplay);
  m_windowContext.window.display();
}

void Window::invokeClosure(ClosureType closure) {
  if (closure) {
    closure(m_windowContext);
  }
};

};  // namespace GameEngine::UI
