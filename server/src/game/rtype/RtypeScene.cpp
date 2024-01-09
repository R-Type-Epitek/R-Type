//
// Created by raphael on 12/22/23.
//

#include "game/rtype/RtypeScene.hpp"
#include "gameEngine/component/Displayable.hpp"
#include "gameEngine/component/Transform.hpp"
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/RegistryBuilder.hpp"

namespace Server::Game
{
  void RtypeScene::initRegistries()
  {
    auto builder = GameEngine::Builder::RegistryBuilder();

    // Components
    builder.registerAllMandatoryComponent();

    // Systems
    builder.buildSystemPhysics();
    builder.buildSystemKeyboard();
    builder.buildSystemEcsSerializer();
    builder.buildSystemInput();
    builder.buildSystemParallax();
    builder.buildSystemMove();

    m_ecsRegistry = builder.getResult();
  }

  void RtypeScene::initEntities()
  {
    m_entityFactory = std::make_unique<GameEngine::Entity::EntityFactory>(m_entities, *m_ecsRegistry);

    //    TODO: Use a config loader
    //    {
    //      auto compId = ComponentRType::NetworkedEntity {1};
    //      auto compMetaData =
    //        ComponentRType::MetaData("assets/sprites/r-typesheet23.gif", GameEngine::Entity::EntityType::Enemy);
    //      m_entityFactory->createFromNetwork(compId, compMetaData);
    //    }
    //
    //    {
    //      auto compId = ComponentRType::NetworkedEntity {2};
    //      auto compMetaData =
    //        ComponentRType::MetaData("assets/sprites/r-typesheet26.gif", GameEngine::Entity::EntityType::Enemy);
    //      m_entityFactory->createFromNetwork(compId, compMetaData);
    //    }
  }

  std::vector<GameEngine::ECS::Entity> RtypeScene::getEntities()
  {
    return m_entities;
  }

} // namespace Server::Game