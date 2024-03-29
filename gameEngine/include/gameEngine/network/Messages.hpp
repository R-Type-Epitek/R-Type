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
  uint32_t timestamp;  ///< The time at which the message was sent.
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
  int key; ///< The input key or command.
};

/**
 * @struct JoinGameData
 * @brief Structure for data related to a 'Join Game' command.
 *
 * This structure is used when initiating a game within a specific room.
 */
struct JoinGameData {
  int roomId; ///< Identifier of the room the player will join.
};

/**
 * @struct ServerClientDisconnectedData
 * @brief Structure for data related to a 'Client Disconnected' command.
 *
 * This structure is used when a client disconnects from the server.
 */
struct ServerClientDisconnectedData {
  int clientId;
};

/**
 * @struct KickPlayerData
 * @brief Structure for data related to a 'Kick Player' command.
 *
 * This structure is used when a client wants to kick another player from the room.
 */
struct KickPlayerData {
  int clientId;
};

/**
 * @struct GodModeData
 * @brief Structure for data related to a 'God Mode' command.
 *
 * This structure is used when a client wants to enable or disable god mode.
 */
struct GodModeData {
  int clientId;
};

/**
 * @struct SpectateData
 * @brief Structure for data related to a 'Spectate' command.
 *
 * This structure is used when a client wants to spectate a game.
 */
struct SpectateData {
  int roomId;
};
