//
// Created by Alexandre Decobert on 15/12/2023.
//

#pragma once

#include "constants/constants.hpp"
#include <utility>

using Vec3 = int;

namespace ComponentRType {

struct Transform {
  ge::Position position;
  Vec3 rotation = 0;
  Vec3 speed = 0;
  Vec3 scale = 1;
};
}