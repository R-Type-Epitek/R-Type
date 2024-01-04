//
// Created by raphael on 1/3/24.
//

#pragma once
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/UI/Window.hpp"
#include "gameEngine/component/Sprite.hpp"
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/system/System.hpp"

namespace GameEngine::System
{
  class IUpdateSystem {
   public:
    ~IUpdateSystem() = default;

    virtual void update(GameEngine::ECS::Registry& registry, GameEngine::UI::WindowContext& ctx) = 0;
  };

} // namespace GameEngine::System;
