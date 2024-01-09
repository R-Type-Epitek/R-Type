//
// Created by Xavier VINCENT on 24/12/23.
//

#pragma once
#include "network/Network.hpp"
#include "network/commands/IHandler.hpp"

namespace Client
{
  /**
   * @brief Handler for join room commands in a networked environment.
   *
   * JoinRoomAutoCommandHandler is responsible for managing join room commands
   * and their interactions with the network. It implements the ICommandHandler
   * interface, providing specific functionality for handling join room requests.
   * This version of the join room command is used when the client does not
   * specify a room to join, and instead requests to be placed in a room automatically.
   */
  class JoinRoomAutoCommandHandler : public ICommandHandler {
   public:
    /**
     * @brief Construct a new JoinRoomAutoCommandHandler object.
     *
     * @param network Reference to the Network instance used for handling
     *                network communications.
     */
    JoinRoomAutoCommandHandler(Network& network);

    /**
     * @brief Send the join room auto command to the server.
     *
     * Implements the send method from ICommandHandler, specifically handling
     * the sending of join room auto commands to the server.
     */
    void send() override;

    /**
     * @brief Handle the server's response to the join room auto command.
     *
     * Implements the onResponse method from ICommandHandler, processing the
     * response received from the server in relation to the join room command sent.
     *
     * @param response Pointer to the response received from the server.
     */
    void onResponse(Response* response) override;

   protected:
   private:
    Network& network; ///< Reference to the network instance for communication.
  };
} // namespace Client
