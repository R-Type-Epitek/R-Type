//
// Created by raphael on 11/28/23.
//

#pragma once

#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/component/ComponentManager.hpp"
#include "gameEngine/ecs/entity/Entity.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include <set>

namespace GameEngine::ECS
{
  class System {
  public:
    virtual ~System() = default;

    std::set<Entity> m_entities {};
  };

} // namespace GameEngine::ECS
