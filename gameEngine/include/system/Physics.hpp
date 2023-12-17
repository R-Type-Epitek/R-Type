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
  void update(std::unordered_map<const char*, std::shared_ptr<IComponentArray>> components, Entity entity, sf::RenderWindow& window) {
      double delta = 0.5f;
      double sub = 1;
      static auto lastUpdate = std::chrono::steady_clock::now();
      auto now = std::chrono::steady_clock::now();
      auto elapsed =
          std::chrono::duration_cast<std::chrono::seconds>(now - lastUpdate);

      if (elapsed.count() >= delta) {
        auto transformComponentArray = std::static_pointer_cast<ComponentArray<ComponentRType::Transform>>(components.at("Transform"));
        ComponentRType::Transform& transform = transformComponentArray->getData(entity);
        auto gravityComponentArray = std::static_pointer_cast<ComponentArray<ComponentRType::Gravity>>(components.at("Gravity"));
        ComponentRType::Gravity& gravity = gravityComponentArray->getData(entity);

        if (transform.position.y < 500) {
          transform.position.y += 1;
        }
        lastUpdate = now;
      }
  }
};