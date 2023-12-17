//
// Created by X-VINCENT on 12/14/23.
//

#include <cstdint>

struct MessageHeader {
  int clientId;
  char command[32];
  uint32_t dataLength;
};

struct Message {
  MessageHeader header;
  char data[];
};

// Name command
struct SendNameData {
  char name[32];
};

// Join command
struct JoinRoomData {
  int roomId;
};
