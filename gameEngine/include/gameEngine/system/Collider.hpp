//
// Created by raphael on 1/4/24.
//

#pragma once

#include "gameEngine/component/Gravity.hpp"
#include "gameEngine/component/Transform.hpp"
#include "gameEngine/component/Clickable.hpp"
#include "gameEngine/component/Displayable.hpp"
#include "gameEngine/component/Position.hpp"
#include "gameEngine/component/Hitbox.hpp"
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/system/System.hpp"
#include "gameEngine/ecs/system/RegistryHolder.hpp"
#include "gameEngine/event/EventRegistry.hpp"
#include "gameEngine/event/Events.hpp"

namespace GameEngine::System
{

  class Collider
    : public GameEngine::ECS::System
    , public GameEngine::ECS::RegistryHolder {
   public:
    void update(GameEngine::Event::EventRegistry& eventRegistry)
    {
      auto& componentManager = getEcsRegistry().getComponentManager();

      for (auto const& entity : m_entities) {
        checkMapBounding(eventRegistry, entity);
        auto entityMaskA = componentManager->getComponent<ComponentRType::Hitbox>(entity).mask;
        for (auto otherEntity : m_entities) {
          auto entityMaskB = componentManager->getComponent<ComponentRType::Hitbox>(otherEntity).mask;
          if (entity == otherEntity || entityMaskA != entityMaskB) {
            continue;
          }
          checkForCollision(eventRegistry, entity, otherEntity);
        }
      }
    }

    void checkForCollision(
      GameEngine::Event::EventRegistry& eventRegistry,
      const GameEngine::ECS::Entity& entity,
      const GameEngine::ECS::Entity& otherEntity)
    {
      auto& componentManager = getEcsRegistry().getComponentManager();
      auto& spriteC = componentManager->getComponent<ComponentRType::Displayable>(entity);
      auto& otherSpriteC = componentManager->getComponent<ComponentRType::Displayable>(otherEntity);
      auto& posA = componentManager->getComponent<ComponentRType::Position>(entity);

      if (spriteC.sprite.getGlobalBounds().intersects(otherSpriteC.sprite.getGlobalBounds())) {
        posA.isValid = false;
        eventRegistry.publish<Event::EntityCollision>(Event::EntityCollision {entity, otherEntity});
      } else {
        posA.isValid = true;
      }
    }

    void checkMapBounding(
      GameEngine::Event::EventRegistry& eventRegistry,
      const GameEngine::ECS::Entity& entity)
    {
      auto& componentManager = getEcsRegistry().getComponentManager();
      auto& spriteC = componentManager->getComponent<ComponentRType::Displayable>(entity);
      auto& posA = componentManager->getComponent<ComponentRType::Position>(entity);
      sf::FloatRect globalBounds = spriteC.sprite.getGlobalBounds();

      if (
        globalBounds.left < 0 || globalBounds.left + globalBounds.width > 1920 || globalBounds.top < 0 ||
        globalBounds.top + globalBounds.height > 1080) {
        posA.isValid = false;
        eventRegistry.publish<Event::EntityCollision>(Event::EntityCollision {entity, entity});
      } else {
        posA.isValid = true;
      }
    }
  };
} // namespace GameEngine::System
