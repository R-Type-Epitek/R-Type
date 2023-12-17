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

class System
{
public:
    std::set<Entity> m_entities{};
    // virtual void update(std::shared_ptr<Mediator>& mediator, Entity entity, sf::RenderWindow& window) = 0;
};
