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
#include "gameEngine/component/Parallax.hpp"
#include "gameEngine/component/Hitbox.hpp"
#include "gameEngine/component/Text.hpp"
#include "gameEngine/component/UiElement.hpp"

#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/system/RegistryHolder.hpp"
#include "gameEngine/ecs/Signature.hpp"

#include "gameEngine/event/EventRegistry.hpp"
#include "gameEngine/system/Animation.hpp"
#include "gameEngine/system/EcsSerializer.hpp"
#include "gameEngine/system/InputCatcher.hpp"
#include "gameEngine/system/Physics.hpp"
#include "gameEngine/system/Renderer.hpp"
#include "gameEngine/system/TextRenderer.hpp"
#include "gameEngine/system/Parallax.hpp"
#include "gameEngine/system/Collider.hpp"
#include "gameEngine/system/ControlableEntity.hpp"
#include "gameEngine/system/Spawning.hpp"
#include "gameEngine/system/NetworkEventPusher.hpp"
#include "gameEngine/system/UI.hpp"

#include <memory>
#include <utility>

namespace GameEngine::Builder
{

  RegistryBuilder::RegistryBuilder()
    : m_registry {std::make_shared<GameEngine::ECS::Registry>()}
  {
  }

  std::shared_ptr<GameEngine::ECS::Registry> RegistryBuilder::getResult()
  {
    return std::move(m_registry);
  }

  void RegistryBuilder::buildFrom(std::shared_ptr<GameEngine::ECS::Registry> existingRegistry)
  {
    m_registry = std::move(existingRegistry);
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
    registerComponent<ComponentRType::Parallax>();
    registerComponent<ComponentRType::Hitbox>();
    registerComponent<ComponentRType::Text>();
    registerComponent<ComponentRType::UIElement>();
  }

  void RegistryBuilder::buildSystemAnimation()
  {
    GameEngine::ECS::Signature signature;
    m_registry->registerSystem<GameEngine::System::Animation>();

    signature.set(m_registry->getComponentType<ComponentRType::Displayable>());
    signature.set(m_registry->getComponentType<ComponentRType::Transform>());
    m_registry->setSystemSignature<GameEngine::System::Animation>(signature);
  }

  void RegistryBuilder::buildSystemCollider()
  {
    using SystemType = GameEngine::System::Collider;
    GameEngine::ECS::Signature signature;
    m_registry->registerSystem<SystemType>();

    signature.set(m_registry->getComponentType<ComponentRType::Hitbox>());
    signature.set(m_registry->getComponentType<ComponentRType::Displayable>());
    m_registry->setSystemSignature<SystemType>(signature);
  }

  void RegistryBuilder::buildSystemEcsSerializer()
  {
    using SystemType = GameEngine::System::EcsSerializer;
    GameEngine::ECS::Signature signature;
    m_registry->registerSystem<SystemType>();

    signature.set(m_registry->getComponentType<ComponentRType::MetaData>());
    signature.set(m_registry->getComponentType<ComponentRType::NetworkedEntity>());
    signature.set(m_registry->getComponentType<ComponentRType::Position>());
    signature.set(m_registry->getComponentType<ComponentRType::Transform>());
    signature.set(m_registry->getComponentType<ComponentRType::Displayable>());
    m_registry->setSystemSignature<SystemType>(signature);
  }

  void RegistryBuilder::buildSystemControlableEntity()
  {
    using SystemType = GameEngine::System::ControlableEntity;
    GameEngine::ECS::Signature signature;
    m_registry->registerSystem<SystemType>();

    signature.set(m_registry->getComponentType<ComponentRType::NetworkedEntity>());
    signature.set(m_registry->getComponentType<ComponentRType::Transform>());
    signature.set(m_registry->getComponentType<ComponentRType::Position>());
    m_registry->setSystemSignature<SystemType>(signature);
  }

  void RegistryBuilder::buildSystemInputCatcher()
  {
    using SystemType = GameEngine::System::InputCatcher;
    GameEngine::ECS::Signature signature;
    m_registry->registerSystem<SystemType>();

    signature.set(m_registry->getComponentType<ComponentRType::Displayable>());
    m_registry->setSystemSignature<SystemType>(signature);
  }

