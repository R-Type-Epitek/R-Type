#include "Component.hpp"

Client::Background::Background(sf::Vector2f position, std::string assetPath)
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

std::shared_ptr<sf::RectangleShape>Client::Button::getShape()
{
    return this->shape_;
}

void Client::Button::isClicked()
{
    this->alpha_ = 190;
}

void Client::Button::isReleased()
{
    this->alpha_ = 250;
}

Client::Button::Button(sf::Vector2f position, sf::Vector2f size, std::string assetPath)
{
    this->shape_ = std::make_shared<sf::RectangleShape>(size);
    this->shape_->setPosition(position);
    if(!this->texture_.loadFromFile(assetPath))
        std::cout << "texture not loaded" << std::endl;
    this->sprite_ = std::make_shared<sf::Sprite>(sf::Sprite(this->texture_));
    this->sprite_->setPosition(position);
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

std::shared_ptr<sf::RectangleShape> Client::InputText::getShape()
{
    return this->shape_;
}

void Client::InputText::startInput()
{
    this->shape_->setFillColor(sf::Color(0, 0, 0, 125));
    this->isClicked_ = true;
}

void Client::InputText::endInput()
{
    this->shape_->setFillColor(sf::Color(0, 0, 0, 0));
    this->isClicked_ = false;
}

std::string Client::InputText::getInput()
{
    return this->input_;
}

void Client::InputText::setInput(char input)
{
    this->input_ += input;
}

void Client::InputText::popInput()
{
    this->input_.pop_back();
}

bool Client::InputText::isClicked() const
{
    return this->isClicked_;
}

Client::InputText::InputText(
    sf::Vector2f position,
    sf::Vector2f size,
    std::string fontPath,
    std::string defaultText
)
{
    int margin_text = (size.y  - 14) / 2;

    this->positionText_.x = position.x + margin_text;
    this->positionText_.y = position.y + margin_text;
    this->shape_ = std::make_shared<sf::RectangleShape>(size);
    this->shape_->setPosition(position);
    this->shape_->setFillColor(sf::Color(0, 0, 0, 0));
    this->input_ = defaultText;
    this->fontPath_ = fontPath;
}

void Client::InputText::draw(sf::RenderWindow &window)
{
    int text_size = 14;
    sf::Font tmp_font;
    sf::Text tmp(this->input_, tmp_font, text_size);
    if (!tmp_font.loadFromFile(this->fontPath_)) {
         std::cout << "font not loaded" << std::endl;
    }
    tmp.setFillColor(sf::Color::White);
    tmp.setPosition(this->positionText_);
    window.draw(*this->shape_);
    tmp.setString(this->input_);
    window.draw(tmp);
}
