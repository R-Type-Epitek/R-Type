//
// Created by Alexandre Decobert on 17/12/2023.
//

#pragma once
#include "gameEngine/asset/AssetManager.hpp"

#include <SFML/Graphics.hpp>
#include <string>

namespace ComponentRType
{

  struct Sprite {
    sf::Sprite sprite;

    Sprite()
    {
      sprite.setTexture(GET_TEXTURE(DEFAULT_TEXTURE));
    }

    Sprite(sf::Texture& texture)
    {
      sprite.setTexture(texture);
    }

    Sprite(sf::Texture& texture, sf::IntRect const& rect)
    {
      sprite.setTexture(texture);
      if (rect.width > 0 || rect.height < 0)
        sprite.setTextureRect(rect);
    }
  };

} // namespace ComponentRType
