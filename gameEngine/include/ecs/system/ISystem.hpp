//
// Created by Alexandre Decobert on 17/12/2023.
//

#pragma once

#include <SFML/Graphics.hpp>
#include "ecs/Mediator.hpp"
#include <set>
#include <memory>

class ISystem {
 public:
  virtual ~ISystem() = default;
  virtual void update(std::shared_ptr<ComponentManager>& component_manager, Entity entity, sf::RenderWindow& window) = 0;
  std::set<Entity> m_entities{};
};