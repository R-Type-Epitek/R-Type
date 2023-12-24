//
// Created by raphael on 11/28/23.
//

#pragma once

#include "ecs/entity/Entity.hpp"
#include <set>

class System {
public:
  std::set<Entity> m_entities {};
};
