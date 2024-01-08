//
// Created by raphael on 11/28/23.
//

#pragma once

#include "gameEngine/ecs/entity/Entity.hpp"
#include <set>

namespace GameEngine::ECS
{
  class System {
   public:
    virtual ~System() = default;

    std::set<Entity> m_entities {};
  };

} // namespace GameEngine::ECS
