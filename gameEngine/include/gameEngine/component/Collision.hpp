//
// Created by raphael on 1/4/24.
//

#pragma once
#include <SFML/Graphics/RectangleShape.hpp>

namespace ComponentRType
{

  /// \brief A component representing if a entity is clickable.
  struct Collision {
    size_t mask = 0;
  };
} // namespace ComponentRType
