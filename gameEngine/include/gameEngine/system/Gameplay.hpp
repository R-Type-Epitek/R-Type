//
// Created by sgLeopold on 14/01/2024.
//

#pragma once

#include "gameEngine/ecs/system/System.hpp"
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/entity/Entity.hpp"

namespace GameEngine::System
{
  class Gameplay
    : public GameEngine::ECS::System
    , public GameEngine::ECS::RegistryHolder {
   public:
    void update()
    {
      // auto &componentManager = getEcsRegistry().getComponentManager();
      // auto &health = componentManager->getComponent<ComponentRType::Health>();
      std::cout << "PLAYER HEALTH SYSTEM" << std::endl;
      // health.health -= 1;
      // if (health.health <= 0) {
      //   // entity.destroy();
      // }
    }
  };
} // namespace GameEngine::System