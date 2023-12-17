//
// Created by edouard on 12/12/23.
//

#include "RTypeClient.hpp"

std::shared_ptr<Client::IScene> Client::SceneManager::createScene(Client::SceneName scene)
{
    std::map<Client::SceneName, std::function<std::shared_ptr<Client::IScene>(Client::SceneName)>> m{
        {Client::SceneName::kWelcomeScene, createWelcomeScene},
        {Client::SceneName::kLobbyScene, createLobbyScene}
    };

    if (m.find(scene) != m.end()) {
        return m[scene](scene);
    }
    std::cout << "\"" << scene << "\" is not a type\n";
    throw std::exception();
}

std::shared_ptr<Client::IScene> Client::SceneManager::createWelcomeScene(Client::SceneName scene)
{
    std::shared_ptr<Client::IScene> scenePtr = std::make_shared<Client::WelcomeScene>(scene);

    return scenePtr;
}

std::shared_ptr<Client::IScene> Client::SceneManager::createLobbyScene(Client::SceneName scene)
{
    std::shared_ptr<Client::IScene> scenePtr = std::make_shared<Client::LobbyScene>(scene);

    return scenePtr;
}