  void RegistryBuilder::buildSystemNetworkEventPusher()
  {
    using SystemType = GameEngine::System::NetworkEventPusher;
    GameEngine::ECS::Signature signature;
    m_registry->registerSystem<SystemType>();

    signature.set(m_registry->getComponentType<ComponentRType::Position>());
    m_registry->setSystemSignature<SystemType>(signature);
  }

  void RegistryBuilder::buildSystemParallax()
  {
    using SystemType = GameEngine::System::Parallax;
    GameEngine::ECS::Signature signature;
    m_registry->registerSystem<SystemType>();

    signature.set(m_registry->getComponentType<ComponentRType::Parallax>());
    signature.set(m_registry->getComponentType<ComponentRType::Transform>());
    signature.set(m_registry->getComponentType<ComponentRType::Position>());
    signature.set(m_registry->getComponentType<ComponentRType::Displayable>());
    m_registry->setSystemSignature<SystemType>(signature);
  }

  void RegistryBuilder::buildSystemPhysics()
  {
    using SystemType = GameEngine::System::Physics;
    GameEngine::ECS::Signature signature;
    m_registry->registerSystem<SystemType>();

    signature.set(m_registry->getComponentType<ComponentRType::Transform>());
    signature.set(m_registry->getComponentType<ComponentRType::Position>());
    signature.set(m_registry->getComponentType<ComponentRType::Displayable>());
    m_registry->setSystemSignature<SystemType>(signature);
  }

  void RegistryBuilder::buildSystemRenderer()
  {
    using SystemType = GameEngine::System::Renderer;
    GameEngine::ECS::Signature signature;
    m_registry->registerSystem<SystemType>();

    signature.set(m_registry->getComponentType<ComponentRType::Displayable>());
    m_registry->setSystemSignature<SystemType>(signature);
  }

  void RegistryBuilder::buildSystemTextRenderer()
  {
    using SystemType = GameEngine::System::TextRenderer;
    GameEngine::ECS::Signature signature;
    m_registry->registerSystem<SystemType>();

    signature.set(m_registry->getComponentType<ComponentRType::Text>());
    m_registry->setSystemSignature<SystemType>(signature);
  }

  void RegistryBuilder::buildSystemSpawning()
  {
    using SystemType = GameEngine::System::Spawn;
    GameEngine::ECS::Signature signature;
    m_registry->registerSystem<SystemType>();

    signature.set(m_registry->getComponentType<ComponentRType::Position>());
    signature.set(m_registry->getComponentType<ComponentRType::NetworkedEntity>());
    signature.set(m_registry->getComponentType<ComponentRType::MetaData>());
    m_registry->setSystemSignature<SystemType>(signature);
  }

  void RegistryBuilder::buildSystemUI()
  {
    using SystemType = GameEngine::System::UI;
    GameEngine::ECS::Signature signature;
    m_registry->registerSystem<SystemType>();

    signature.set(m_registry->getComponentType<ComponentRType::Position>());
    signature.set(m_registry->getComponentType<ComponentRType::Clickable>());
    signature.set(m_registry->getComponentType<ComponentRType::Displayable>());
    signature.set(m_registry->getComponentType<ComponentRType::UIElement>());
    m_registry->setSystemSignature<SystemType>(signature);
  }

  void RegistryBuilder::feedSystemHolder(
    std::shared_ptr<ECS::Registry> ecsRegistry,
    std::shared_ptr<Event::EventRegistry> eventRegistry)
  {
    auto &&systems = ecsRegistry->getSystems();

    for (auto &[typeId, system_ptr] : systems) {
      if (auto sys = std::dynamic_pointer_cast<ECS::RegistryHolder>(system_ptr)) {
        sys->setEcsRegistry(ecsRegistry);
        sys->setEventRegistry(eventRegistry);
      }
    }
  }

}; // namespace GameEngine::Builder