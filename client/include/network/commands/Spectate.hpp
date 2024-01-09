//
// Created by Xavier VINCENT on 24/12/23.
//

#pragma once
#include "network/Network.hpp"
#include "network/commands/IHandler.hpp"

namespace Client
{
  /**
   * @brief Handler for spectate commands in a networked environment.
   *
   * SpectateCommandHandler is responsible for managing spectate commands
   * and their interactions with the network. It extends the ICommandHandler
   * interface, providing specific implementations for handling spectate requests.
   */
  class SpectateCommandHandler : public ICommandHandler {
   public:
    /**
     * @brief Construct a new SpectateCommandHandler object.
     *
     * @param network Reference to the Network instance used for handling
     *                network communications.
     */
    SpectateCommandHandler(Network& network);

    /**
     * @brief Set the room ID for the spectate command.
     *
     * @param roomId The ID of the room to spectate.
     */
    void setRoomId(int roomId);

    /**
     * @brief Get the room ID associated with the spectate command.
     *
     * @return int The ID of the room to spectate.
     */
    int getRoomId() const;

    /**
     * @brief Send the spectate command to the server.
     *
     * Implements the send method from ICommandHandler, specifically handling
     * the sending of spectate commands to the server.
     */
    void send() override;

    /**
     * @brief Handle the server's response to the spectate command.
     *
     * Implements the onResponse method from ICommandHandler, processing the
     * response received from the server in relation to the spectate command sent.
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
