//
// Created by edouard on 12/21/23.
//

#include "scene/WelcomeScene.hpp"
#include "gameEngine/component/Clickable.hpp"
#include "gameEngine/component/Displayable.hpp"
#include "gameEngine/component/Position.hpp"
#include "gameEngine/component/Transform.hpp"
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/Signature.hpp"
#include "network/system/Network.hpp"

namespace Client
{

  WelcomeScene::WelcomeScene(Network& network)
    : m_network {network}
  {
    initRegistries();
    initEntities();
  }

  void WelcomeScene::initRegistries()
  {
    GameEngine::Scene::SimpleScene::initRegistries();
    initCustomSystem();
  }

  void WelcomeScene::initCustomSystem()
  {
    using NetworkSystem = Client::System::KeyboardInputHandler;
    GameEngine::ECS::Signature signature;
    m_ecsRegistry->registerSystem<NetworkSystem>();
    signature.set(m_ecsRegistry->getComponentType<ComponentRType::Displayable>());
    m_ecsRegistry->setSystemSignature<NetworkSystem>(signature);
  }

  void WelcomeScene::initEntities()
  {
    auto enttBackground = m_ecsRegistry->createEntity();
    m_entities.push_back(enttBackground);
    m_ecsRegistry->addComponent(
      enttBackground,
      ComponentRType::Displayable(GameEngine::Asset::getTexture("assets/welcome/bg.jpg")));

    auto enttButton = m_ecsRegistry->createEntity();
    m_entities.push_back(enttButton);
    m_ecsRegistry->addComponent(
      enttButton,
      ComponentRType::Displayable(GameEngine::Asset::getTexture("assets/welcome/rtype_button.jpg")));
    m_ecsRegistry->addComponent(enttButton, ComponentRType::Transform());
    m_ecsRegistry->addComponent(enttButton, ComponentRType::Position(615, 480));
    m_ecsRegistry->addComponent(enttButton, ComponentRType::Clickable(615, 480, 690, 120));

    m_entityFactory = std::make_unique<GameEngine::Entity::EntityFactory>(m_entities, *m_ecsRegistry);
  }

} // namespace Client
