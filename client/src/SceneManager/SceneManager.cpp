#include "../../include/WelcomeScene.hh"
#include "../../include/LobbiesScene.hh"

std::shared_ptr<client::IScene> client::SceneManager::creatScene(client::Scene_name scene)
{
    std::map<client::Scene_name, std::function<std::shared_ptr<client::IScene>(client::Scene_name)>> m{
        {client::Scene_name::kWelcomeScene, creatWelcomeScene},
        {client::Scene_name::kLobbiesScene, creatLobbiesScene}};

    if (m.find(scene) != m.end()) {
        return m[scene](scene);
    }
    std::cout << "\"" << scene << "\" is not a type\n";
    throw std::exception();
}

std::shared_ptr<client::IScene> client::SceneManager::creatWelcomeScene(client::Scene_name scene)
{
    std::shared_ptr<client::IScene> scene_ptr = std::make_shared<client::WelcomeScene>(scene);
    return scene_ptr;
}

std::shared_ptr<client::IScene> client::SceneManager::creatLobbiesScene(client::Scene_name scene)
{
    std::shared_ptr<client::IScene> scene_ptr = std::make_shared<client::LobbiesScene>(scene);
    return scene_ptr;
}
