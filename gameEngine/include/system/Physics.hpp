//
// Created by Alexandre Decobert on 16/12/2023.
//

#pragma once

#include "component/Transform.hpp"
#include "component/Gravity.hpp"
#include "ecs/Mediator.hpp"
#include "ecs/system/System.hpp"
#include <chrono>

class Physics: public System
{
 public:
  static void update(Mediator &mediator, std::vector<Entity> &entities, double delta)
  {
    static auto lastUpdate = std::chrono::steady_clock::now();
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - lastUpdate);

    if (elapsed.count() >= delta) {
      for (auto const& entity : entities) {
        auto& transform =
            mediator.getComponent<ComponentRType::Transform>(entity);
        auto const& gravity =
            mediator.getComponent<ComponentRType::Gravity>(entity);
        transform.position.y += gravity.force;
      }
      lastUpdate = now;
    }
  }
};