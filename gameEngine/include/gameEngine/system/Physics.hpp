//
// Created by Alexandre Decobert on 16/12/2023.
//

#pragma once

#include "gameEngine/component/Gravity.hpp"
#include "gameEngine/component/Transform.hpp"
#include "gameEngine/component/Position.hpp"
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/system/System.hpp"

namespace GameEngine::System
{

  class Physics : public GameEngine::ECS::System {
   public:
    void update(GameEngine::ECS::Registry& registry)
    {
      auto& componentManager = registry.getComponentManager();

      for (auto const& entity : m_entities) {
        auto& compId = componentManager->getComponent<ComponentRType::Position>(entity);
        (void)compId;
      }
    }
  };
} // namespace GameEngine::System
