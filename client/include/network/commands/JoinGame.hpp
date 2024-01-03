//
// Created by Xavier VINCENT on 24/12/23.
//

#pragma once
#include "network/Network.hpp"
#include "network/commands/IHandler.hpp"

namespace Client
{
  /**
   * @brief Handler for join game commands in a networked environment.
   *
   * JoinGameCommandHandler is responsible for managing join game commands
   * and their interactions with the network. It extends the ICommandHandler
   * interface, providing specific implementations for handling join game requests.
   */
  class JoinGameCommandHandler : public ICommandHandler {
   public:
    /**
     * @brief Construct a new JoinGameCommandHandler object.
     *
     * @param network Reference to the Network instance used for handling
     *                network communications.
     */
    JoinGameCommandHandler(Network& network);

    /**
     * @brief Set the room ID for the join game command.
     *
     * @param roomId The ID of the room to join.
     */
    void setRoomId(int roomId);

    /**
     * @brief Get the room ID associated with the join game command.
     *
     * @return int The ID of the room to join.
     */
    int getRoomId() const;

    /**
     * @brief Send the join game command to the server.
     *
     * Implements the send method from ICommandHandler, specifically handling
     * the sending of join game commands to the server.
     */
    void send() override;

    /**
     * @brief Handle the server's response to the join game command.
     *
     * Implements the onResponse method from ICommandHandler, processing the
     * response received from the server in relation to the join game command sent.
     *
     * @param response Pointer to the response received from the server.
     */
    void onResponse(Response* response) override;

   protected:
   private:
    Network& network; ///< Reference to the network instance for communication.
    int roomId;       ///< The ID of the room to join.
  };
} // namespace Client
