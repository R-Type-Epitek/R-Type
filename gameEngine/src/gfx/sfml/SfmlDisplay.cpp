//
// Created by Alexandre Decobert on 17/12/2023.
//

#include "gameEngine/gfx/sfml/SfmlDisplay.hpp"
#include <SFML/Graphics.hpp>

/// \brief Display sprite in a SFML RenderWindow
/// \param sf::RenderWindow&
/// \param sf::Sprite&
void SfmlDisplay::display(sf::RenderWindow& window, sf::Sprite& sprite)
{
  window.draw(sprite);
}

/// \brief Set the position of a SFML Sprite
/// \param sf::Sprite&
/// \param ge::Position&
void SfmlDisplay::setPosition(sf::Sprite& sprite, ge::Position& position)
{
  sprite.setPosition(position.x, position.y);
}