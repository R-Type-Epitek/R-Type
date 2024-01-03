//
// Created by Xavier VINCENT on 24/12/23.
//

#pragma once
#include "gameEngine/network/Responses.hpp"

namespace Client
{
  /**
     * @brief Abstract class representing a command handler in the client.
     *
     * ICommandHandler provides an interface for handling commands and their
     * responses in the client part of a game engine. It defines the basic
     * structure for sending commands and processing their responses.
     */
  class ICommandHandler {
   public:
    /**
     * @brief Virtual destructor for ICommandHandler.
     *
     * Ensures that destructors in derived classes are called correctly.
     */
    virtual ~ICommandHandler() = default;

    /**
     * @brief Send a command to the server.
     *
     * This function is a pure virtual function and needs to be implemented
     * in derived classes to handle the sending of commands to the server.
     */
    virtual void send() = 0;

    /**
     * @brief Handle the response received from the server.
     *
     * This function is a pure virtual function and should be implemented
     * in derived classes to process the response received from the server
     * after a command is sent.
     *
     * @param response Pointer to the response received from the server.
     */
    virtual void onResponse(Response *response) = 0;
  };
} // namespace Client
