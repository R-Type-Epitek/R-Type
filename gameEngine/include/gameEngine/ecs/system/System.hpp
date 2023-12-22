//
// Created by raphael on 11/28/23.
//

#pragma once

#include "gameEngine/ecs/component/ComponentManager.hpp"
#include "gameEngine/ecs/entity/Entity.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include <set>

namespace GameEngine::ECS {
class System {
 public:
  virtual ~System() = default;
  virtual void update(std::shared_ptr<ComponentManager>& component_manager, Entity entity,
                      sf::RenderWindow& window) = 0;
  std::set<Entity> m_entities{};
};

}  // namespace GameEngine::ECS
