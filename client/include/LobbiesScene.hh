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
#include "Network.hpp"

namespace client {
    class LobbiesScene : public IScene {
        public:
            explicit LobbiesScene(client::Scene_name scene_name);
            ~LobbiesScene() override = default;

            static bool is_in_shape(sf::Event::MouseButtonEvent &mouse, sf::RectangleShape &my_shape);
            int poll_event(sf::RenderWindow &window, client::Network &network) override;
            void draw(sf::RenderWindow &window) override;
        private:
            client::Scene_name scene_name_;
            std::vector<std::shared_ptr<int>> entity_; // future entity
            Background background_;
            std::shared_ptr<Button> escape_button_;
            std::shared_ptr<Button> return_button_;
            std::shared_ptr<Button> accept_button_;
            std::shared_ptr<InputText> ip_input_;
            std::shared_ptr<InputText> port_input_;
            std::string nt_ip_{DEFAULT_IP};
            std::string nt_port_{DEFAULT_PORT};
            sf::Event event_;
    };
}