#include "../../include/WelcomeScene.hh"

client::WelcomeScene::WelcomeScene(client::Scene_name scene_name)
{
    this->scene_name_ = scene_name;
    std::string tmp = "assets/welcome/welcome_bg.jpg";
    Background tmp_background(sf::Vector2f(0, 0), tmp);
    this->background_ = tmp_background;
    tmp = "assets/welcome/rtype_button.jpg";
    Button tmp_button(sf::Vector2f(615, 480), sf::Vector2f(690, 120), tmp);
    this->play_button_ = std::make_shared<Button>(tmp_button);
}

void client::WelcomeScene::draw(sf::RenderWindow &window)
{
    this->background_.draw(window);
    this->play_button_->draw(window);
}

bool client::WelcomeScene::is_in_shape(sf::Event::MouseButtonEvent &mouse, sf::RectangleShape &my_shape)
{
    int min_x = my_shape.getPosition().x;
    int min_y = my_shape.getPosition().y;
    int max_x = my_shape.getSize().x + min_x;
    int max_y = my_shape.getSize().y + min_y;

    return min_x < mouse.x && mouse.x < max_x && min_y < mouse.y && mouse.y < max_y;
}

int client::WelcomeScene::poll_event(sf::RenderWindow &window, client::Network &network)
{
    while (window.pollEvent(this->event_)) {
        if ((this->event_.type == sf::Event::Closed) ||
        (this->event_.type == sf::Event::KeyPressed &&
        this->event_.key.code == sf::Keyboard::Escape)){
            // open pop up to ask if user wants to quit if he is in a lobby
            window.close();
        }
        if ((this->event_.type == sf::Event::MouseButtonPressed) ||
        (this->event_.type == sf::Event::MouseButtonReleased)) {
            if (this->is_in_shape(this->event_.mouseButton, *this->play_button_->get_shape())) {
                if (this->event_.type == sf::Event::MouseButtonReleased) {
                    this->play_button_->is_release();
                    return 2;
                }
                this->play_button_->is_clicked();
               
            }
        }
    }
    return 0;
}