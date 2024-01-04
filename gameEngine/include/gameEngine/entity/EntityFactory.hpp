//
// Created by raphael on 1/4/24.
//

#pragma once

#include "gameEngine/ecs/entity/Entity.hpp"
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/asset/AssetManager.hpp"
#include "spdlog/spdlog.h"
#include <stdexcept>
#include <string>
#include <vector>
#include <SFML/System/Vector2.hpp>

namespace GameEngine
{
  namespace Entity
  {

    enum class EntityType
    {
      Player,
      Enemy,
      Bullet
    };

    struct PlayerPayload {
      bool light = false;
      std::string texturePath;
      sf::Vector2f SpawnPosition;
    };

    struct EnemyPayload {
      bool light = false;
      std::string texturePath;
      sf::Vector2f SpawnPosition;
    };

    struct BulletPayload {
      bool light = false;
      std::string texturePath;
      sf::Vector2f SpawnPosition;
    };

    class EntityFactory {
     public:
      EntityFactory(std::vector<GameEngine::ECS::Entity> &entities, GameEngine::ECS::Registry &registry);

      GameEngine::ECS::Entity create(const PlayerPayload &payload = {});
      GameEngine::ECS::Entity create(const EnemyPayload &payload = {});
      GameEngine::ECS::Entity create(const BulletPayload &payload = {});

     private:
      using AssetManager = GameEngine::Asset::AssetManager;
      GameEngine::ECS::Entity createPlayer(PlayerPayload = {});
      GameEngine::ECS::Entity createEnemy(EnemyPayload = {});
      GameEngine::ECS::Entity createBullet(BulletPayload = {});
      GameEngine::ECS::Entity newEntity();

      std::vector<GameEngine::ECS::Entity> &m_entities; ///< Vector of entities in the Factory context.
      GameEngine::ECS::Registry &m_registry;            ///< Reference to the ECS registry.
    };

  } // Entity
} // GameEngine
