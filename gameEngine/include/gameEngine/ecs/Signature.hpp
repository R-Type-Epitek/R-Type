//
// Created by raphael on 11/28/23.
//

#pragma once

#include "gameEngine/ecs/component/Component.hpp"

#include <bitset>

namespace GameEngine::ECS
{

  using Signature = std::bitset<MAX_COMPONENTS>;

}
