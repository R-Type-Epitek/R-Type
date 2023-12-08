//
// Created by raphael on 11/28/23.
//

#pragma once

#include <set>
#include "ecs/entity/Entity.hpp"

class System
{
public:
    std::set<Entity> m_entities{};
};
