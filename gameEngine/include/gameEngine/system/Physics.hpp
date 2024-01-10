//
// Created by Alexandre Decobert on 16/12/2023.
//

#pragma once

#include "gameEngine/component/Gravity.hpp"
#include "gameEngine/component/Transform.hpp"
#include "gameEngine/component/Position.hpp"
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/system/System.hpp"
#include "gameEngine/ecs/system/RegistryHolder.hpp"
#include "gameEngine/event/IEventListener.hpp"
#include "gameEngine/event/Events.hpp"
#include "gameEngine/event/IEvent.hpp"

namespace GameEngine::System
{

  class Physics
    : public GameEngine::ECS::System
    , public GameEngine::ECS::RegistryHolder
    , public Event::IEventListener {
   public:
    void update(GameEngine::ECS::Registry& registry)
    {
      auto& componentManager = registry.getComponentManager();

      for (auto const& entity : m_entities) {
        auto& compId = componentManager->getComponent<ComponentRType::Position>(entity);
        (void)compId;
      }
    }

    void handleEvent(const Event::IEvent& eventRaw) final
    {
      auto& componentManager = getEcsRegistry().getComponentManager();
      auto event = dynamic_cast<const Event::EventCollision&>(eventRaw);

      auto transformEntityA = componentManager->getComponent<ComponentRType::Transform>(event.entityA);
      auto transformEntityB = componentManager->getComponent<ComponentRType::Transform>(event.entityB);

      transformEntityA.movement = {0, 0};
      transformEntityB.movement = {0, 0};
    }
  };
} // namespace GameEngine::System
