//
// Created by Alexandre Decobert on 15/12/2023.
//

#pragma once

#include "constants/constants.hpp"
#include <utility>

using Vec3 = int;

namespace ComponentRType
{
  /// \brief A component representing the transformation properties of an entity.
  struct Transform {
    ge::Position position;
    Vec3 rotation = 0;
    Vec3 speed = 1;
    Vec3 scale = 1;
  };
} // namespace ComponentRType