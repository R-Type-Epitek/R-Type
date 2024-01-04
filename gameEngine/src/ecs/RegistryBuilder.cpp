//
// Created by raphael on 12/22/23.
//

#include "gameEngine/ecs/RegistryBuilder.hpp"

#include "gameEngine/component/NetworkedEntity.hpp"
#include "gameEngine/component/MetaData.hpp"
#include "gameEngine/component/Gravity.hpp"
#include "gameEngine/component/Controllable.hpp"
#include "gameEngine/component/Position.hpp"
#include "gameEngine/component/Transform.hpp"
#include "gameEngine/component/Displayable.hpp"
#include "gameEngine/component/Clickable.hpp"

#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/Signature.hpp"
#include "gameEngine/system/Animation.hpp"
#include "gameEngine/system/EcsSerializer.hpp"
#include "gameEngine/system/Keyboard.hpp"
#include "gameEngine/system/Physics.hpp"
#include "gameEngine/system/Renderer.hpp"
#include "gameEngine/system/Input.hpp"
#include "gameEngine/system/Move.hpp"

#include <memory>
#include <utility>

namespace GameEngine::Builder
{

  RegistryBuilder::RegistryBuilder()
    : m_registry {std::make_unique<GameEngine::ECS::Registry>()}
  {
  }

  std::unique_ptr<GameEngine::ECS::Registry> RegistryBuilder::getResult()
  {
    return std::move(m_registry);
  }

  void RegistryBuilder::registerAllMandatoryComponent()
  {
    registerComponent<ComponentRType::MetaData>();
    registerComponent<ComponentRType::NetworkedEntity>();
    registerComponent<ComponentRType::Gravity>();
    registerComponent<ComponentRType::Controllable>();
    registerComponent<ComponentRType::Position>();
    registerComponent<ComponentRType::Transform>();
    registerComponent<ComponentRType::Clickable>();
    registerComponent<ComponentRType::Displayable>();
  }

  void RegistryBuilder::buildSystemRenderer()
  {
    GameEngine::ECS::Signature signature;
    m_registry->registerSystem<GameEngine::System::Renderer>();

    signature.set(m_registry->getComponentType<ComponentRType::Displayable>());
    m_registry->setSystemSignature<GameEngine::System::Renderer>(signature);
  }

  void RegistryBuilder::buildSystemAnimation()
  {
    GameEngine::ECS::Signature signature;
    m_registry->registerSystem<GameEngine::System::Animation>();

    signature.set(m_registry->getComponentType<ComponentRType::Displayable>());
    signature.set(m_registry->getComponentType<ComponentRType::Transform>());
    m_registry->setSystemSignature<GameEngine::System::Animation>(signature);
  }

  void RegistryBuilder::buildSystemPhysics()
  {
    GameEngine::ECS::Signature signature;
    m_registry->registerSystem<GameEngine::System::Physics>();

    signature.set(m_registry->getComponentType<ComponentRType::Gravity>());
    signature.set(m_registry->getComponentType<ComponentRType::Transform>());
    signature.set(m_registry->getComponentType<ComponentRType::Position>());
    m_registry->setSystemSignature<GameEngine::System::Physics>(signature);
  }

  void RegistryBuilder::buildSystemKeyboard()
  {
    GameEngine::ECS::Signature signature;
    m_registry->registerSystem<GameEngine::System::Keyboard>();

    signature.set(m_registry->getComponentType<ComponentRType::Displayable>());
    m_registry->setSystemSignature<GameEngine::System::Keyboard>(signature);
  }

  void RegistryBuilder::buildSystemEcsSerializer()
  {
    GameEngine::ECS::Signature signature;
    m_registry->registerSystem<GameEngine::System::EcsSerializer>();

    signature.set(m_registry->getComponentType<ComponentRType::MetaData>());
    signature.set(m_registry->getComponentType<ComponentRType::NetworkedEntity>());
    signature.set(m_registry->getComponentType<ComponentRType::Position>());
    signature.set(m_registry->getComponentType<ComponentRType::Transform>());
    m_registry->setSystemSignature<GameEngine::System::EcsSerializer>(signature);
  }

  void RegistryBuilder::buildSystemMove()
  {
    GameEngine::ECS::Signature signature;
    m_registry->registerSystem<GameEngine::System::Move>();

    signature.set(m_registry->getComponentType<ComponentRType::Displayable>());
    signature.set(m_registry->getComponentType<ComponentRType::Position>());
    m_registry->setSystemSignature<GameEngine::System::Move>(signature);
  }

  void RegistryBuilder::buildSystemInput()
  {
    GameEngine::ECS::Signature signature;
    m_registry->registerSystem<GameEngine::System::Input>();

    signature.set(m_registry->getComponentType<ComponentRType::NetworkedEntity>());
    signature.set(m_registry->getComponentType<ComponentRType::Position>());
    m_registry->setSystemSignature<GameEngine::System::Input>(signature);
  }

}; // namespace GameEngine::Builder