//
// Created by raphael on 11/28/23.
//

#pragma once
#include "ecs/entity/Entity.hpp"

class IComponentArray {
public:
  virtual ~IComponentArray() = default;
  virtual void entityDestroyed(Entity entity) = 0;
};
