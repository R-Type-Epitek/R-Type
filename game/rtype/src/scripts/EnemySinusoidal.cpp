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

  void EnemySinusoidal::execute(int df)
  {
    auto &componentManager = m_ecsRegistry->getComponentManager();
    auto &transform = componentManager->getComponent<ComponentRType::Transform>(m_entity);
    auto &position = componentManager->getComponent<ComponentRType::Position>(m_entity);

    static const double amplitude = 500.0;
    static const double frequency = 0.1;

    transform.movement.x = transform.speed;

    float y = amplitude * std::sin(frequency * (position.position.x)) / 200;
    transform.movement.y = y;
  }

} // namespace GameEngine::Script
