//
// Created by lsg on 17/12/23.
//

#pragma once

#include "component/Gravity.hpp"
#include "component/Transform.hpp"
#include "ecs/Mediator.hpp"
#include "ecs/system/System.hpp"

namespace ComponentRType {
struct KeyInput {
  KeyInput() = default;
  KeyInput(KeyInput const&) = default;
  KeyInput(KeyInput&&) noexcept = default;
  ~KeyInput() = default;

  void update(std::shared_ptr<ComponentManager>& component_manager,
              Entity entity, sf::RenderWindow window,
              std::vector<Entity> const& entities) {
    for (Entity entity : entities) {
      auto components = component_manager->getComponentsWithEntity(entity);

      if (components.find(typeid(Transform).name()) != components.end() &&
          components.find(typeid(KeyInput).name()) != components.end()) {
        float velX = 0.0f;
        float velY = 0.0f;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) {
          velY -= 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
          velY += 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
          velX -= 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
          velX += 1.0f;
        }

        auto& transform =
            component_manager->getComponent<ComponentRType::Transform>(entity);
        auto& gravity =
            component_manager->getComponent<ComponentRType::Gravity>(entity);

        transform.position.x = velX;
        transform.position.y = velY;

        transform.position.x += velX * transform.speed;
        transform.position.y += velY * transform.speed;

        transform.position.x =
            std::max(0.0f, std::min(transform.position.x,
                                    static_cast<float>(window.getSize().x)));
        transform.position.y =
            std::max(0.0f, std::min(transform.position.y,
                                    static_cast<float>(window.getSize().y)));
      }
    }
  }
}
};  // namespace ComponentRType
