//
// Created by edouard on 12/12/23.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window/Window.hpp>
#include <iostream>
#include <memory>
#include <optional>
#include <functional>
#include "Scene.hpp"
#include "Component.hpp"
#include "Network.hpp"

namespace Client {
    class LobbiesScene : public IScene {
        public:
            explicit LobbiesScene(Client::SceneName sceneName);
            ~LobbiesScene() override = default;

            static bool isInShape(sf::Event::MouseButtonEvent &mouse, sf::RectangleShape &myShape);
            int pollEvent(sf::RenderWindow &window, Client::Network &network) override;
            void draw(sf::RenderWindow &window) override;

        protected:
        private:
            Client::SceneName sceneName_;
            std::vector<std::shared_ptr<int>> entity_; // future entity
            Background background_;
            std::shared_ptr<Button> escapeButton_;
            std::shared_ptr<Button> returnButton_;
            std::shared_ptr<Button> acceptButton_;
            std::shared_ptr<InputText> ipInput_;
            std::shared_ptr<InputText> portInput_;
            std::string ntIp_{DEFAULT_IP};
            std::string ntPort_{DEFAULT_PORT};
            sf::Event event_;
    };
}