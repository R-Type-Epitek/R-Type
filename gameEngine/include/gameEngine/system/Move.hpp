//
// Created by raphael on 1/4/24.
//

#pragma once

#include "gameEngine/component/Gravity.hpp"
#include "gameEngine/component/Transform.hpp"
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
        auto& positionC = componentManager->getComponent<ComponentRType::Position>(entity);
        spriteC.sprite.move(positionC.position);
      }
    }
  };
} // namespace GameEngine::System
