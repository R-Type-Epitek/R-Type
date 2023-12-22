//
// Created by Xavier VINCENT on 18/12/23.
//

#include "RTypeClient.hpp"

Client::GameScene::GameScene(Client::SceneName sceneName) {
  this->sceneName_ = sceneName;

  Background tmpBackground(sf::Vector2f(0, 0), "assets/welcome/bg.jpg");
  this->background_ = tmpBackground;
}

void Client::GameScene::draw(sf::RenderWindow& window) { this->background_.draw(window); }

int Client::GameScene::pollEvent(sf::RenderWindow& window, Client::Network& network) {
  (void)network;
  while (window.pollEvent(this->event_)) {
    if (this->event_.type == sf::Event::Closed ||
        (this->event_.type == sf::Event::KeyPressed && this->event_.key.code == sf::Keyboard::Escape)) {
      // TODO: open pop up to ask if user wants to quit if he is in a lobby
      window.close();
    }
    if (this->event_.type == sf::Event::KeyPressed) {
      if (this->event_.key.code == sf::Keyboard::Z) network.sendKey("z");
      if (this->event_.key.code == sf::Keyboard::Q) network.sendKey("q");
      if (this->event_.key.code == sf::Keyboard::S) network.sendKey("s");
      if (this->event_.key.code == sf::Keyboard::D) network.sendKey("d");
      if (this->event_.key.code == sf::Keyboard::Space) network.sendKey(" ");
    }
  }
  return 0;
}
