//
// Created by Xavier VINCENT on 17/12/23.
//

#include "RTypeClient.hpp"

Client::Button::Button(
  sf::Vector2f position,
  sf::Vector2f size,
  std::string assetPath)
{
  this->shape_ = std::make_shared<sf::RectangleShape>(size);
  this->shape_->setPosition(position);
  if (!this->texture_.loadFromFile(assetPath))
    std::cout << "texture not loaded" << std::endl;
  this->sprite_ = std::make_shared<sf::Sprite>(sf::Sprite(this->texture_));
  this->sprite_->setPosition(position);
}

std::shared_ptr<sf::RectangleShape> Client::Button::getShape()
{
  return this->shape_;
}

void Client::Button::draw(sf::RenderWindow &window)
{
  this->sprite_->setTexture(this->texture_);
  this->sprite_->setPosition(this->shape_->getPosition());
  sf::Color color = this->sprite_->getColor();
  color.a = this->alpha_;
  this->sprite_->setColor(color);
  window.draw(*this->sprite_);
}

void Client::Button::isClicked()
{
  this->alpha_ = 190;
}

void Client::Button::isReleased()
{
  this->alpha_ = 255;
}
