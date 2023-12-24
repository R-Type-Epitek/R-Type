//
// Created by raphael on 11/28/23.
//

#pragma once
#include "gameEngine/ecs/entity/Entity.hpp"

namespace GameEngine::ECS {

class IComponentArray {
 public:
  virtual ~IComponentArray() = default;

  virtual void entityDestroyed(Entity entity) = 0;
  virtual bool hasEntity(Entity entity) = 0;
};

};  // namespace GameEngine::ECS