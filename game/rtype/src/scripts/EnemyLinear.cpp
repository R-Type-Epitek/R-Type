//
// Created by raphael on 1/14/24.
//

#include "script/EnemyLinear.hpp"
#include "gameEngine/component/Position.hpp"
#include "gameEngine/component/Transform.hpp"
#include "spdlog/spdlog.h"

namespace Rtype::Script
{
  EnemyLinear::EnemyLinear(
    std::shared_ptr<GameEngine::ECS::Registry> ecsRegistry,
    std::shared_ptr<GameEngine::Event::EventRegistry> eventRegistry)
    : DataHolder(ecsRegistry, eventRegistry)
  {
  }

  void EnemyLinear::subscribeEvent()
  {
    spdlog::info("EnemyLinear::subscribeEvent");
  }

  void EnemyLinear::execute(int)
  {
    auto &componentManager = m_ecsRegistry->getComponentManager();
    auto &transform = componentManager->getComponent<ComponentRType::Transform>(m_entity);

    transform.movement.x = transform.speed;
    transform.movement.y = -2;
  }

} // namespace GameEngine::Script