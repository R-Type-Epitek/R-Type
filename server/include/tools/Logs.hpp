//
// Created by Xavier VINCENT on 24/12/2023.
//

#include "RTypeNetwork.hpp"

void logMessage(std::string prefix, Message *message, const int width = 20);
void logResponse(std::string prefix, Response *response, const int width = 20);
void logTimedMessage(
  std::string prefix,
  TimedMessage timedMessage,
  Response response,
  const int width = 20);
