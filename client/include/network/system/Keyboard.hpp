//
// Created by raphael on 12/22/23.
//

#pragma once

#include "gameEngine/UI/Window.hpp"
#include "gameEngine/component/Sprite.hpp"
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/system/System.hpp"
#include "network/Network.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace Client::System::Network {

class Keyboard : public GameEngine::ECS::System {
 public:
  void update(GameEngine::UI::WindowContext& ctx, ::Client::Network& network) {
    if (ctx.event.type != sf::Event::KeyPressed) {
      return;
    }
    auto& eventKey = ctx.event.key.code;
    if (eventKey == sf::Keyboard::Up) network.sendKey("UP");
    if (eventKey == sf::Keyboard::Down) network.sendKey("DOWN");
    if (eventKey == sf::Keyboard::Left) network.sendKey("LEFT");
    if (eventKey == sf::Keyboard::Right) network.sendKey("RIGHT");
  };
};

}  // namespace Client::System::Network