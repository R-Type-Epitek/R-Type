//
// Created by raphael on 12/20/23.
//

#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window.hpp>
#include <functional>
#include <string>

namespace GameEngine::UI {

struct WindowContext {
  sf::RenderWindow window;
  sf::Event event;
  sf::Clock deltaClock;
  float screenRatio;
};

class Window {
 public:
  using ClosureType = std::function<void(WindowContext&)>;

  Window(int width, int height, std::string& name, float screenRatio);

  void setFrameRate(int);

  void subscribeEvent(std::function<void(WindowContext&)> closure);
  void unsubscribeEvent();

  void subscribeUpdate(std::function<void(WindowContext&)> closure);
  void unsubscribeUpdate();

  void subscribeDisplay(std::function<void(WindowContext&)> closure);
  void unsubscribeDisplay();

  void launch();
  void display();

 private:
  void handleEvent();
  void onResize();
  void invokeClosure(ClosureType closure);

  WindowContext m_windowContext;
  ClosureType m_closureEvent;
  ClosureType m_closureUpdate;
  ClosureType m_closureDisplay;
};

}  // namespace GameEngine::UI
