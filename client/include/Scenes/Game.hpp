//
// Created by X-VINCENT on 12/18/23.
//

#pragma once

#include "RTypeClient.hpp"

namespace Client
{
    class GameScene : public IScene {
        public:
            explicit GameScene(Client::SceneName sceneName);
            ~GameScene() override = default;

            int pollEvent(
                sf::RenderWindow &window,
                Client::Network &network
            ) override;
            void draw(sf::RenderWindow &window) override;

        protected:
        private:
            Client::SceneName sceneName_;
            Client::Background background_;
            sf::Event event_;
    };
}
