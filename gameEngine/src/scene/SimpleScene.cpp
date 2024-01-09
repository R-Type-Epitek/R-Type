//
// Created by raphael on 1/9/24.
//

#include "gameEngine/scene/SimpleScene.hpp"
#include "gameEngine/ecs/RegistryBuilder.hpp"

namespace GameEngine::Scene
{

  void SimpleScene::initRegistries()
  {
    // ECS
    auto builder = Builder::RegistryBuilder();

    // ECS - Component
    builder.registerAllMandatoryComponent();

    // ECS - Component - System
    builder.buildSystemPhysics();
    builder.buildSystemMove();
    builder.buildSystemAnimation();
    builder.buildSystemRenderer();
    builder.buildSystemKeyboard();
    builder.buildSystemEcsSerializer();
    builder.buildSystemParallax();
    m_ecsRegistry = builder.getResult();

    // Event
    m_eventRegistry = std::make_unique<Event::EventRegistry>();
  }

  void SimpleScene::initEntities()
  {
  }

  GameEngine::Entity::EntityFactory& SimpleScene::getEntityFactory()
  {
    return *m_entityFactory;
  }

  ECS::Registry& SimpleScene::getEcsRegistry()
  {
    return *m_ecsRegistry;
  }

  Event::EventRegistry& SimpleScene::getEventRegistry()
  {
    return *m_eventRegistry;
  }

} // namespace GameEngine::Scene
