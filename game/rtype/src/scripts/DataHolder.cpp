//
// Created by raphael on 1/14/24.
//

#include "script/DataHolder.hpp"

namespace Rtype::Script
{
  DataHolder::DataHolder(
    std::shared_ptr<GameEngine::ECS::Registry> ecsRegistry,
    std::shared_ptr<GameEngine::Event::EventRegistry> eventRegistry)
    : m_ecsRegistry(ecsRegistry)
    , m_eventRegistry(eventRegistry)
  {
  }

  bool DataHolder::isConfigured()
  {
    return ((m_ecsRegistry != nullptr) && (m_eventRegistry != nullptr));
  }

  void DataHolder::attachEntity(const GameEngine::ECS::Entity entity)
  {
    m_entity = entity;
  }

  void DataHolder::attachEcsRegistry(std::shared_ptr<GameEngine::ECS::Registry> ecsRegistry)
  {
    m_ecsRegistry = ecsRegistry;
  }

  void DataHolder::attachEventRegistry(std::shared_ptr<GameEngine::Event::EventRegistry> eventRegistry)
  {
    m_eventRegistry = eventRegistry;
  }
} // namespace GameEngine::Script
