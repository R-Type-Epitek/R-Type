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
    this->is_clicked_ = true;
}

void client::InputText::end_input()
{
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

bool client::InputText::is_clicked() const
{
    return this->is_clicked_;
}

client::InputText::InputText(sf::Vector2f position, sf::Vector2f size, std::string &font_path)
{
    sf::Font font;
    int text_size = 14;
    int margin_text = (size.y  - text_size) / 2;
    sf::Vector2f position_text;

    position_text.x = position.x + margin_text;
    position_text.y = position.y + margin_text;
    this->shape_ = std::make_shared<sf::RectangleShape>(size);
    this->shape_->setPosition(position);
    if (!font.loadFromFile(font_path)) {
         std::cout << "font not loaded" << std::endl;
    }
    sf::Text tmp("", font, text_size);
    this->text_ = std::make_shared<sf::Text>(tmp);
    this->text_->setFillColor(sf::Color::White);
    this->text_->setPosition(position_text);
}

void client::InputText::draw(sf::RenderWindow &window)
{
    //this->shape_->setFillColor(sf::Color::Red);
    //window.draw(*this->shape_);
    this->text_->setString(this->input_);
    window.draw(*this->text_);
}