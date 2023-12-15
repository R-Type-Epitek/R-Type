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
#include "Scene.hh"
#include "Component.hh"

namespace client {
    class WelcomeScene : public IScene {
        public:
            explicit WelcomeScene(client::Scene_name scene_name);
            ~WelcomeScene() override = default;

            static bool is_in_shape(sf::Event::MouseButtonEvent &mouse, sf::RectangleShape &my_shape);
            int poll_event(sf::RenderWindow &window, client::Network &network) override;
            void draw(sf::RenderWindow &window) override;
        private:
            client::Scene_name scene_name_;
            std::vector<std::shared_ptr<int>> entity_; // future entity
            Background background_;
            std::shared_ptr<Button> play_button_;
            sf::Event event_;
    };
}