//
// Created by edouard on 12/12/23.
//

#include "RTypeClient.hpp"

Client::LobbyScene::LobbyScene(Client::SceneName sceneName)
{
    this->sceneName_ = sceneName;

    Background tmpBackground(
        sf::Vector2f(0, 0),
        "assets/lobby/bg.png"
    );
    this->background_ = tmpBackground;

    Button tmpEscapeButton(
        sf::Vector2f(1182, 270),
        sf::Vector2f(31, 31),
        "assets/lobby/escape_button.png"
    );
    this->escapeButton_ = std::make_shared<Button>(tmpEscapeButton);

    Button tmpAcceptButton(
        sf::Vector2f(963, 720),
        sf::Vector2f(156, 50),
        "assets/lobby/accept_button.png"
    );
    this->acceptButton_ = std::make_shared<Button>(tmpAcceptButton);

    Button tmpReturnButton(
        sf::Vector2f(803, 720),
        sf::Vector2f(156, 50),
        "assets/lobby/return_button.png"
    );
    this->returnButton_ = std::make_shared<Button>(tmpReturnButton);

    InputText tmpIpInput(
        sf::Vector2f(718, 338),
        sf::Vector2f(237, 48),
        "assets/font/nasalization-rg.ttf",
        DEFAULT_IP
    );
    this->ipInput_ = std::make_shared<InputText>(tmpIpInput);

    InputText tmpPortInput(
        sf::Vector2f(961, 338),
        sf::Vector2f(237, 48),
        "assets/font/nasalization-rg.ttf",
        DEFAULT_PORT
    );
    this->portInput_ = std::make_shared<InputText>(tmpPortInput);
}

void Client::LobbyScene::draw(sf::RenderWindow &window)
{
    this->background_.draw(window);
    this->acceptButton_->draw(window);
    this->returnButton_->draw(window);
    this->escapeButton_->draw(window);
    this->ipInput_->draw(window);
    this->portInput_->draw(window);
}

bool Client::LobbyScene::isInShape(sf::Event::MouseButtonEvent &mouse, sf::RectangleShape &myShape)
{
    int minX = myShape.getPosition().x;
    int minY = myShape.getPosition().y;
    int maxX = myShape.getSize().x + minX;
    int maxY = myShape.getSize().y + minY;

    return minX < mouse.x && mouse.x < maxX && minY < mouse.y && mouse.y < maxY;
}

int Client::LobbyScene::pollEvent(sf::RenderWindow &window, Client::Network &network)
{
    while (window.pollEvent(this->event_)) {
        if (this->event_.type == sf::Event::Closed ||
           (this->event_.type == sf::Event::KeyPressed &&
            this->event_.key.code == sf::Keyboard::Escape)) {
            // TODO: open pop up to ask if user wants to quit if he is in a lobby
            window.close();
        }

        // get text from input slot
        if (this->event_.type == sf::Event::TextEntered && this->event_.text.unicode < 128) {
            if (this->ipInput_->isClicked() && !this->portInput_->isClicked()) {
                if (this->event_.text.unicode == 8) { // 8 = Backspace
                    this->ntIp_.pop_back();
                    this->ipInput_->popInput();
                    continue;
                }
                if (this->event_.text.unicode != 13) { // 13 = Enter
                    this->ntIp_ += static_cast<char>(this->event_.text.unicode);
                    this->ipInput_->setInput(static_cast<char>(this->event_.text.unicode));
                } else {
                    this->ipInput_->endInput();
                }
            }
            if (this->portInput_->isClicked() && !this->ipInput_->isClicked()) {
                if (this->event_.text.unicode == 8) { // 8 = Backspace
                    this->ntPort_.pop_back();
                    this->portInput_->popInput();
                    continue;
                }
                if (this->event_.text.unicode != 13) { // 13 = Enter
                    this->ntPort_ += static_cast<char>(this->event_.text.unicode);
                    this->portInput_->setInput(static_cast<char>(this->event_.text.unicode));
                } else {
                    this->portInput_->endInput();
                }
            }
        }

        // get mouse event
        if ((this->event_.type == sf::Event::MouseButtonPressed) ||
            (this->event_.type == sf::Event::MouseButtonReleased)) {
            // Button click
            if (this->isInShape(this->event_.mouseButton, *this->escapeButton_->getShape())) {
                if (this->event_.type == sf::Event::MouseButtonReleased) {
                    this->escapeButton_->isReleased();
                    // TODO: open pop up to ask if user wants to quit if he is in a lobby
                    window.close();
                }
                this->escapeButton_->isClicked();
            }
            if (this->isInShape(this->event_.mouseButton, *this->returnButton_->getShape())) {
                if (this->event_.type == sf::Event::MouseButtonReleased) {
                    this->returnButton_->isReleased();
                    return Client::SceneName::kWelcomeScene;
                }
                this->returnButton_->isClicked();
            }
            if (this->isInShape(this->event_.mouseButton, *this->acceptButton_->getShape())) {
                if (this->event_.type == sf::Event::MouseButtonReleased) {
                    this->acceptButton_->isReleased();
                    if (this->ntIp_ != DEFAULT_IP || this->ntPort_ != DEFAULT_PORT) {
                        network.setEndpoint(this->ntIp_, this->ntPort_);
                    }
                    network.connectToServer();
                    network.updateName("John Doe");
                    network.joinRoom(0);
                    network.startGame(0);
                    return Client::SceneName::kGameScene;
                }
                this->acceptButton_->isClicked();
            }

            // InputSlot click
            if (this->isInShape(this->event_.mouseButton, *this->ipInput_->getShape())) {
                if (this->portInput_->isClicked()) {
                    this->portInput_->endInput();
                }
                this->ipInput_->startInput();
            }
            if (this->isInShape(this->event_.mouseButton, *this->portInput_->getShape())) {
                if (this->ipInput_->isClicked()) {
                    this->ipInput_->endInput();
                }
                this->portInput_->startInput();
            }
        }
    }
    return 0;
}
