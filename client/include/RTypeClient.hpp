//
// Created by Xavier VINCENT on 17/12/23.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

#include <spdlog/spdlog.h>

#include <iostream>
#include <iomanip>
#include <sstream>
#include <memory>
#include <optional>
#include <functional>
#include <string>
#include <vector>
#include <exception>
#include <unordered_map>
#include <thread>
#include <ostream>

// Game Engine
#include "gameEngine/component/Gravity.hpp"
#include "gameEngine/component/Sprite.hpp"
#include "gameEngine/component/Transform.hpp"
#include "gameEngine/ecs/component/Component.hpp"
#include "gameEngine/ecs/component/ComponentManager.hpp"
#include "gameEngine/ecs/entity/Entity.hpp"
#include "gameEngine/ecs/entity/EntityManager.hpp"
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/RegistryBuilder.hpp"
#include "gameEngine/ecs/Signature.hpp"
#include "gameEngine/network/Commands.hpp"
#include "gameEngine/network/Messages.hpp"
#include "gameEngine/network/MessageType.hpp"
#include "gameEngine/network/Responses.hpp"
#include "gameEngine/network/Statuses.hpp"
#include "gameEngine/scene/IScene.hpp"
#include "gameEngine/scene/SceneManager.hpp"
#include "gameEngine/system/Animation.hpp"
#include "gameEngine/system/Keyboard.hpp"
#include "gameEngine/system/Physics.hpp"
#include "gameEngine/system/Renderer.hpp"
#include "gameEngine/UI/Window.hpp"

// Client
#include "graphics/GUI.hpp"
#include "network/commands/IHandler.hpp"
#include "network/commands/Tracker.hpp"
#include "network/tools/Logs.hpp"
#include "network/Constants.hpp"
#include "network/Network.hpp"
#include "network/system/Keyboard.hpp"
#include "scene/Manager.hpp"
#include "scene/Game.hpp"
#include "Client.hpp"

// Commands
#include "network/commands/ConnectToServer.hpp"
#include "network/commands/Input.hpp"
#include "network/commands/JoinRoom.hpp"
#include "network/commands/StartGame.hpp"
#include "network/commands/UpdateName.hpp"
