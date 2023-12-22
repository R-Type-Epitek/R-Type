//
// Created by raphael on 12/22/23.
//

#pragma once

#include "gameEngine/UI/Window.hpp"
#include "gameEngine/component/Sprite.hpp"
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/system/System.hpp"
#include <iostream>

namespace GameEngine::System {

class Renderer : public GameEngine::ECS::System {
 public:
  void update(GameEngine::ECS::Registry& registry, GameEngine::UI::WindowContext& ctx) {
    auto& componentManager = registry.getComponentManager();
    std::cout << "Renderer entity count:" << m_entities.size() << std::endl;
    //    for (auto const& entity : m_entities) {
    //      auto& spriteC = componentManager->getComponent<ComponentRType::Sprite>(entity);
    //      std::cout << spriteC.width << std::endl;
    //      //      ctx.window.draw(spriteC.sprite);
    //    }
  }
};

}  // namespace GameEngine::System
