//
// Created by raphael on 1/4/24.
//

#pragma once

#include "gameEngine/component/Gravity.hpp"
#include "gameEngine/component/Transform.hpp"
#include "gameEngine/component/Clickable.hpp"
#include "gameEngine/component/Displayable.hpp"
#include "gameEngine/component/Position.hpp"
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/system/System.hpp"
#include "IUpdateSystem.hpp"

namespace GameEngine::System
{

  class Move : public GameEngine::ECS::System {
   public:
    void update(GameEngine::ECS::Registry& registry)
    {
      auto& componentManager = registry.getComponentManager();

      for (auto const& entity : m_entities) {
        auto& spriteC = componentManager->getComponent<ComponentRType::Displayable>(entity);
        auto& transform = componentManager->getComponent<ComponentRType::Transform>(entity);
        auto& position = componentManager->getComponent<ComponentRType::Position>(entity);

        position.position += transform.movement;
        spriteC.sprite.move(transform.movement);
        position.position = spriteC.sprite.getPosition();
        position.latestPosition = position.position;
      }
    }

    void updateClient(GameEngine::ECS::Registry& registry)
    {
      auto& componentManager = registry.getComponentManager();

      for (auto const& entity : m_entities) {
        auto& spriteC = componentManager->getComponent<ComponentRType::Displayable>(entity);
        auto& transform = componentManager->getComponent<ComponentRType::Transform>(entity);
        auto& position = componentManager->getComponent<ComponentRType::Position>(entity);

        if (registry.hasComponent<ComponentRType::Clickable>(entity)) {
          spriteC.sprite.setPosition(position.position);
        }
        spriteC.sprite.move(transform.movement);
      }
    }
  };
} // namespace GameEngine::System
