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
      eventRegistry.subscribeLambda<Event::EntityCollision>(([this](const Event::IEvent& eventRaw) {
        handleCollision(eventRaw);
      }));
    }

    void update()
    {
      auto& componentManager = getEcsRegistry().getComponentManager();

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

    void updateClient()
    {
      auto& componentManager = getEcsRegistry().getComponentManager();

      for (auto const& entity : m_entities) {
        auto& spriteC = componentManager->getComponent<ComponentRType::Displayable>(entity);
        auto& transform = componentManager->getComponent<ComponentRType::Transform>(entity);
        auto& position = componentManager->getComponent<ComponentRType::Position>(entity);

        if (getEcsRegistry().hasComponent<ComponentRType::Clickable>(entity)) {
          spriteC.sprite.setPosition(position.position);
        }
        spriteC.sprite.move(transform.movement);
      }
    }

    void handleCollision(const Event::IEvent& eventRaw)
    {
      auto& componentManager = getEcsRegistry().getComponentManager();
      auto event = dynamic_cast<const Event::EntityCollision&>(eventRaw);

      auto transformEntityA = componentManager->getComponent<ComponentRType::Transform>(event.entityA);
      auto transformEntityB = componentManager->getComponent<ComponentRType::Transform>(event.entityB);

      transformEntityA.movement = {0, 0};
      transformEntityB.movement = {0, 0};
    }
  };
} // namespace GameEngine::System
