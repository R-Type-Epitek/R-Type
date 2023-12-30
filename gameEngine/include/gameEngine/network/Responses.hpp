//
// Created by Xavier VINCENT on 14/12/23.
//

#pragma once
#include "MessageType.hpp"

#include <cstdint>

struct ResponseHeader {
  int clientId;
  char command[32];
  int commandId;
  uint32_t dataLength;
  int status;
  char statusMessage[128];
};

struct Response {
  MessageType type = MessageType::Message; ///< Type of the message.
  ResponseHeader header;
  char data[];
};
