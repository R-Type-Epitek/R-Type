//
// Created by raphael on 12/20/23.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <string>

namespace GameEngine::UI {
#define DEFAULT_RATIO (16.f / 9.f)

struct WindowContext {
  sf::RenderWindow window;
  sf::Event event;
  sf::Clock deltaClock;
  float screenRatio;
};

class Window {
 public:
  Window(int width, int height, std::string& name, float screenRatio = DEFAULT_RATIO);

  void setFrameRate(int);

  void subscribeEvent(std::function<void(WindowContext&)>& closure);
  void unsubscribeEvent();

  void subscribeUpdate(std::function<void(WindowContext&)>& closure);
  void unsubscribeUpdate();

  void subscribeDisplay(std::function<void(WindowContext&)>& closure);
  void unsubscribeDisplay();

  void launch();
  void display();

 private:
  void handleEvent();
  void onResize();

  WindowContext m_windowContext;
  std::function<void(WindowContext&)> m_closureEvent;
  std::function<void(WindowContext&)> m_closureUpdate;
  std::function<void(WindowContext&)> m_closureDisplay;
};

}  // namespace GameEngine::UI
