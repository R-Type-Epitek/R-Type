//
// Created by Alexandre Decobert on 17/12/2023.
//

#include "logic/SystemLogic.hpp"
#include "ecs/Mediator.hpp"
#include <vector>
#include <iostream>
#include <memory>
#include "ecs/system/ISystem.hpp"

void SystemLogic::launchSystem(std::shared_ptr<Mediator>& mediator, std::vector<Entity> entities, sf::RenderWindow& window)
{
  std::unordered_map<const char*, std::shared_ptr<ISystem>> systems = mediator->getSystems();

  for (auto& entity: entities) {
    for (auto& system : systems) {
      std::string current_type = system.first;
      Signature sys_signature = mediator->getSystemSignature(current_type.c_str());
      Signature entity_signature = mediator->getEntitySignature(entity);
        if ((sys_signature & entity_signature) == sys_signature) {
          // bug here
          //system.second->update(mediator->getComponents(entity), entity, window);
        }
    }
  }
}