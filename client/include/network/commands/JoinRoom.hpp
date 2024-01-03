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
   * JoinRoomCommandHandler is responsible for managing join room commands
   * and their interactions with the network. It implements the ICommandHandler
   * interface, providing specific functionality for handling join room requests.
   */
  class JoinRoomCommandHandler : public ICommandHandler {
   public:
    /**
     * @brief Construct a new JoinRoomCommandHandler object.
     *
     * @param network Reference to the Network instance used for handling
     *                network communications.
     */
    JoinRoomCommandHandler(Network& network);

    /**
     * @brief Set the room ID for the join room command.
     *
     * @param roomId The ID of the room to join.
     */
    void setRoomId(int roomId);

    /**
     * @brief Get the room ID associated with the join room command.
     *
     * @return int The ID of the room currently set to join.
     */
    int getRoomId() const;

    /**
     * @brief Send the join room command to the server.
     *
     * Implements the send method from ICommandHandler, specifically handling
     * the sending of join room commands to the server.
     */
    void send() override;

    /**
     * @brief Handle the server's response to the join room command.
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
    int roomId;       ///< The ID of the room to join.
  };
} // namespace Client
