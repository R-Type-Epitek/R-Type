//
// Created by Alexandre Decobert on 16/12/2023.
//

#pragma once

#include "gameEngine/component/Gravity.hpp"
#include "gameEngine/component/Transform.hpp"
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/system/System.hpp"
#include <chrono>
#include <iostream>
#include <memory>

namespace GameEngine::ECS {

class Physics : public System {
 public:
  /// \brief Apply the physics to the entity
  /// \param std::shared_ptr<ComponentManager>&
  /// \param Entity
  /// \param sf::RenderWindow&

  void update(int test1, int test2) {
    std::cout << "test " << test1 << " " << test2 << std::endl;
    std::cout << "size " << m_entities.size() << std::endl;
    //    double delta = 0.5f;
    //
    //    static auto lastUpdate = std::chrono::steady_clock::now();
    //    auto now = std::chrono::steady_clock::now();
    //    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - lastUpdate);
    //
    //    if (elapsed.count() >= delta) {
    //      auto& transform = component_manager->getComponent<ComponentRType::Transform>(entity);
    //      //      auto& gravity = component_manager->getComponent<ComponentRType::Gravity>(entity);
    //
    //      if (transform.position.y < 500) {
    //        transform.position.y += 1;
    //      }
    //      lastUpdate = now;
    //    }
  }
};
}  // namespace GameEngine::ECS
