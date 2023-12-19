//
// Created by Xavier VINCENT on 14/12/23.
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
struct UpdateNameData {
  char name[32];
};

// Join command
struct JoinRoomData {
  int roomId;
};

// Input command
struct InputData {
  char key[1];
};

// Start game command
struct StartGameData {
  int roomId;
};
