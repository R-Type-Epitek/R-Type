//
// Created by Xavier VINCENT on 24/12/23.
//

#include "RTypeClient.hpp"

namespace Client
{
  CommandTracker::CommandTracker(const std::string &command)
    : command(command)
    , sendTime(std::chrono::steady_clock::now())
    , isCompleted(false)
  {
    this->sendTime = std::chrono::steady_clock::now();
  }

  const std::string &CommandTracker::getCommand() const
  {
    return this->command;
  }

  const std::chrono::steady_clock::time_point &CommandTracker::getSendTime() const
  {
    return this->sendTime;
  }

  bool CommandTracker::getIsCompleted() const
  {
    return this->isCompleted;
  }

  void CommandTracker::setIsCompleted(bool isCompleted)
  {
    this->isCompleted = isCompleted;
  }
}
