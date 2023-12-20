//
// Created by raphael on 12/20/23.
//

#include "UI/Window.hpp"
#include

namespace GameEngine::UI {
Window::Window(int width, int height, std::string& name, float screenRatio)
    : m_windowContext{
          .window = sf::RenderWindow(sf::VideoMode(width, height), name),
          .event = sf::Event(),
          .deltaClock = sf::Clock(),
          .screenRatio = screenRatio,
      } {}

void Window::setFrameRate(int limit) { m_windowContext.window.setFramerateLimit(limit); }

void Window::subscribeEvent(std::function<void(WindowContext&)>& closure) { m_closureEvent = closure; }
void Window::unsubscribeEvent() { m_closureEvent = {}; }

void Window::subscribeUpdate(std::function<void(WindowContext&)>& closure) { m_closureEvent = closure; };
void Window::unsubscribeUpdate() { m_closureUpdate = {}; };

void Window::subscribeDisplay(std::function<void(WindowContext&)>& closure) { m_closureDisplay = closure; };
void Window::unsubscribeDisplay() { m_closureDisplay = {}; };

void Window::launch() {
#pragma unroll
  while (m_windowContext.window.isOpen()) {
    m_closureUpdate(m_windowContext);
    this->handleEvent();
  }
}

void Window::handleEvent() {
#pragma unroll
  while (m_windowContext.window.pollEvent(m_windowContext.event)) {
    switch (m_windowContext.event.type) {
      case sf::Event::Closed:
        return m_windowContext.window.close();
      case sf::Event::Resized:
        return this->onResize();
      default:
        break;
    }
    m_closureEvent(m_windowContext);
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
  m_closureDisplay(m_windowContext);
  m_windowContext.window.display();
};

};  // namespace GameEngine::UI
