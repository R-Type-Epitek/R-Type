//
// Created by raphael on 12/22/23.
//

#pragma once

#include "gameEngine/UI/Window.hpp"
#include "gameEngine/component/Sprite.hpp"
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/system/System.hpp"
#include "IUpdateSystem.hpp"

namespace GameEngine::System
{

  class Renderer
    : public GameEngine::ECS::System
    , public IUpdateSystem {
   public:
    void update(GameEngine::ECS::Registry& registry, GameEngine::UI::WindowContext& ctx) final
    {
      auto& componentManager = registry.getComponentManager();

      for (auto const& entity : m_entities) {
        auto& spriteC = componentManager->getComponent<ComponentRType::Sprite>(entity);
        ctx.window.draw(spriteC.sprite);
      }
    }
  };

} // namespace GameEngine::System
