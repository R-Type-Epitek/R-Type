//
// Created by sgLeopold on 12/01/24.
//

#pragma once

#include "gameEngine/ecs/system/RegistryHolder.hpp"
#include "gameEngine/component/Parallax.hpp"
#include "gameEngine/component/Displayable.hpp"
#include "gameEngine/component/Position.hpp"

#include <memory>

namespace GameEngine::System
{
  class Parallax
    : public GameEngine::ECS::System
    , public GameEngine::ECS::RegistryHolder {
   public:
    void update()
    {
      auto& componentManager = getEcsRegistry().getComponentManager();

      for (auto& entity : m_entities) {
        auto& displayable = componentManager->getComponent<ComponentRType::Displayable>(entity);
        auto position = componentManager->getComponent<ComponentRType::Position>(entity).position;
        const auto rect = displayable.sprite.getTextureRect();
        
        if (position.x <= -(rect.width - 1920)) {
          displayable.sprite.setPosition(0, 0);
        }
      }
    }
  };
} // Namespace GameEngine::System
