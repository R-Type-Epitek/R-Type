//
// Created by raphael on 12/22/23.
//

#pragma once

#include "gameEngine/UI/Window.hpp"
#include "gameEngine/component/Displayable.hpp"
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/system/System.hpp"
#include "IUpdateSystem.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace GameEngine::System
{

  class Keyboard
    : public GameEngine::ECS::System
    , public IUpdateSystem {
   public:
    void update(GameEngine::ECS::Registry &, GameEngine::UI::WindowContext &) final {
      //TODO REfaccto this Sysytem to implement a keybinds system catcher

      //      if (ctx.event.type != sf::Event::KeyPressed) {
      //        return;
      //      }
      //      sf::Vector2f posEnd {0, 0};
      //      auto& eventKey = ctx.event.key.code;
      //      if (eventKey == sf::Keyboard::Up)
      //        posEnd.y -= 7;
      //      if (eventKey == sf::Keyboard::Down)
      //        posEnd.y += 7;
      //      if (eventKey == sf::Keyboard::Left)
      //        posEnd.x -= 7;
      //      if (eventKey == sf::Keyboard::Right)
      //        posEnd.x += 7;
      //
      //      auto& componentManager = registry.getComponentManager();
      //      for (auto const& entity : m_entities) {
      //        auto& spriteC = componentManager->getComponent<ComponentRType::Displayable>(entity);
      //        spriteC.sprite.setPosition(spriteC.sprite.getPosition() + posEnd);
      //      }
    };
  };
} // namespace GameEngine::System
