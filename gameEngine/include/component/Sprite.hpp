//
// Created by Alexandre Decobert on 17/12/2023.
//
#pragma once
#include <optional>

#include <string>
#include <SFML/Graphics.hpp>
#include "constants/constants.hpp"

namespace ComponentRType {
struct Sprite
{
        public:
  Sprite() = default;
  Sprite(const Sprite&) = default;
  Sprite(Sprite&&) noexcept = default;
  ~Sprite() = default;

  Sprite& operator=(const Sprite&) = default;
  Sprite& operator=(Sprite&&) noexcept = default;

  sf::Sprite object;

  void setTexture(const std::string& path = "assets/unknown.png", sf::Vector2f scale = {1, 1})
  {
    sf::Texture texture;
    if (!texture.loadFromFile(path)) {
      std::cerr << "Texture not found" << std::endl;
    }
    object.setTexture(texture);
    object.setScale(scale);
  }
};
}