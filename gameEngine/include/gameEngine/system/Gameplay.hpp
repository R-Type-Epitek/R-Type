//
// Created by sgLeopold on 14/01/2024.
//

#pragma once

#include "gameEngine/ecs/system/System.hpp"
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/entity/Entity.hpp"
#include "gameEngine/event/Events.hpp"
#include "gameEngine/event/EventRegistry.hpp"
#include "gameEngine/event/IEvent.hpp"
#include "gameEngine/event/IEventBindable.hpp"

namespace GameEngine::System
{
  class Gameplay
    : public GameEngine::ECS::System
    , public GameEngine::ECS::RegistryHolder
    , public Event::IEventBindable {
   public:
    void bindEvent(Event::EventRegistry& eventRegistry) final
    {
      eventRegistry.subscribeLambda<Event::EntityHit>(
        ([this](const Event::IEvent& eventRaw) { hitEntity(eventRaw); }));
    }

    void update()
    {
      //      auto& componentManager = getEcsRegistry().getComponentManager();
      //
      //      for (auto const& entity : m_entities) {
      //        auto& spriteC = componentManager->getComponent<ComponentRType::Displayable>(entity);
      //      }
    }

    void hitEntity(const Event::IEvent& eventRaw)
    {
      auto& componentManager = getEcsRegistry().getComponentManager();
      auto event = dynamic_cast<const Event::EntityHit&>(eventRaw);

      if (
        componentManager->hasComponent<ComponentRType::Health>(event.entityA) &&
        componentManager->hasComponent<ComponentRType::Health>(event.entityB)) {
        auto& healthA = componentManager->getComponent<ComponentRType::Health>(event.entityA);
        auto& healthB = componentManager->getComponent<ComponentRType::Health>(event.entityB);

        healthA.value -= healthB.damage;
        if (healthA.value <= 0) {
          healthA.value = 0;
          getEventRegistry().publish<Event::DestroyEntity>(Event::DestroyEntity {event.entityA});
        }
      }
    }
  };
} // namespace GameEngine::System
