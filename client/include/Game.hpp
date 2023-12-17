//
// Created by Alexandre Decobert on 17/12/2023.
//

#pragma once

#include <SFML/Graphics.hpp>
#include "Controller.hpp"
#include "ecs/Mediator.hpp"
#include "component/Gravity.hpp"
#include "component/Transform.hpp"
#include "system/Physics.hpp"
#include <optional>

class Game {
 public:
  Game();
  ~Game();
  void run();
 private:
  sf::RenderWindow window;
  std::unique_ptr<Controller> controller;
  std::shared_ptr<Mediator> mediator;
  std::vector<Entity> entities;
};