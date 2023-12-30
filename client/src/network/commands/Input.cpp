//
// Created by Xavier VINCENT on 24/12/23.
//

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Window.hpp>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <exception>
#include <functional>
#include <iomanip>
#include <iostream>
#include <memory>
#include <optional>
#include <ostream>
#include <spdlog/spdlog.h>
#include <sstream>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

// Game Engine
#include "gameEngine/UI/Window.hpp"
#include "gameEngine/component/Gravity.hpp"
#include "gameEngine/component/Sprite.hpp"
#include "gameEngine/component/Transform.hpp"
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/RegistryBuilder.hpp"
#include "gameEngine/ecs/Signature.hpp"
#include "gameEngine/ecs/component/Component.hpp"
#include "gameEngine/ecs/component/ComponentManager.hpp"
#include "gameEngine/ecs/entity/Entity.hpp"
#include "gameEngine/ecs/entity/EntityManager.hpp"
#include "gameEngine/network/Commands.hpp"
#include "gameEngine/network/MessageType.hpp"
#include "gameEngine/network/Messages.hpp"
#include "gameEngine/network/Responses.hpp"
#include "gameEngine/network/Statuses.hpp"
#include "gameEngine/scene/IScene.hpp"
#include "gameEngine/scene/SceneManager.hpp"
#include "gameEngine/system/Animation.hpp"
#include "gameEngine/system/Keyboard.hpp"
#include "gameEngine/system/Physics.hpp"
#include "gameEngine/system/Renderer.hpp"

// Client
#include "Client.hpp"
#include "graphics/GUI.hpp"
#include "network/Constants.hpp"
#include "network/Network.hpp"
#include "network/commands/IHandler.hpp"
#include "network/commands/Tracker.hpp"
#include "network/system/Keyboard.hpp"
#include "network/tools/Logs.hpp"
#include "scene/GameScene.hpp"
#include "scene/SceneManager.hpp"
#include "spdlog/spdlog.h"

// Commands
#include "network/commands/ConnectToServer.hpp"
#include "network/commands/Input.hpp"
#include "network/commands/JoinRoom.hpp"
#include "network/commands/StartGame.hpp"
#include "network/commands/UpdateName.hpp"

namespace Client
{
  InputCommandHandler::InputCommandHandler(Network& network)
    : network(network)
  {
  }

  void InputCommandHandler::setKey(std::string key)
  {
    this->key = key;
  }

  const std::string& InputCommandHandler::getKey() const
  {
    return this->key;
  }

  void InputCommandHandler::send()
  {
    InputData data;
    strcpy(data.key, this->key.c_str());
    char dataBuffer[sizeof(data)];
    memcpy(dataBuffer, &data, sizeof(data));

    this->network.sendMessage(INPUT_COMMAND, dataBuffer, sizeof(data));
  }

  void InputCommandHandler::onResponse(Response* response)
  {
    InputData* data = (InputData*)response->data;

    spdlog::info("Input received: {}", data->key);
  }
};
