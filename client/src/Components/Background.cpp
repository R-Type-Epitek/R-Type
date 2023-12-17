//
// Created by X-VINCENT on 12/17/23.
//

#include "RTypeClient.hpp"

Client::Background::Background(
    sf::Vector2f position,
    std::string assetPath
)
{
    if(!this->texture_.loadFromFile(assetPath))
        std::cout << "texture not loaded" << std::endl;
    this->sprite_ = std::make_shared<sf::Sprite>(sf::Sprite(this->texture_));
    this->sprite_->setPosition(position);
}

void Client::Background::draw(sf::RenderWindow &window)
{
    this->sprite_ = std::make_shared<sf::Sprite>(sf::Sprite(this->texture_));
    window.draw(*this->sprite_);
}
