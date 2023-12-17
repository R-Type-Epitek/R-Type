//
// Created by Alexandre Decobert on 17/12/2023.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "ecs/Mediator.hpp"
#include "component/Transform.hpp"
#include "component/Sprite.hpp"
#include "gfx/sfml/SfmlDisplay.hpp"
#include "component/Gravity.hpp"

namespace ComponentRType
{
  struct Animation {
    static void update(Mediator &mediator, sf::RenderWindow& window, std::vector<Entity> &entities, double delta)
    {
      for (auto const& entity : entities) {
        auto& sprite = mediator.getComponent<ComponentRType::Sprite>(entity);
        display(sprite.object);
      }
    }
  };
}
