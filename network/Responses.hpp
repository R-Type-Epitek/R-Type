//
// Created by X-VINCENT on 12/14/23.
//

#include <cstdint>

struct ResponseHeader {
  int client_id;
  char command[32];
  uint32_t dataLength;
  int status;
  char status_message[128];
};

struct Response {
  ResponseHeader header;
  char data[];
};
