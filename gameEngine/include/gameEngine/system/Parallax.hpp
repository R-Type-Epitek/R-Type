//
// Created by sgLeopold on 12/01/24.
//

#pragma once

#include <SFML/Graphics.hpp>
#include "gameEngine/ecs/system/System.hpp"

#include <memory>

namespace GameEngine::System
{
  class Parallax : public GameEngine::ECS::System {
    void update()
    {
      std::cout << "Parallax" << std::endl;
    }
  };
} // Namespace GameEngine::System