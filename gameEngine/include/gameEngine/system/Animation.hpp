//
// Created by Alexandre Decobert on 17/12/2023.
//

#pragma once

#include "gameEngine/component/Gravity.hpp"
#include "gameEngine/component/Transform.hpp"
#include "gameEngine/ecs/system/RegistryHolder.hpp"
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/component/ComponentManager.hpp"
#include "gameEngine/ecs/system/System.hpp"
#include "gameEngine/UI/Window.hpp"

#include <SFML/Graphics.hpp>
#include <memory>

namespace GameEngine::System
{

  class Animation
    : public GameEngine::ECS::System
    , public GameEngine::ECS::RegistryHolder {
   public:
    void update(int df)
    {
      (void)df;
    }
  };

} // namespace GameEngine::System
