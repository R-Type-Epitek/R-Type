//
// Created by raphael on 12/22/23.
//

#pragma once

#include "gameEngine/constants/Keybinds.hpp"
#include "gameEngine/UI/Window.hpp"
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/event/EventRegistry.hpp"
#include "gameEngine/event/Events.hpp"
#include "gameEngine/ecs/system/System.hpp"

namespace GameEngine::System
{

  class Keyboard : public GameEngine::ECS::System {
   public:
    void update(Event::EventRegistry &eventRegistry, UI::WindowContext &ctx)
    {
      if (ctx.event.type != sf::Event::KeyPressed)
        return;

      Event::EventKeyboardInput event(convertKey(ctx.event.key.code));
      eventRegistry.publish<Event::EventKeyboardInput>(event);
      eventRegistry.publish<Event::EventCollision>(event);
    }

    static GameEngine::Keybinds convertKey(sf::Keyboard::Key key)
    {
      switch (key) {
        case sf::Keyboard::Key::A:
          return GameEngine::Keybinds::A;
        case sf::Keyboard::Key::B:
          return GameEngine::Keybinds::B;
        case sf::Keyboard::Key::C:
          return GameEngine::Keybinds::C;
        case sf::Keyboard::Key::D:
          return GameEngine::Keybinds::D;
        case sf::Keyboard::Key::E:
          return GameEngine::Keybinds::E;
        case sf::Keyboard::Key::F:
          return GameEngine::Keybinds::F;
        case sf::Keyboard::Key::G:
          return GameEngine::Keybinds::G;
        case sf::Keyboard::Key::H:
          return GameEngine::Keybinds::H;
        case sf::Keyboard::Key::I:
          return GameEngine::Keybinds::I;
        case sf::Keyboard::Key::J:
          return GameEngine::Keybinds::J;
        case sf::Keyboard::Key::K:
          return GameEngine::Keybinds::K;
        case sf::Keyboard::Key::L:
          return GameEngine::Keybinds::L;
        case sf::Keyboard::Key::M:
          return GameEngine::Keybinds::M;
        case sf::Keyboard::Key::N:
          return GameEngine::Keybinds::N;
        case sf::Keyboard::Key::O:
          return GameEngine::Keybinds::O;
        case sf::Keyboard::Key::P:
          return GameEngine::Keybinds::P;
        case sf::Keyboard::Key::Q:
          return GameEngine::Keybinds::Q;
        case sf::Keyboard::Key::R:
          return GameEngine::Keybinds::R;
        case sf::Keyboard::Key::S:
          return GameEngine::Keybinds::S;
        case sf::Keyboard::Key::T:
          return GameEngine::Keybinds::T;
        case sf::Keyboard::Key::U:
          return GameEngine::Keybinds::U;
        case sf::Keyboard::Key::V:
          return GameEngine::Keybinds::V;
        case sf::Keyboard::Key::W:
          return GameEngine::Keybinds::W;
        case sf::Keyboard::Key::X:
          return GameEngine::Keybinds::X;
        case sf::Keyboard::Key::Y:
          return GameEngine::Keybinds::Y;
        case sf::Keyboard::Key::Z:
          return GameEngine::Keybinds::Z;
        case sf::Keyboard::Key::Num0:
          return GameEngine::Keybinds::Num0;
        case sf::Keyboard::Key::Num1:
          return GameEngine::Keybinds::Num1;
        case sf::Keyboard::Key::Num2:
          return GameEngine::Keybinds::Num2;
        case sf::Keyboard::Key::Num3:
          return GameEngine::Keybinds::Num3;
        case sf::Keyboard::Key::Num4:
          return GameEngine::Keybinds::Num4;
        case sf::Keyboard::Key::Num5:
          return GameEngine::Keybinds::Num5;
        case sf::Keyboard::Key::Num6:
          return GameEngine::Keybinds::Num6;
        case sf::Keyboard::Key::Num7:
          return GameEngine::Keybinds::Num7;
        case sf::Keyboard::Key::Num8:
          return GameEngine::Keybinds::Num8;
        case sf::Keyboard::Key::Num9:
          return GameEngine::Keybinds::Num9;
        case sf::Keyboard::Key::Left:
          return GameEngine::Keybinds::Left;
        case sf::Keyboard::Key::Right:
          return GameEngine::Keybinds::Right;
        case sf::Keyboard::Key::Up:
          return GameEngine::Keybinds::Up;
        case sf::Keyboard::Key::Down:
          return GameEngine::Keybinds::Down;
        case sf::Keyboard::Key::Escape:
          return GameEngine::Keybinds::Escape;
        case sf::Keyboard::Key::Enter:
          return GameEngine::Keybinds::Enter;
        case sf::Keyboard::Key::Space:
          return GameEngine::Keybinds::Space;
        case sf::Keyboard::Key::BackSpace:
          return GameEngine::Keybinds::Backspace;
        case sf::Keyboard::Key::Comma:
          return GameEngine::Keybinds::Comma;
        default:
          break;
      }
      return GameEngine::Keybinds::Unknown;
    }
  };
} // namespace GameEngine::System
