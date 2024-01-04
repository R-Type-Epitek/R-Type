//
// Created by raphael on 1/4/24.
//

#pragma once

#include "gameEngine/ecs/entity/Entity.hpp"
#include "gameEngine/component/MetaData.hpp"
#include "gameEngine/component/NetworkedEntity.hpp"
#include "EntityType.hpp"
#include "gameEngine/asset/AssetManager.hpp"
#include "spdlog/spdlog.h"
#include <stdexcept>

namespace GameEngine::Entity
{

  class EntityFactory {
   public:
    EntityFactory(std::vector<GameEngine::ECS::Entity> &entities, GameEngine::ECS::Registry &registry);

    GameEngine::ECS::Entity create(const EntityType &type);

    GameEngine::ECS::Entity createFromNetwork(
      ComponentRType::NetworkedEntity &networkId,
      ComponentRType::MetaData &metaData);

    GameEngine::ECS::Entity createFromBluePrint(EntityBluePrint const &payload);

    static EntityBluePrint playerEntity;
    static EntityBluePrint enemyEntity;
    static EntityBluePrint bulletEntity;

   private:
    using AssetManager = GameEngine::Asset::AssetManager;

    std::vector<GameEngine::ECS::Entity> &m_entities; ///< Vector of entities in the Factory context.
    GameEngine::ECS::Registry &m_registry;            ///< Reference to the ECS registry.
  };

} // GameEngine::Entity
