#include "../include/Client.hh"
#include "../include/Scene.hh"

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML Window");
    sf::Color color = sf::Color::Black;
    std::shared_ptr<client::IScene> current_scene = client::SceneManager::creatScene(client::Scene_name::kWelcomeScene);

    while (window.isOpen()) {
        switch (current_scene->poll_event(window)) {
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
        // Draw your SFML content here
        window.display();
    }

    return 0;
}
