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

    transform.movement.x = transform.speed;
    transform.movement.y = -2;
    static const double amplitude = 50.0;
    static double frequency = 0.1;

    transform.movement.x = transform.speed;

    double time = static_cast<double>(df);
    transform.movement.y = amplitude * std::sin(frequency * time);
  }

} // namespace GameEngine::Script