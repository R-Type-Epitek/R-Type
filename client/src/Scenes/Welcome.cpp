//
// Created by edouard on 12/12/23.
//

#include "RTypeClient.hpp"

Client::WelcomeScene::WelcomeScene(Client::SceneName sceneName)
{
    this->sceneName_ = sceneName;

    Background tmpBackground(
        sf::Vector2f(0, 0),
        "assets/welcome/bg.jpg"
    );
    this->background_ = tmpBackground;

    Button tmpButton(
        sf::Vector2f(615, 480),
        sf::Vector2f(690, 120),
        "assets/welcome/rtype_button.jpg"
    );
    this->playButton_ = std::make_shared<Button>(tmpButton);
}

void Client::WelcomeScene::draw(sf::RenderWindow &window)
{
    this->background_.draw(window);
    this->playButton_->draw(window);
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
            if (this->isInShape(this->event_.mouseButton, *this->playButton_->getShape())) {
                if (this->event_.type == sf::Event::MouseButtonReleased) {
                    this->playButton_->isReleased();
                    return Client::SceneName::kLobbyScene;
                }
                this->playButton_->isClicked();
            }
        }
    }
    return 0;
}
