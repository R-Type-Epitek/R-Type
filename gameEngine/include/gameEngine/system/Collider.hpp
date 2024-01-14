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
      for (auto const& entity : m_entities) {
        for (auto otherEntity : m_entities) {
          if (entity == otherEntity) {
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
      if (!m_entities.contains(otherEntity) && !m_entities.contains(entity)) {
        return;
      }
      auto& componentManager = getEcsRegistry().getComponentManager();
      const auto globalBounds =
        componentManager->getComponent<ComponentRType::Displayable>(entity).sprite.getGlobalBounds();
      const auto globalBoundsOther =
        componentManager->getComponent<ComponentRType::Displayable>(otherEntity).sprite.getGlobalBounds();

      //      Check collision AABB
      if (globalBounds.intersects(globalBoundsOther)) {
        int const mask = componentManager->getComponent<ComponentRType::Hitbox>(entity).mask;
        int const maskOther = componentManager->getComponent<ComponentRType::Hitbox>(otherEntity).mask;
        eventRegistry.publish<Event::EntityCollision>(
          Event::EntityCollision {entity, otherEntity, mask, maskOther});
      }
      //      Check map bounds
      int const mask = componentManager->getComponent<ComponentRType::Hitbox>(entity).mask;
      if (
        mask != 0 &&
        (globalBounds.left < 0 || globalBounds.left + globalBounds.width > 1920 || globalBounds.top < 0 ||
         globalBounds.top + globalBounds.height > 1080)) {
        eventRegistry.publish<Event::EntityCollision>(Event::EntityCollision {entity, 666, mask, -1});
      }
    }
  };
} // namespace GameEngine::System
