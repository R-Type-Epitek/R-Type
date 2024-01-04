//
// Created by raphael on 12/20/23.
//

#pragma once
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/entity/EntityFactory.hpp"

namespace GameEngine::Scene
{
  class IScene {
   public:
    virtual ~IScene() = default;

    virtual void initRegistry() = 0;

    virtual void initEntities() = 0;

    virtual ECS::Registry& getECS() = 0;

    virtual GameEngine::Entity::EntityFactory& getEntityFactory() = 0;
  };
} // namespace GameEngine::Scene
