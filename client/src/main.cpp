#include "Scene.hpp"
#include "Network.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "R-Type");
    sf::Color color = sf::Color::Black;
    std::shared_ptr<Client::IScene> current_scene = Client::SceneManager::createScene(Client::SceneName::kWelcomeScene);
    Client::Network network(DEFAULT_IP, DEFAULT_PORT);

    while (window.isOpen()) {
        switch (current_scene->pollEvent(window, network)) {
            case Client::SceneName::kWelcomeScene:
                current_scene = Client::SceneManager::createScene(Client::SceneName::kWelcomeScene);
                break;
            case Client::SceneName::kLobbiesScene:
                current_scene = Client::SceneManager::createScene(Client::SceneName::kLobbiesScene);
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
