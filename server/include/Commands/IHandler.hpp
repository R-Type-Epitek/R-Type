//
// Created by Xavier VINCENT on 20/12/2023.
//

#pragma once

#include "RTypeNetwork.hpp"
#include "gameEngine/network/Messages.hpp"
#include "gameEngine/network/Responses.hpp"

namespace Network {
/**
 * @brief Interface for handling network commands.
 *
 * ICommandHandler provides an interface for processing network commands
 * received from clients. It includes methods for checking authorization
 * and handling specific commands.
 */
class ICommandHandler {
 public:
  /**
   * @brief Virtual destructor for interface.
   */
  virtual ~ICommandHandler() = default;

  /**
   * @brief Checks if a client is authorized.
   *
   * Determines if the given client is authorized to execute commands.
   *
   * @param clientId The identifier of the client.
   * @return True if the client is authorized, false otherwise.
   */
  virtual bool isAuthorized(int clientId) = 0;

  /**
   * @brief Handles a received command.
   *
   * Processes the given command message and generates a response.
   *
   * @param message Pointer to the message to be handled.
   * @return A Response object representing the outcome of the command.
   */
  virtual Response handleCommand(Message* message) = 0;
};
}  // namespace Network
