//
// Created by edouard on 12/12/23.
//

#pragma once

#include "RTypeClient.hpp"

namespace Client {
class WelcomeScene : public IScene {
 public:
  explicit WelcomeScene(Client::SceneName sceneName);
  ~WelcomeScene() override = default;

  static bool isInShape(sf::Event::MouseButtonEvent& mouse, sf::RectangleShape& myShape);
  int pollEvent(sf::RenderWindow& window, Client::Network& network) override;
  void draw(sf::RenderWindow& window) override;

 protected:
 private:
  Client::SceneName sceneName_;
  Client::Background background_;
  std::shared_ptr<Client::Button> playButton_;
  sf::Event event_;
};
}  // namespace Client
