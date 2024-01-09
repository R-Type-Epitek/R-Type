//
// Created by raphael on 12/21/23.
//

#include "scene/GameScene.hpp"
#include "gameEngine/system/Move.hpp"
#include "gameEngine/component/Displayable.hpp"
#include "gameEngine/asset/AssetManager.hpp"
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/Signature.hpp"
#include "gameEngine/event/Events.hpp"
#include "network/system/Keyboard.hpp"
#include "spdlog/spdlog.h"

namespace Client
{

  GameScene::GameScene(Network &network)
    : m_network {network}
  {
    initRegistries();
    initEntities();
  }

  void GameScene::initRegistries()
  {
    GameEngine::Scene::SimpleScene::initRegistries();
    initCustomSystem();

    auto moveSystem = m_ecsRegistry->getSystem<GameEngine::System::Move>();
    m_eventRegistry->subscribe<GameEngine::Event::EventKeyboardInput>(moveSystem);
  }

  void GameScene::initCustomSystem()
  {
    GameEngine::ECS::Signature signature;
    m_ecsRegistry->registerSystem<System::Network::Keyboard>();
    //  System components
    signature.set(m_ecsRegistry->getComponentType<ComponentRType::Displayable>());
    m_ecsRegistry->setSystemSignature<System::Network::Keyboard>(signature);
  }

  void GameScene::initEntities()
  {
    m_entityFactory = std::make_unique<GameEngine::Entity::EntityFactory>(m_entities, *m_ecsRegistry);
    auto enttBackground = m_ecsRegistry->createEntity();
    m_entities.push_back(enttBackground);
    m_ecsRegistry->addComponent<ComponentRType::Displayable>(
      enttBackground,
      ComponentRType::Displayable(GameEngine::Asset::getTexture("assets/background_starfield.png")));
  }

} // namespace Client
