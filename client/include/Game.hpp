//
// Created by Alexandre Decobert on 17/12/2023.
//

#pragma once

#include "Controller.hpp"
#include "component/Gravity.hpp"
#include "component/Transform.hpp"
#include "ecs/Mediator.hpp"
#include "gameEngine/system/Physics.hpp"
#include <SFML/Graphics.hpp>
#include <optional>

class Game : Controller {
 public:
  Game();
  ~Game();
  void run();

 private:
  void initPlayer(sf::RenderWindow& window);
  sf::RenderWindow window;
};
