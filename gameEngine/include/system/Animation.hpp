//
// Created by Alexandre Decobert on 17/12/2023.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "ecs/Mediator.hpp"
#include "ecs/system/System.hpp"
#include "component/Transform.hpp"
#include "component/Sprite.hpp"
#include "gfx/sfml/SfmlDisplay.hpp"
#include "component/Gravity.hpp"

class Animation : public System {

  /// \brief update the position of the sprite and display it
  /// \param component_manager
  /// \param entity
  /// \param window

 public:
  void update(std::shared_ptr<ComponentManager>& component_manager, Entity entity, sf::RenderWindow& window)
  {
        SfmlDisplay sfml_display;

        auto& transform = component_manager->getComponent<ComponentRType::Transform>(entity);
        auto& sprite = component_manager->getComponent<ComponentRType::Sprite>(entity);
        auto& gravity = component_manager->getComponent<ComponentRType::Gravity>(entity);

        sfml_display.setPosition(sprite.object, transform.position);
        sfml_display.display(window, sprite.object);
  }
};
