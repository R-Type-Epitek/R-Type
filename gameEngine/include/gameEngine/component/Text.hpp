//
// Created by Alexandre Decobert on 17/12/2023.
//

#pragma once
#include "gameEngine/asset/AssetManager.hpp"

#include <SFML/Graphics.hpp>
#include <string>

namespace ComponentRType
{
  namespace assetManager = GameEngine::Asset;

  struct Text {
    sf::Text text;

    Text() = default;

    Text(std::string const &str, size_t x, size_t y, size_t size, sf::Font &font = assetManager::getFont())
    {
      text = sf::Text();
      text.setFont(font);
      text.setString(str);
      text.setCharacterSize(size);
      text.setFillColor(sf::Color::White);
      text.setPosition(x, y);
    }
  };

} // namespace ComponentRType
