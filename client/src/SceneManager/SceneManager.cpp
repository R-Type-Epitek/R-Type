#include "Scenes/WelcomeScene.hpp"
#include "Scenes/LobbiesScene.hpp"

std::shared_ptr<Client::IScene> Client::SceneManager::createScene(Client::SceneName scene)
{
    std::map<Client::SceneName, std::function<std::shared_ptr<Client::IScene>(Client::SceneName)>> m{
        {Client::SceneName::kWelcomeScene, createWelcomeScene},
        {Client::SceneName::kLobbiesScene, createLobbiesScene}
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

std::shared_ptr<Client::IScene> Client::SceneManager::createLobbiesScene(Client::SceneName scene)
{
    std::shared_ptr<Client::IScene> scenePtr = std::make_shared<Client::LobbiesScene>(scene);

    return scenePtr;
}
