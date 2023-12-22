//
// Created by Alexandre Decobert on 17/12/2023.
//
#pragma once
#include <optional>
#include <string>
#include "ecs/TextureManager.hpp"
#include <SFML/Graphics.hpp>
#include "constants/constants.hpp"

namespace ComponentRType {
/// \brief A component structure for handling SFML sprites and textures.
struct Sprite {
  std::string m_texturePath;
  sf::IntRect m_intRect;
  sf::Sprite m_object;

  /// \brief Constructs a new Sprite object with default values.
  ///
  /// Initializes the texture path to "unknown.png" and sets the texture of the
  /// sprite object. If an IntRect is provided, it sets the texture rectangle of the sprite.
  Sprite() : m_texturePath("unknown.png"), m_intRect() {
    m_object.setTexture(*TextureManager::getInstance().getTexture(m_texturePath));
    if (m_intRect != sf::IntRect()) {
      m_object.setTextureRect(m_intRect);
    }
  }

  /// \brief Sets the texture of the sprite.
  /// \param sf::Texture& - Reference to an SFML Texture.
  void setTexture(std::string& texturePath) {
    m_object.setTexture(*TextureManager::getInstance().getTexture(m_texturePath));
  }
};
}
