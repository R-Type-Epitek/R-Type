//
// Created by raphael on 1/14/24.
//

#include "script/EnemySinusoidal.hpp"
#include <cmath>
#include "gameEngine/component/Position.hpp"
#include "gameEngine/component/Transform.hpp"
#include "spdlog/spdlog.h"

namespace Rtype::Script
{
  EnemySinusoidal::EnemySinusoidal(
    std::shared_ptr<GameEngine::ECS::Registry> ecsRegistry,
    std::shared_ptr<GameEngine::Event::EventRegistry> eventRegistry)
    : DataHolder(ecsRegistry, eventRegistry)
  {
  }

  void EnemySinusoidal::subscribeEvent()
  {
    spdlog::info("EnemySinusoidal::subscribeEvent");
  }

  void EnemySinusoidal::execute(int)
  {
    auto &componentManager = m_ecsRegistry->getComponentManager();
    auto &transform = componentManager->getComponent<ComponentRType::Transform>(m_entity);
    auto &position = componentManager->getComponent<ComponentRType::Position>(m_entity);

    static const double amplitude = transform.speed;
    double frequency = position.position.x / 50;

    transform.movement.x = transform.speed;
    transform.movement.y = amplitude * std::sin(frequency);
  }

} // namespace GameEngine::Script
