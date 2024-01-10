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
      for (auto const& entity : m_entities) {
        for (auto otherEntity : m_entities) {
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

      if (spriteC.sprite.getGlobalBounds().intersects(otherSpriteC.sprite.getGlobalBounds())) {
        eventRegistry.publish<Event::EntityCollision>(Event::EntityCollision {entity, otherEntity});
      } else if (
        spriteC.sprite.getPosition().x < 0 || spriteC.sprite.getPosition().x > 1920 ||
        spriteC.sprite.getPosition().y < 0 || spriteC.sprite.getPosition().y > 1080) {
        eventRegistry.publish<Event::EntityCollision>(Event::EntityCollision {entity, otherEntity});
      }
    }
  };
} // namespace GameEngine::System
