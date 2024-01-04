//
// Created by Alexandre Decobert on 17/12/2023.
//

#pragma once
#include "gameEngine/asset/AssetManager.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <string>

namespace ComponentRType
{

  namespace assetManager = GameEngine::Asset;

  struct Displayable {
    sf::Sprite sprite;

    Displayable()
    {
      sprite.setTexture(assetManager::getTexture());
    }

    Displayable(sf::Texture& texture)
    {
      sprite.setTexture(texture);
    }

    Displayable(sf::Texture& texture, sf::IntRect const& rect)
    {
      sprite.setTexture(texture);
      if (rect.width > 0 || rect.height < 0)
        sprite.setTextureRect(rect);
    }
  };

} // namespace ComponentRType
