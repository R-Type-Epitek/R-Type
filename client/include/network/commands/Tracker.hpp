//
// Created by Xavier VINCENT on 24/12/23.
//

#pragma once
#include "network/commands/IHandler.hpp"

#include <chrono>
#include <string>

namespace Client
{
  /**
   * @brief Class for tracking the status of a command.
   *
   * CommandTracker is responsible for storing and managing the information
   * about a specific command, including its name, the time it was sent, and
   * its completion status.
   */
  class CommandTracker {
   public:
    /**
     * @brief Construct a new CommandTracker object.
     *
     * @param command The name of the command being tracked.
     */
    CommandTracker(const std::string &command);

    /**
     * @brief Default destructor for CommandTracker.
     */
    ~CommandTracker() = default;

    /**
     * @brief Get the name of the command.
     *
     * @return const std::string& Reference to the command name.
     */
    const std::string &getCommand() const;

    /**
     * @brief Get the time point when the command was sent.
     *
     * @return const std::chrono::steady_clock::time_point& Reference to the time point
     *                                                        when the command was sent.
     */
    const std::chrono::steady_clock::time_point &getSendTime() const;

    /**
     * @brief Get the completion status of the command.
     *
     * @return bool True if the command has been completed, false otherwise.
     */
    bool getIsCompleted() const;

    /**
     * @brief Set the completion status of the command.
     *
     * @param isCompleted The new completion status of the command.
     */
    void setIsCompleted(bool isCompleted);

   private:
    std::string command;                            ///< Name of the command being tracked.
    std::chrono::steady_clock::time_point sendTime; ///< Time point when the command was sent.
    bool isCompleted;                               ///< Completion status of the command.
  };
} // namespace Client
