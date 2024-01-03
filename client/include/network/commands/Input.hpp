//
// Created by Xavier VINCENT on 24/12/23.
//

#pragma once
#include "network/Network.hpp"
#include "network/commands/IHandler.hpp"

namespace Client
{
  /**
   * @brief Handler for input commands in a networked environment.
   *
   * InputCommandHandler is responsible for managing input-related commands
   * and their interaction with the network. It extends the ICommandHandler
   * interface, providing specific implementations for input command handling.
   */
  class InputCommandHandler : public ICommandHandler {
   public:
    /**
     * @brief Construct a new InputCommandHandler object.
     *
     * @param network Reference to the Network instance used for handling
     *                network communications.
     */
    InputCommandHandler(Network& network);

    /**
     * @brief Set the key for the input command.
     *
     * @param key The key to be set for this input command.
     */
    void setKey(std::string key);

    /**
     * @brief Get the key associated with the input command.
     *
     * @return const std::string& Reference to the key currently set for
     *                            this input command.
     */
    const std::string& getKey() const;

    /**
     * @brief Send the input command to the server.
     *
     * Implements the send method from ICommandHandler, specifically handling
     * the sending of input commands to the server.
     */
    void send() override;

    /**
     * @brief Handle the server's response to the input command.
     *
     * Implements the onResponse method from ICommandHandler, processing the
     * response received from the server in relation to the input command sent.
     *
     * @param response Pointer to the response received from the server.
     */
    void onResponse(Response* response) override;

   protected:
   private:
    Network& network; ///< Reference to the network instance for communication.
    std::string key;  ///< The key associated with the input command.
  };
} // namespace Client
