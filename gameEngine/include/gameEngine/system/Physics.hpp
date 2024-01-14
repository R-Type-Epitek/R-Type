//
// Created by Alexandre Decobert on 16/12/2023.
//

#pragma once

#include "gameEngine/component/Gravity.hpp"
#include "gameEngine/component/Transform.hpp"
#include "gameEngine/component/Position.hpp"
#include "gameEngine/component/Clickable.hpp"
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/system/System.hpp"
#include "gameEngine/ecs/system/RegistryHolder.hpp"
#include "gameEngine/event/IEventBindable.hpp"
#include "gameEngine/event/Events.hpp"
#include "gameEngine/event/IEvent.hpp"

namespace GameEngine::System
{

  class Physics
    : public GameEngine::ECS::System
    , public GameEngine::ECS::RegistryHolder
    , public Event::IEventBindable {
   public:
    void bindEvent(Event::EventRegistry& eventRegistry) final
    {
      eventRegistry.subscribeLambda<Event::EntityCollision>(
        ([this](const Event::IEvent& eventRaw) { handleCollision(eventRaw); }));
    }

    void update()
    {
      auto& componentManager = getEcsRegistry().getComponentManager();

      for (auto const& entity : m_entities) {
        auto& spriteC = componentManager->getComponent<ComponentRType::Displayable>(entity);
        auto& transform = componentManager->getComponent<ComponentRType::Transform>(entity);
        auto& position = componentManager->getComponent<ComponentRType::Position>(entity);

        if (!position.isValid) {
          position.position = position.latestValidPosition;
          spriteC.sprite.setPosition(position.position);
          position.isValid = true;
        } else {
          position.position = spriteC.sprite.getPosition();
          spriteC.sprite.move(transform.movement);
          position.latestValidPosition = position.position;
        }
      }
    }

    void updateClient()
    {
      auto& componentManager = getEcsRegistry().getComponentManager();

      for (auto const& entity : m_entities) {
        auto& spriteC = componentManager->getComponent<ComponentRType::Displayable>(entity);
        auto& position = componentManager->getComponent<ComponentRType::Position>(entity);

        spriteC.sprite.setPosition(position.position);
      }
    }

    void handleCollision(const Event::IEvent& eventRaw)
    {
      auto& eventRegistry = getEventRegistry();
      auto event = dynamic_cast<const Event::EntityCollision&>(eventRaw);

      // Collision between enemy and bullet
      if (event.maskA == 0 && event.maskB == 6) {
        eventRegistry.publish<Event::EntityHit>(
          Event::EntityHit {event.entityA, event.entityA, event.maskA, event.maskB});
        eventRegistry.publish<Event::DestroyEntity>(Event::DestroyEntity {event.entityA});
      }
      //      // Collision between enemy and Player
      //      if ((event.maskA == 6 && event.maskB == 1)) {
      //        eventRegistry.publish<Event::EntityHit>(
      //          Event::EntityHit {event.entityA, event.entityA, event.maskA, event.maskB});
      //      }
      // Collision between bullet and itself or walls
      if ((event.maskA == 6 && event.maskB == 6) || (event.maskA == 6 && event.maskB == -1)) {
        eventRegistry.publish<Event::DestroyEntity>(Event::DestroyEntity {event.entityA});
      }

      // Check for collision to stop velocity
      if (event.maskA != -1 && event.maskB != -1 && event.maskA != event.maskB) {
        return;
      }
      auto& componentManager = getEcsRegistry().getComponentManager();
      auto& transformA = componentManager->getComponent<ComponentRType::Transform>(event.entityA);
      auto& position = componentManager->getComponent<ComponentRType::Position>(event.entityA);

      position.isValid = false;
      transformA.movement = {0, 0};
    }
  };
} // namespace GameEngine::System
