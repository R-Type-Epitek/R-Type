//
// Created by raphael on 12/22/23.
//

#pragma once
#include "gameEngine/constants/Keybinds.hpp"
#include "gameEngine/UI/Window.hpp"
#include "gameEngine/component/Displayable.hpp"
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/system/System.hpp"
#include "gameEngine/event/IEventListener.hpp"
#include "gameEngine/event/Events.hpp"
#include "network/Network.hpp"

#include <deque>

namespace Client::System
{
  /**
   * @brief System class for handling keyboard events in a networked game environment.
   *
   * The Network class is part of the game engine's system and is responsible for
   * detecting and processing keyboard input, particularly the arrow keys, and
   * transmitting these inputs through the network system.
   */
  class KeyboardInputHandler
    : public GameEngine::ECS::System
    , public GameEngine::Event::IEventListener {
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
    void update(::Client::Network &networkInstance)
    {
      while (!commandQueue.empty()) {
        auto event = commandQueue.front();
        commandQueue.pop();
        networkInstance.sendKey(event.getKey());
      }
    };

    void handleEvent(const GameEngine::Event::IEvent &eventRaw) final
    {
      auto event = dynamic_cast<const GameEngine::Event::EventKeyboardInput &>(eventRaw);
      commandQueue.push(event);
    }

   private:
    std::queue<GameEngine::Event::EventKeyboardInput> commandQueue {};
  };
} // namespace Client::System::Network
