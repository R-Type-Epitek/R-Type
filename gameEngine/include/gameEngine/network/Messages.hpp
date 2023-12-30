//
// Created by Xavier VINCENT on 14/12/23.
//

#pragma once
#include "MessageType.hpp"

#include <cstdint>

/**
 * @struct MessageHeader
 * @brief Structure representing the header of a network message.
 *
 * This structure contains the client identifier, command, and length of the data
 * that follows in the message.
 */
struct MessageHeader {
  int clientId;        ///< Unique identifier for the client.
  char command[32];    ///< Command type in ASCII format.
  int commandId;       ///< Unique identifier for the command.
  uint32_t dataLength; ///< Length of the following data in bytes.
};

/**
 * @struct Message
 * @brief Structure representing a complete network message.
 *
 * This structure combines the MessageHeader with the actual data payload, allowing
 * for easy manipulation and transmission of network messages.
 */
struct Message {
  MessageType type = MessageType::Message; ///< Type of the message.
  MessageHeader header;                    ///< Header of the message.
  char data[];                             ///< Variable-length data payload.
};

/**
 * @struct UpdateNameData
 * @brief Structure for data related to a 'Name' command.
 *
 * This structure is used when the command involves updating a client's name.
 */
struct UpdateNameData {
  char name[32]; ///< New name for the client.
};

/**
 * @struct JoinRoomData
 * @brief Structure for data related to a 'Join Room' command.
 *
 * This structure is used when a client sends a request to join a specific room.
 */
struct JoinRoomData {
  int roomId; ///< Identifier of the room to join.
};

/**
 * @struct InputData
 * @brief Structure for data related to an 'Input' command.
 *
 * This structure is used to transmit client's input, typically a single character.
 */
struct InputData {
  char key[1]; ///< The input key or command.
};

/**
 * @struct StartGameData
 * @brief Structure for data related to a 'Start Game' command.
 *
 * This structure is used when initiating a game within a specific room.
 */
struct StartGameData {
  int roomId; ///< Identifier of the room where the game will start.
};

struct ServerClientDisconnectedData {
  int clientId;
};