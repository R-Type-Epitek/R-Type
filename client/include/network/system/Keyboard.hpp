//
// Created by raphael on 12/22/23.
//

#pragma once
#include "gameEngine/constants/Keybinds.hpp"
#include "gameEngine/UI/Window.hpp"
#include "gameEngine/component/Displayable.hpp"
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/system/System.hpp"
#include "network/Network.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace Client::System::Network
{
  /**
   * @brief System class for handling keyboard events in a networked game environment.
   *
   * The Keyboard class is part of the game engine's system and is responsible for
   * detecting and processing keyboard input, particularly the arrow keys, and
   * transmitting these inputs through the network system.
   */
  class Keyboard : public GameEngine::ECS::System {
   public:
    /**
     * @brief Update the system based on keyboard events.
     *
     * This function checks for key press events and sends corresponding commands
     * (like "UP", "DOWN", "LEFT", "RIGHT") to the server using the network system.
     *
     * @param ctx Reference to the WindowContext, containing event data.
     * @param network Reference to the network system for sending key commands.
     */
    void update(GameEngine::UI::WindowContext &, ::Client::Network &) {};

   private:
  };
} // namespace Client::System::Network
