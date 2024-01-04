//
// Created by Alexandre Decobert on 16/12/2023.
//

#pragma once

#include "gameEngine/component/Gravity.hpp"
#include "gameEngine/component/Transform.hpp"
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/system/System.hpp"
#include "IUpdateSystem.hpp"

namespace GameEngine::System
{

  class Physics
    : public GameEngine::ECS::System
    , public IUpdateSystem {
   public:
    void update(GameEngine::ECS::Registry &, GameEngine::UI::WindowContext &) final
    {
      return;
    }
  };
} // namespace GameEngine::System
