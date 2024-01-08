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

  class Collider : public GameEngine::ECS::System {
   public:
    void update(GameEngine::ECS::Registry& registry)
    {
      for (auto const& entity : m_entities) {
        for (auto otherEntity : m_entities) {
          checkForCollision(registry, entity, otherEntity);
        }
      }
    }

    void checkForCollision(
      GameEngine::ECS::Registry& registry,
      const GameEngine::ECS::Entity& entity,
      const GameEngine::ECS::Entity& otherEntity)
    {
      auto& componentManager = registry.getComponentManager();

      auto& spriteC = componentManager->getComponent<ComponentRType::Displayable>(entity);
      auto& transform = componentManager->getComponent<ComponentRType::Transform>(entity);
      auto& position = componentManager->getComponent<ComponentRType::Position>(entity);

      auto& otherSpriteC = componentManager->getComponent<ComponentRType::Displayable>(otherEntity);
      auto& otherTransform = componentManager->getComponent<ComponentRType::Transform>(otherEntity);
      auto& otherPosition = componentManager->getComponent<ComponentRType::Position>(otherEntity);

      if (spriteC.sprite.getGlobalBounds().intersects(otherSpriteC.sprite.getGlobalBounds())) {
        position.position = position.latestPosition;
        otherPosition.position = otherPosition.latestPosition;
        spriteC.sprite.setPosition(position.position);
        transform.movement = sf::Vector2f(0, 0);
        otherTransform.movement = sf::Vector2f(0, 0);
      }
    }
  };
} // namespace GameEngine::System
