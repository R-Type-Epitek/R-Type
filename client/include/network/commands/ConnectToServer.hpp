//
// Created by Xavier VINCENT on 24/12/23.
//

#pragma once

// Client
#include "network/Network.hpp"
#include "network/commands/IHandler.hpp"

namespace Client
{
  /**
   * @brief Handler for connecting to the server command.
   *
   * ConnectToServerCommandHandler is a concrete implementation of the ICommandHandler
   * interface. It is responsible for handling the command to connect to a server
   * within the network context of the game engine.
   */
  class ConnectToServerCommandHandler : public ICommandHandler {
   public:
    /**
     * @brief Construct a new ConnectToServerCommandHandler object.
     *
     * @param network Reference to the Network instance used for establishing
     *                the connection.
     */
    ConnectToServerCommandHandler(Network& network);

    /**
     * @brief Send the connect command to the server.
     *
     * Implements the send method from ICommandHandler to handle the specifics
     * of sending a connect command to the server.
     */
    void send() override;

    /**
     * @brief Handle the server's response to the connect command.
     *
     * Implements the onResponse method from ICommandHandler to process the
     * response received from the server after sending a connect command.
     *
     * @param response Pointer to the response received from the server.
     */
    void onResponse(Response* response) override;

   protected:
   private:
    Network& network; ///< Reference to the network instance used for communication.
  };
} // namespace Client
