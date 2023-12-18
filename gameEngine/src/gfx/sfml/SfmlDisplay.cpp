//
// Created by Alexandre Decobert on 17/12/2023.
//

#include "gfx/sfml/SfmlDisplay.hpp"
#include "component/Transform.hpp"
#include <SFML/Graphics.hpp>
#include "component/Transform.hpp"

/// \brief display the sprite
/// \param window
/// \param sprite

void SfmlDisplay::display(sf::RenderWindow& window, sf::Sprite& sprite)
{
  window.draw(sprite);
}

/// \brief set the position of the sprite
/// \param sprite
/// \param position

void SfmlDisplay::setPosition(sf::Sprite& sprite, ge::Position& position)
{
  sprite.setPosition(position.x, position.y);
}