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

namespace Client {
    class WelcomeScene : public IScene {
        public:
            explicit WelcomeScene(Client::SceneName sceneName);
            ~WelcomeScene() override = default;

            static bool isInShape(sf::Event::MouseButtonEvent &mouse, sf::RectangleShape &myShape);
            int pollEvent(sf::RenderWindow &window, Client::Network &network) override;
            void draw(sf::RenderWindow &window) override;

        protected:
        private:
            Client::SceneName sceneName_;
            std::vector<std::shared_ptr<int>> entity_; // future entity
            Background background_;
            std::shared_ptr<Button> play_button_;
            sf::Event event_;
    };
}