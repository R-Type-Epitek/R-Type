//
// Created by raphael on 1/9/24.
//

#include "gameEngine/scene/SimpleScene.hpp"
#include "gameEngine/ecs/RegistryBuilder.hpp"
#include "gameEngine/event/IEventBindable.hpp"

#include "gameEngine/system/Animation.hpp"
#include "gameEngine/system/NetworkEventPusher.hpp"
#include "gameEngine/system/Physics.hpp"
#include "gameEngine/system/UI.hpp"

namespace GameEngine::Scene
{

  void SimpleScene::initRegistries()
  {
    // ECS
    auto builder = Builder::RegistryBuilder();

    // ECS - Component
    builder.registerAllMandatoryComponent();

    // ECS - Component - System
    builder.buildSystemAnimation();
    builder.buildSystemInputCatcher();
    builder.buildSystemNetworkEventPusher();
    builder.buildSystemPhysics();
    builder.buildSystemRenderer();
    builder.buildSystemTextRenderer();
    builder.buildSystemUI();
    builder.buildSystemEcsSerializer();
    builder.buildSystemParallax();
    m_ecsRegistry = builder.getResult();
  }

  void SimpleScene::initEntities()
  {
    m_entityFactory = std::make_unique<GameEngine::Entity::EntityFactory>(m_entities, *m_ecsRegistry);
  }

  void SimpleScene::initEvents()
  {
    m_eventRegistry = std::make_unique<Event::EventRegistry>();

    auto&& systems = getEcsRegistry().getSystems();
    for (auto& [typeId, system_ptr] : systems) {
      if (auto sys = std::dynamic_pointer_cast<Event::IEventBindable>(system_ptr)) {
        sys->bindEvent(*m_eventRegistry);
      }
    }
  }

  const std::vector<ECS::Entity>& SimpleScene::getEntities()
  {
    return m_entities;
  }

  GameEngine::Entity::EntityFactory& SimpleScene::getEntityFactory()
  {
    return *m_entityFactory;
  }

  ECS::Registry& SimpleScene::getEcsRegistry()
  {
    return *m_ecsRegistry;
  }

  std::shared_ptr<ECS::Registry> SimpleScene::getSharedEcsRegistry()
  {
    return m_ecsRegistry;
  }

  Event::EventRegistry& SimpleScene::getEventRegistry()
  {
    return *m_eventRegistry;
  }

  void SimpleScene::onUpdate(size_t df)
  {
    auto& ecsRegistry = getEcsRegistry();
    try {
      {
        auto system = ecsRegistry.getSystem<GameEngine::System::Animation>();
        system->update(df);
      }
      {
        auto system = ecsRegistry.getSystem<GameEngine::System::Physics>();
        system->updateClient();
      }
      {
        auto system = ecsRegistry.getSystem<GameEngine::System::UI>();
        system->update();
      }
    } catch (const std::exception& e) {
      spdlog::error("[Client update] Error: {}", e.what());
    }
  }

} // namespace GameEngine::Scene
