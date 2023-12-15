#include "../../include/Component.hh"

client::Background::Background(sf::Vector2f position, std::string &asset_path)
{
    if(!this->texture_.loadFromFile(asset_path))
        std::cout << "texture not loaded" << std::endl;
    this->sprite_ = std::make_shared<sf::Sprite>(sf::Sprite(this->texture_));
    this->sprite_->setPosition(position);
}

void client::Background::draw(sf::RenderWindow &window)
{
    this->sprite_ = std::make_shared<sf::Sprite>(sf::Sprite(this->texture_));
    window.draw(*this->sprite_);
}

std::shared_ptr<sf::RectangleShape>client::Button::get_shape()
{
    return this->shape_;
}

void client::Button::is_clicked()
{
    this->alpha_ = 190;
}

void client::Button::is_release()
{
    this->alpha_ = 250;
}

client::Button::Button(sf::Vector2f position, sf::Vector2f size, std::string &asset_path)
{
    this->shape_ = std::make_shared<sf::RectangleShape>(size);
    this->shape_->setPosition(position);
    if(!this->texture_.loadFromFile(asset_path))
        std::cout << "texture not loaded" << std::endl;
    this->sprite_ = std::make_shared<sf::Sprite>(sf::Sprite(this->texture_));
    this->sprite_->setPosition(position);
}

void client::Button::draw(sf::RenderWindow &window)
{
    this->sprite_->setTexture(this->texture_);
    this->sprite_->setPosition(this->shape_->getPosition());
    sf::Color color = this->sprite_->getColor();
    color.a = this->alpha_;
    this->sprite_->setColor(color);
    window.draw(*this->sprite_);
}

std::shared_ptr<sf::RectangleShape> client::InputText::get_shape()
{
    return this->shape_;
}

void client::InputText::start_input()
{
    this->shape_->setFillColor(sf::Color(0, 0, 0, 125));
    this->is_clicked_ = true;
}

void client::InputText::end_input()
{
    this->shape_->setFillColor(sf::Color(0, 0, 0, 0));
    this->is_clicked_ = false;
}

std::string client::InputText::get_input()
{
    return this->input_;
}

void client::InputText::set_input(char input)
{
    this->input_ += input;
}

void client::InputText::pop_input()
{
    this->input_.pop_back();
}

bool client::InputText::is_clicked() const
{
    return this->is_clicked_;
}

client::InputText::InputText(sf::Vector2f position, sf::Vector2f size, std::string &font_path, std::string &default_text)
{
    int margin_text = (size.y  - 14) / 2;

    this->position_text_.x = position.x + margin_text;
    this->position_text_.y = position.y + margin_text;
    this->shape_ = std::make_shared<sf::RectangleShape>(size);
    this->shape_->setPosition(position);
    this->shape_->setFillColor(sf::Color(0, 0, 0, 0));
    this->input_ = default_text;
    this->font_path_ = font_path;
}

void client::InputText::draw(sf::RenderWindow &window)
{
    int text_size = 14;
    sf::Font tmp_font;
    sf::Text tmp(this->input_, tmp_font, text_size);
    if (!tmp_font.loadFromFile(this->font_path_)) {
         std::cout << "font not loaded" << std::endl;
    }
    tmp.setFillColor(sf::Color::White);
    tmp.setPosition(this->position_text_);
    window.draw(*this->shape_);
    tmp.setString(this->input_);
    window.draw(tmp);
}