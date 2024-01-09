//
// Created by Alexandre Decobert on 17/12/2023.
//

#pragma once

#include "gameEngine/component/Gravity.hpp"
#include "gameEngine/component/Transform.hpp"
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/component/ComponentManager.hpp"
#include "gameEngine/ecs/system/System.hpp"
#include "gameEngine/gfx/sfml/SfmlDisplay.hpp"

#include <SFML/Graphics.hpp>
#include <memory>

namespace GameEngine::System
{

  class Animation : public GameEngine::ECS::System {
   public:
    void update(GameEngine::ECS::Registry &, GameEngine::UI::WindowContext &)
    {
    }
  };

} // namespace GameEngine::System
