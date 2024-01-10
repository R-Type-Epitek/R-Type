//
// Created by Xavier VINCENT on 24/12/23.
//

#pragma once
#include "network/Network.hpp"
#include "network/commands/IHandler.hpp"

namespace Client
{
  /**
   * @brief Handler for kick player commands in a networked environment.
   *
   * KickPlayerCommandHandler is responsible for managing kick player commands
   * and their interactions with the network. It implements the ICommandHandler
   * interface, providing specific functionality for handling kick player requests.
   */
  class KickPlayerCommandHandler : public ICommandHandler {
   public:
    /**
     * @brief Construct a new KickPlayerCommandHandler object.
     *
     * @param network Reference to the Network instance used for handling
     *                network communications.
     */
    KickPlayerCommandHandler(Network& network);

    /**
     * @brief Set the client ID for the kick player command.
     *
     * @param roomId The ID of the player to kick.
     */
    void setClientId(int clientId);

    /**
     * @brief Get the client ID associated with the kick player command.
     *
     * @return int The ID of the client currently set to kick.
     */
    int getClientId() const;

    /**
     * @brief Send the kick player command to the server.
     *
     * Implements the send method from ICommandHandler, specifically handling
     * the sending of kick player commands to the server.
     */
    void send() override;

    /**
     * @brief Handle the server's response to the kick player command.
     *
     * Implements the onResponse method from ICommandHandler, processing the
     * response received from the server in relation to the kick player command sent.
     *
     * @param response Pointer to the response received from the server.
     */
    void onResponse(Response* response) override;

   protected:
   private:
    Network& network; ///< Reference to the network instance for communication.
    int clientId;     ///< The ID of the player to kick.
  };
} // namespace Client
