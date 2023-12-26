//
// Created by Xavier VINCENT on 24/12/23.
//

#pragma once
#include "RTypeClient.hpp"

namespace Client
{
  class CommandTracker {
  public:
    CommandTracker(const std::string &command);
    ~CommandTracker() = default;
    const std::string &getCommand() const;
    const std::chrono::steady_clock::time_point &getSendTime() const;
    bool getIsCompleted() const;
    void setIsCompleted(bool isCompleted);

  protected:
  private:
    std::string command;
    std::chrono::steady_clock::time_point sendTime;
    bool isCompleted;
  };
}
