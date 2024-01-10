//
// Created by raphael on 12/22/23.
//

#include "game/rtype/RtypeScene.hpp"
#include "gameEngine/asset/ConfigLoader.hpp"
#include "game/rtype/RtypeScene.hpp"
#include "gameEngine/component/Displayable.hpp"
#include "gameEngine/system/Physics.hpp"
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
    builder.buildSystemCollider();
    m_ecsRegistry = builder.getResult();

    m_eventRegistry = std::make_unique<GameEngine::Event::EventRegistry>();

    auto physicSys = m_ecsRegistry->getSystem<GameEngine::System::Physics>();
    m_eventRegistry->subscribe<GameEngine::Event::EventCollision>(physicSys);
  }

  void RtypeScene::initEntities()
  {
    m_entityFactory = std::make_shared<GameEngine::Entity::EntityFactory>(m_entities, *m_ecsRegistry);

    ConfigLoader::loadEntities(m_entityFactory);
  }

  GameEngine::ECS::Registry& RtypeScene::getEcsRegistry()
  {
    return *m_ecsRegistry;
  }

  std::shared_ptr<GameEngine::ECS::Registry> RtypeScene::getSharedEcsRegistry()
  {
    return m_ecsRegistry;
  }

  GameEngine::Event::EventRegistry& RtypeScene::getEventRegistry()
  {
    return *m_eventRegistry;
  }

  GameEngine::Entity::EntityFactory& RtypeScene::getEntityFactory()
  {
    return *m_entityFactory;
  }

  std::vector<GameEngine::ECS::Entity> RtypeScene::getEntities()
  {
    return m_entities;
  }
} // namespace Server::Game namespace Server::Game