//
// Created by Alexandre Decobert on 17/12/2023.
//

#pragma once

#include "gameEngine/component/Gravity.hpp"
#include "gameEngine/component/Sprite.hpp"
#include "gameEngine/component/Transform.hpp"
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/system/System.hpp"
#include "gameEngine/gfx/sfml/SfmlDisplay.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

namespace GameEngine::System {

class Animation : public GameEngine::ECS::System {
 public:
  /// \brief Updates the position and display of an entity's sprite based on its components.
  /// \param std::shared_ptr<ComponentManager>&
  /// \param Entity
  /// \param sf::RenderWindow&

  void update(std::shared_ptr<ECS::ComponentManager>& component_manager, ECS::Entity entity, sf::RenderWindow& window) {
    SfmlDisplay sfml_display;

    auto& transform = component_manager->getComponent<ComponentRType::Transform>(entity);
    auto& sprite = component_manager->getComponent<ComponentRType::Sprite>(entity);
    //    auto& gravity = component_manager->getComponent<ComponentRType::Gravity>(entity);

    sfml_display.setPosition(sprite.m_object, transform.position);
    sfml_display.display(window, sprite.m_object);
  }
};

}  // namespace GameEngine::System
