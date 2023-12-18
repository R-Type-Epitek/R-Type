//
// Created by Xavier VINCENT on 14/12/23.
//

#include <cstdint>

struct ResponseHeader {
  int clientId;
  char command[32];
  uint32_t dataLength;
  int status;
  char statusMessage[128];
};

struct Response {
  ResponseHeader header;
  char data[];
};
