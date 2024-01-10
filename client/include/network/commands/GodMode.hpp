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
   * GodModeCommandHandler is responsible for managing god mode commands
   * and their interactions with the network. It extends the ICommandHandler
   * interface, providing specific implementations for handling god mode requests.
   */
  class GodModeCommandHandler : public ICommandHandler {
   public:
    /**
     * @brief Construct a new GodModeCommandHandler object.
     *
     * @param network Reference to the Network instance used for handling
     *                network communications.
     */
    GodModeCommandHandler(Network& network);

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
     * @brief Send the god mode command to the server.
     *
     * Implements the send method from ICommandHandler, specifically handling
     * the sending of god mode commands to the server.
     */
    void send() override;

    /**
     * @brief Handle the server's response to the god mode command.
     *
     * Implements the onResponse method from ICommandHandler, processing the
     * response received from the server in relation to the god mode command sent.
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
