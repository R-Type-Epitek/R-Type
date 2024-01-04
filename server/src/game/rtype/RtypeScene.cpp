//
// Created by raphael on 12/22/23.
//

#include "game/rtype/RtypeScene.hpp"
#include "gameEngine/component/Gravity.hpp"
#include "gameEngine/component/MetaData.hpp"
#include "gameEngine/component/Displayable.hpp"
#include "gameEngine/component/Transform.hpp"
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/RegistryBuilder.hpp"
#include "gameEngine/component/NetworkedEntity.hpp"

namespace Server::Game
{
  void RtypeScene::initRegistry()
  {
    auto builder = GameEngine::Builder::RegistryBuilder();

    // Components
    builder.registerAllMandatoryComponent();

    // Systems
    builder.buildSystemPhysics();
    builder.buildSystemAnimation();
    builder.buildSystemRenderer();
    builder.buildSystemKeyboard();
    builder.buildSystemEcsSerializer();
    m_registry = builder.getResult();
  }

  void RtypeScene::initEntities()
  {
    m_entityFactory = std::make_unique<GameEngine::Entity::EntityFactory>(m_entities, *m_registry);

    //    TODO: Use a config loader
    {
      auto compId = ComponentRType::NetworkedEntity {1};
      auto compMetaData =
        ComponentRType::MetaData("assets/sprites/r-typesheet23.gif", GameEngine::Entity::EntityType::Enemy);
      m_entityFactory->createFromNetwork(compId, compMetaData);
    }

    {
      auto compId = ComponentRType::NetworkedEntity {2};
      auto compMetaData =
        ComponentRType::MetaData("assets/sprites/r-typesheet26.gif", GameEngine::Entity::EntityType::Enemy);
      m_entityFactory->createFromNetwork(compId, compMetaData);
    }
  }

  GameEngine::ECS::Registry& RtypeScene::getECS()
  {
    return *m_registry;
  }

  GameEngine::Entity::EntityFactory& RtypeScene::getEntityFactory()
  {
    return *m_entityFactory;
  }

} // namespace Server::Game::Rtype