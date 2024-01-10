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
#include "network/system/Network.hpp"
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
    using NetworkSystem = Client::System::KeyboardInputHandler;
    GameEngine::ECS::Signature signature;
    auto sys = m_ecsRegistry->registerSystem<NetworkSystem>();
    signature.set(m_ecsRegistry->getComponentType<ComponentRType::Displayable>());
    m_ecsRegistry->setSystemSignature<NetworkSystem>(signature);

    //    subscribe to network event
    m_eventRegistry->subscribe<GameEngine::Event::EventKeyboardInput>(sys);
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
