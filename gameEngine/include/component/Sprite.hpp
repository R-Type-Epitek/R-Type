//
// Created by Alexandre Decobert on 17/12/2023.
//
#pragma once
#include <optional>
#include <string>
#include <SFML/Graphics.hpp>
#include "constants/constants.hpp"

namespace ComponentRType {
struct Sprite {
  sf::Sprite object;
  sf::Texture* texture;

  Sprite() : texture(nullptr) {}

  Sprite(Sprite& other) : texture(other.texture) {
    if (texture) {
      object.setTexture(*texture);
    }
  }

  Sprite(sf::Texture& tex) : texture(&tex) {
    object.setTexture(*texture);
  }

  Sprite& operator=(Sprite& other) {
    if (this != &other) {
      texture = other.texture;
      if (texture) {
        object.setTexture(*texture);
      }
    }
    return *this;
  }

  void setTexture(sf::Texture& tex) {
    texture = &tex;
    object.setTexture(*texture);
  }

  void applyTexture() {
    object.setTexture(*texture);
  }
};
}
