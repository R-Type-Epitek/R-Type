#include "../include/Scene.hh"
#include "../include/Network.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "R-Type");
    sf::Color color = sf::Color::Black;
    std::shared_ptr<client::IScene> current_scene = client::SceneManager::creatScene(client::Scene_name::kWelcomeScene);
    client::Network network(DEFAULT_IP, DEFAULT_PORT);

    while (window.isOpen()) {
        switch (current_scene->poll_event(window, network)) {
            case 1:
                current_scene = client::SceneManager::creatScene(client::Scene_name::kWelcomeScene);
                break;
            case 2:
                current_scene = client::SceneManager::creatScene(client::Scene_name::kLobbiesScene);
                break;
            default:
                break;
        }
        window.clear(color);
        current_scene->draw(window);
        window.display();
    }

    return 0;
}
