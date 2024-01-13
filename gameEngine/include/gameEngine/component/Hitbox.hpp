//
// Created by raphael on 1/4/24.
//

#pragma once
#include <SFML/Graphics/RectangleShape.hpp>

namespace ComponentRType
{

  /// \brief A component representing if a entity is clickable.
  struct Hitbox {
    Hitbox() = default;
    explicit Hitbox(int mask, sf::Vector2f size)
      : mask {mask}
      , shape(size)
    {
      shape.setFillColor(sf::Color::Transparent);
      shape.setOutlineColor(sf::Color::Red);
      shape.setOutlineThickness(1);
    }

    int mask = 0;
    sf::RectangleShape shape;
  };
} // namespace ComponentRType
