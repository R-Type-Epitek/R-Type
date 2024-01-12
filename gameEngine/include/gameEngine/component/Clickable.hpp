//
// Created by Edouard on 1/4/24.
//

#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <functional>

namespace ComponentRType
{

  /// \brief A component representing if a entity is clickable.
  struct Clickable {
    Clickable() = default;

    explicit Clickable(std::function<void()> callback)
      : callback(callback)
    {
    }

    std::function<void()> callback = []() {
    };
    ;
  };
} // namespace ComponentRType
