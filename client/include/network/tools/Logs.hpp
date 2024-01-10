//
// Created by Xavier VINCENT on 24/12/2023.
//

#pragma once
#include "gameEngine/network/Commands.hpp"
#include "gameEngine/network/MessageType.hpp"
#include "gameEngine/network/Messages.hpp"
#include "gameEngine/network/Responses.hpp"
#include "gameEngine/network/Statuses.hpp"
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
