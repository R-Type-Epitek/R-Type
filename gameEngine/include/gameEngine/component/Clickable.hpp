//
// Created by Edouard on 1/4/24.
//

#pragma once
#include <SFML/Graphics/RectangleShape.hpp>

namespace ComponentRType
{

  /// \brief A component representing if a entity is clickable.
  struct Clickable {
    sf::RectangleShape rect;

    Clickable() = default;

    explicit Clickable(size_t x, size_t y, size_t w, size_t h) {
      rect.setPosition(x, y);
      rect.setSize(sf::Vector2f(w, h));
    }
  };
} // namespace ComponentRType
