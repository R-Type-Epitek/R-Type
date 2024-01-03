//
// Created by Xavier VINCENT on 24/12/23.
//

#pragma once
#include "network/Network.hpp"
#include "network/commands/IHandler.hpp"

namespace Client
{
  /**
   * @brief Handler for update name commands in a networked environment.
   *
   * UpdateNameCommandHandler is responsible for managing update name commands
   * and their interactions with the network. It implements the ICommandHandler
   * interface, providing specific functionality for handling requests to update a user's name.
   */
  class UpdateNameCommandHandler : public ICommandHandler {
   public:
    /**
     * @brief Construct a new UpdateNameCommandHandler object.
     *
     * @param network Reference to the Network instance used for handling
     *                network communications.
     */
    UpdateNameCommandHandler(Network& network);

    /**
     * @brief Set the name for the update name command.
     *
     * @param name The new name to be set.
     */
    void setName(std::string name);

    /**
     * @brief Get the name associated with the update name command.
     *
     * @return const std::string& Reference to the name currently set for
     *                            the update name command.
     */
    const std::string& getName() const;

    /**
     * @brief Send the update name command to the server.
     *
     * Implements the send method from ICommandHandler, specifically handling
     * the sending of update name commands to the server.
     */
    void send() override;

    /**
     * @brief Handle the server's response to the update name command.
     *
     * Implements the onResponse method from ICommandHandler, processing the
     * response received from the server in relation to the update name command sent.
     *
     * @param response Pointer to the response received from the server.
     */
    void onResponse(Response* response) override;

   protected:
   private:
    Network& network; ///< Reference to the network instance for communication.
    std::string name; ///< The name associated with the update command.
  };
} // namespace Client
