//
// Created by Alexandre Decobert on 17/12/2023.
//

#include "gameEngine/logic/SystemLogic.hpp"
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/system/System.hpp"
#include "gameEngine/system/Animation.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>
#include <memory>
#include <vector>

/// \brief Launches the system and updates each entity using the relevant systems.
/// \param std::shared_ptr<Mediator>& - A shared pointer to the Mediator object.
/// \param std::vector<Entity> - A vector of Entity objects.
/// \param sf::RenderWindow& - A reference to the RenderWindow object.

namespace GameEngine::ECS {

void SystemLogic::launchSystem(std::shared_ptr<Registry>& mediator, std::vector<Entity> entities,
                               sf::RenderWindow& window) {
  std::unordered_map<char const*, std::shared_ptr<System>> systems = mediator->getSystems();

  for (auto& entity : entities) {
    for (auto& system : systems) {
      Signature sys_signature = mediator->getSystemSignature(system.first);
      Signature entity_signature = mediator->getEntitySignature(entity);
      if ((entity_signature & sys_signature) == sys_signature) {
        system.second->update(mediator->getComponentManager(), entity, window);
      }
    }
  }
}
}  // namespace GameEngine::ECS
