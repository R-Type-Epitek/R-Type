//
// Created by Alexandre Decobert on 17/12/2023.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "ecs/Mediator.hpp"
#include "ecs/system/System.hpp"
#include "component/Transform.hpp"
#include "component/Sprite.hpp"
#include "gfx/sfml/SfmlDisplay.hpp"
#include "component/Gravity.hpp"

struct Animation : System {
  void update(std::shared_ptr<ComponentManager> component_manager, Entity entity, sf::RenderWindow& window)
  {
  }
};
