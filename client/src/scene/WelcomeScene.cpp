//
// Created by edouard on 12/21/23.
//

#include "scene/WelcomeScene.hpp"
#include "gameEngine/component/Gravity.hpp"
#include "gameEngine/component/MetaData.hpp"
#include "gameEngine/component/NetworkedEntity.hpp"
#include "gameEngine/component/Displayable.hpp"
#include "gameEngine/component/Clickable.hpp"
#include "gameEngine/component/Position.hpp"
#include "gameEngine/component/Transform.hpp"
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/RegistryBuilder.hpp"
#include "gameEngine/ecs/Signature.hpp"
#include "network/system/Keyboard.hpp"
#include "spdlog/spdlog.h"

namespace Client
{

    WelcomeScene::WelcomeScene(Network& network)
        : m_network {network}
    {
        initRegistry();
        initEntities();
    }

    GameEngine::ECS::Registry& WelcomeScene::getECS()
    {
        return *m_registry;
    }

    GameEngine::Entity::EntityFactory& WelcomeScene::getEntityFactory()
    {
      return *m_entityFactory;
    }

    void WelcomeScene::initRegistry()
    {
        auto builder = GameEngine::Builder::RegistryBuilder();

        // Components
        builder.registerAllMandatoryComponent();

        // Systems
        builder.buildSystemPhysics();
        builder.buildSystemMove();
        builder.buildSystemAnimation();
        builder.buildSystemRenderer();
        builder.buildSystemKeyboard();
        builder.buildSystemEcsSerializer();
        m_registry = builder.getResult();

        // Custom client System
        initCustomSystem();
    }

    void WelcomeScene::initCustomSystem()
    {
        GameEngine::ECS::Signature signature;
        m_registry->registerSystem<System::Network::Keyboard>();
        //    System components
        signature.set(m_registry->getComponentType<ComponentRType::Displayable>());
        m_registry->setSystemSignature<System::Network::Keyboard>(signature);
    }

    void WelcomeScene::initEntities()
    {
        auto enttBackground = m_registry->createEntity();
        m_entities.push_back(enttBackground);
        m_registry->addComponent(enttBackground, ComponentRType::Displayable(GameEngine::Asset::getTexture("assets/welcome/bg.jpg")));

        auto enttButton = m_registry->createEntity();
        m_entities.push_back(enttButton);
        m_registry->addComponent(enttButton, ComponentRType::Displayable(GameEngine::Asset::getTexture("assets/welcome/rtype_button.jpg")));
        m_registry->addComponent(enttButton, ComponentRType::Transform());
        m_registry->addComponent(enttButton, ComponentRType::Position(615, 480));
        m_registry->addComponent(enttButton, ComponentRType::Clickable(615, 480, 690, 120));

        m_entityFactory = std::make_unique<GameEngine::Entity::EntityFactory>(m_entities, *m_registry);
    }
} // namespace Client
