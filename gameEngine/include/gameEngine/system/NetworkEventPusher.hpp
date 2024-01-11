//
// Created by raphael on 12/22/23.
//

#pragma once
#include "gameEngine/constants/Keybinds.hpp"
#include "gameEngine/UI/Window.hpp"
#include "gameEngine/component/Displayable.hpp"
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/system/System.hpp"
#include "gameEngine/event/IEventBindable.hpp"
#include "gameEngine/event/Events.hpp"
#include "gameEngine/network/INetworkController.hpp"

#include <deque>

namespace GameEngine::System
{

  class NetworkEventPusher
    : public ECS::System
    , public Event::IEventBindable {
   public:
    void bindEvent(Event::EventRegistry &eventRegistry) final
    {
      eventRegistry.subscribeLambda<Event::KeyboardInput>([this](const Event::IEvent &eventRaw) {
        handleKeyboardEvent(eventRaw);
      });
    }

    void update(Network::INetworkController &networkInstance)
    {
      while (!commandQueue.empty()) {
        auto event = commandQueue.front();
        commandQueue.pop();
        networkInstance.sendKey(event.key);
      }
    };

    void handleKeyboardEvent(const GameEngine::Event::IEvent &eventRaw)
    {
      auto event = dynamic_cast<const GameEngine::Event::KeyboardInput &>(eventRaw);
      commandQueue.push(event);
    }

   private:
    std::queue<GameEngine::Event::KeyboardInput>
      commandQueue {}; ///< Queue for storing keyboard input events.
  };
} // namespace Client::System::Network
