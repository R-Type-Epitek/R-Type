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

namespace Client {
    enum SceneName {
        kWelcomeScene,
        kLobbiesScene,
        //GAME_SCENE,
        kNullScene
    };

    class IScene {
        public:
            virtual ~IScene() = default;

            virtual int pollEvent(
                sf::RenderWindow &window,
                Client::Network &network
            ) = 0;
            virtual void draw(sf::RenderWindow &window) = 0;
    };

    class SceneManager
    {
        public:
            SceneManager() = delete;
            ~SceneManager() = delete;
            SceneManager(SceneManager const &toCopy) = delete;
            SceneManager(SceneManager &&toMove) = delete;
            SceneManager &operator=(SceneManager const &toCopy) = delete;
            SceneManager &operator=(SceneManager &&toMove) = delete;

            static std::shared_ptr<Client::IScene> createScene(SceneName scene);
        private:
            static std::shared_ptr<Client::IScene> createWelcomeScene(SceneName scene);
            static std::shared_ptr<Client::IScene> createLobbiesScene(SceneName scene);
            //static std::shared_ptr<Client::IScene> creatGameScene(SceneName scene);
    };
}