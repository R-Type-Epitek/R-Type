//
// Created by raphael on 12/22/23.
//

#pragma once

#include "gameEngine/UI/Window.hpp"
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/system/System.hpp"
#include "IUpdateSystem.hpp"

namespace GameEngine::System
{

  class Keyboard : public GameEngine::ECS::System {
   public:
    void update(GameEngine::ECS::Registry &, GameEngine::UI::WindowContext &) {

    };
  };
} // namespace GameEngine::System
