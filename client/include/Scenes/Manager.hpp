//
// Created by edouard on 12/12/23.
//

#pragma once

#include "RTypeClient.hpp"

namespace Client
{
    enum SceneName {
        kWelcomeScene,
        kLobbyScene,
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

        protected:
        private:
            static std::shared_ptr<Client::IScene> createWelcomeScene(SceneName scene);
            static std::shared_ptr<Client::IScene> createLobbyScene(SceneName scene);
            //static std::shared_ptr<Client::IScene> creatGameScene(SceneName scene);
    };
}
