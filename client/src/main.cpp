//
// Created by edouard on 12/12/23.
//

// int main() {
//   sf::RenderWindow window(sf::VideoMode(1920, 1080), "R-Type");
//   sf::Color color = sf::Color::Black;
//   std::shared_ptr<Client::IScene> current_scene =
//   Client::SceneManager::createScene(Client::SceneName::kWelcomeScene);
//   Client::Network network(DEFAULT_IP, DEFAULT_PORT);
//
//   while (window.isOpen()) {
//     switch (current_scene->pollEvent(window, network)) {
//       case Client::SceneName::kWelcomeScene:
//         current_scene =
//             Client::SceneManager::createScene(Client::SceneName::kWelcomeScene);
//         break;
//       case Client::SceneName::kLobbyScene:
//         current_scene =
//             Client::SceneManager::createScene(Client::SceneName::kLobbyScene);
//         break;
//       case Client::SceneName::kGameScene:
//         current_scene =
//             Client::SceneManager::createScene(Client::SceneName::kGameScene);
//         break;
//       default:
//         break;
//     }
//     window.clear(color);
//     current_scene->draw(window);
//     window.display();
//   }
//
//   return 0;
// }

#include "Client.hpp"
#include "spdlog/spdlog.h"

int main() {
  spdlog::set_level(spdlog::level::debug);
  Client::Client client = Client::Client();

  client.initNetwork();
  client.initGUI();
  client.initScenes();
  client.run();
};
