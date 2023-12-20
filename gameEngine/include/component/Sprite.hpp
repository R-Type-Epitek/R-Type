//
// Created by Alexandre Decobert on 17/12/2023.
//
#pragma once
#include <optional>
#include <string>
#include <SFML/Graphics.hpp>
#include "constants/constants.hpp"

namespace ComponentRType {
/// \brief A component structure for handling SFML sprites and textures.
struct Sprite {
  sf::Sprite object;
  sf::Texture* texture;

  /// \brief Default constructor, initializes texture pointer to nullptr.
  Sprite() : texture(nullptr) {}

  /// \brief Copy constructor.
  /// \param Sprite& - Reference to another Sprite object.
  Sprite(Sprite& other) : texture(other.texture) {
    if (texture) {
      object.setTexture(*texture);
    }
  }

  /// \brief Constructor with texture reference.
  /// \param sf::Texture& - Reference to an SFML Texture.
  Sprite(sf::Texture& tex) : texture(&tex) {
    object.setTexture(*texture);
  }

  /// \brief Copy assignment operator.
  /// \param Sprite& - Reference to another Sprite object.
  /// \return Sprite& - Reference to this Sprite object.
  Sprite& operator=(Sprite& other) {
    if (this != &other) {
      texture = other.texture;
      if (texture) {
        object.setTexture(*texture);
      }
    }
    return *this;
  }

  /// \brief Sets the texture of the sprite.
  /// \param sf::Texture& - Reference to an SFML Texture.
  void setTexture(sf::Texture& tex) {
    texture = &tex;
    object.setTexture(*texture);
  }

  /// \brief Applies the texture to the sprite object.
  void applyTexture() {
    object.setTexture(*texture);
  }
};
}
