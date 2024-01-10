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
    builder.buildSystemCollider();
    m_ecsRegistry = builder.getResult();
  }

  void SimpleScene::initEntities()
  {
    m_entityFactory = std::make_unique<GameEngine::Entity::EntityFactory>(m_entities, *m_ecsRegistry);
  }

  void SimpleScene::initEvents()
  {
    m_eventRegistry = std::make_unique<Event::EventRegistry>();
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
  }

} // namespace GameEngine::Scene
