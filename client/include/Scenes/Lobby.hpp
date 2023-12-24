//
// Created by edouard on 12/12/23.
//

#pragma once

#include "RTypeClient.hpp"

namespace Client
{
  class LobbyScene : public IScene {
  public:
    explicit LobbyScene(Client::SceneName sceneName);
    ~LobbyScene() override = default;

    static bool isInShape(
      sf::Event::MouseButtonEvent &mouse,
      sf::RectangleShape &myShape);
    int pollEvent(sf::RenderWindow &window, Client::Network &network) override;
    void draw(sf::RenderWindow &window) override;

  protected:
  private:
    Client::SceneName sceneName_;
    Client::Background background_;
    std::shared_ptr<Client::Button> escapeButton_;
    std::shared_ptr<Client::Button> returnButton_;
    std::shared_ptr<Client::Button> acceptButton_;
    std::shared_ptr<Client::InputText> ipInput_;
    std::shared_ptr<Client::InputText> portInput_;
    std::string ntIp_ {DEFAULT_IP};
    std::string ntPort_ {DEFAULT_PORT};
    sf::Event event_;
  };
} // namespace Client
