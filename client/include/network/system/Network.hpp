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
   * @class KeyboardInputHandler
   * @brief System class for handling keyboard events in a networked game environment.
   */
  class KeyboardInputHandler
    : public GameEngine::ECS::System
    , public GameEngine::Event::IEventListener {
   public:
    /**
     * @brief Update the system based on keyboard events.
     *
     * This function checks for key press events and sends corresponding commands
     * (like "UP", "DOWN", "LEFT", "RIGHT") to the server using the network interface.
     *
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

    /**
     * @brief Handle the keyboard input event.
     *
     * This function is called when a keyboard input event is received. It adds the
     * event to the command queue for processing.
     *
     * @param eventRaw Reference to the raw keyboard input event.
     */
    void handleEvent(const GameEngine::Event::IEvent &eventRaw) final
    {
      auto event = dynamic_cast<const GameEngine::Event::EventKeyboardInput &>(eventRaw);
      commandQueue.push(event);
    }

   private:
    std::queue<GameEngine::Event::EventKeyboardInput>
      commandQueue {}; ///< Queue for storing keyboard input events.
  };
} // namespace Client::System::Network
