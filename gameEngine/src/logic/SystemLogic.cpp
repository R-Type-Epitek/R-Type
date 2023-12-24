//
// Created by Alexandre Decobert on 17/12/2023.
//

#include "logic/SystemLogic.hpp"
#include "ecs/Mediator.hpp"
#include <vector>
#include <iostream>
#include <memory>
#include "ecs/system/ISystem.hpp"
#include "system/Animation.hpp"

/// \brief Launches the system and updates each entity using the relevant systems.
/// \param std::shared_ptr<Mediator>& - A shared pointer to the Mediator object.
/// \param std::vector<Entity> - A vector of Entity objects.
/// \param sf::RenderWindow& - A reference to the RenderWindow object.

void SystemLogic::launchSystem(std::shared_ptr<Mediator>& mediator, std::vector<Entity> entities, sf::RenderWindow& window)
{
  std::unordered_map<const char*, std::shared_ptr<ISystem>> systems = mediator->getSystems();

  for (auto& entity: entities) {
    for (auto& system : systems) {
      Signature sys_signature = mediator->getSystemSignature(system.first);
      Signature entity_signature = mediator->getEntitySignature(entity);
      if ((entity_signature & sys_signature) == sys_signature) {
          system.second->update(mediator->getComponentManager(), entity, window);
      }
    }
  }
}