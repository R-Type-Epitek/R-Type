//
// Created by raphael on 11/28/23.
//

#pragma once

#include <memory>
#include "ecs/Mediator.hpp"
#include <set>
#include "ecs/entity/Entity.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include "ISystem.hpp"

class System : public ISystem
{
 public:
    void update(std::shared_ptr<ComponentManager>& component_manager, Entity entity, sf::RenderWindow& window) {}
  std::vector<Entity> m_entities;
};
