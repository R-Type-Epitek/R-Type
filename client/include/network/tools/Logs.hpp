//
// Created by Xavier VINCENT on 24/12/2023.
//

#pragma once
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
#include "spdlog/spdlog.h"

/**
 * @brief Log a message with a specific prefix.
 *
 * This function logs a message, typically used for debugging or informational purposes
 * within the game engine. It formats the message with a given prefix and ensures it
 * is displayed in a consistent manner.
 *
 * @param prefix A string prefix to prepend to the message.
 * @param message Pointer to the Message object to be logged.
 * @param width The width for formatting the output (default is 20).
 */
void logMessage(std::string prefix, Message *message, const int width = 20);

/**
 * @brief Log a response with a specific prefix.
 *
 * This function logs a response from the network or other sources, intended for
 * debugging or tracking purposes within the game engine. It formats the response with
 * a given prefix to ensure consistent and readable output.
 *
 * @param prefix A string prefix to prepend to the response.
 * @param response Pointer to the Response object to be logged.
 * @param width The width for formatting the output (default is 20).
 */
void logResponse(std::string prefix, Response *response, const int width = 20);
