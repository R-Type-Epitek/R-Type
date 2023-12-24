//
// Created by Alexandre Decobert on 17/12/2023.
//
#pragma once

#include <SFML/Graphics.hpp>
#include <variant>

using Vec3 = int;

namespace ge
{
  struct Position {
    float x = 0;
    float y = 0;

    Position() = default;

    Position(float x, float y)
      : x(x)
      , y(y) {};
  };

  using VectorVariant = std::variant<sf::Vector2f, sf::Vector2i, sf::Vector2u>;
} // namespace ge