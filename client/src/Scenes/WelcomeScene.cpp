#include "Scenes/WelcomeScene.hpp"

Client::WelcomeScene::WelcomeScene(Client::SceneName sceneName)
{
    this->sceneName_ = sceneName;
    std::string tmp = "assets/welcome/welcome_bg.jpg";
    Background tmp_background(sf::Vector2f(0, 0), tmp);
    this->background_ = tmp_background;
    tmp = "assets/welcome/rtype_button.jpg";
    Button tmp_button(sf::Vector2f(615, 480), sf::Vector2f(690, 120), tmp);
    this->play_button_ = std::make_shared<Button>(tmp_button);
}

void Client::WelcomeScene::draw(sf::RenderWindow &window)
{
    this->background_.draw(window);
    this->play_button_->draw(window);
}

bool Client::WelcomeScene::isInShape(
    sf::Event::MouseButtonEvent &mouse,
    sf::RectangleShape &myShape
)
{
    int min_x = myShape.getPosition().x;
    int min_y = myShape.getPosition().y;
    int max_x = myShape.getSize().x + min_x;
    int max_y = myShape.getSize().y + min_y;

    return min_x < mouse.x && mouse.x < max_x && min_y < mouse.y && mouse.y < max_y;
}

int Client::WelcomeScene::pollEvent(
    sf::RenderWindow &window,
    Client::Network &network
)
{
    (void)network;
    while (window.pollEvent(this->event_)) {
        if (this->event_.type == sf::Event::Closed ||
           (this->event_.type == sf::Event::KeyPressed &&
            this->event_.key.code == sf::Keyboard::Escape)) {
            // TODO: open pop up to ask if user wants to quit if he is in a lobby
            window.close();
        }
        if (this->event_.type == sf::Event::MouseButtonPressed ||
            this->event_.type == sf::Event::MouseButtonReleased) {
            if (this->isInShape(this->event_.mouseButton, *this->play_button_->getShape())) {
                if (this->event_.type == sf::Event::MouseButtonReleased) {
                    this->play_button_->isReleased();
                    return Client::SceneName::kLobbiesScene;
                }
                this->play_button_->isClicked();
            }
        }
    }
    return Client::SceneName::kWelcomeScene;
}
