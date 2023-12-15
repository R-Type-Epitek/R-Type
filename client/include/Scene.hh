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
#include "Network.hpp"

namespace client {
    enum Scene_name {
    kWelcomeScene,
    kLobbiesScene,
    //GAME_SCENE,
    kNullScene
    };

    class IScene {
        public:
            virtual ~IScene() = default;

            virtual int poll_event(sf::RenderWindow &window, client::Network &network) = 0;
            virtual void draw(sf::RenderWindow &window) = 0;
    };

    class SceneManager
    {
        public:
            SceneManager() = delete;
            ~SceneManager() = delete;
            SceneManager(SceneManager const &to_copy) = delete;
            SceneManager(SceneManager &&to_move) = delete;
            SceneManager &operator=(SceneManager const &to_copy) = delete;
            SceneManager &operator=(SceneManager &&to_move) = delete;

            static std::shared_ptr<client::IScene> creatScene(Scene_name scene);
        private:
            static std::shared_ptr<client::IScene> creatWelcomeScene(Scene_name scene);
            static std::shared_ptr<client::IScene> creatLobbiesScene(Scene_name scene);
            //static std::shared_ptr<client::IScene> creatGameScene(Scene_name scene);
    };
}