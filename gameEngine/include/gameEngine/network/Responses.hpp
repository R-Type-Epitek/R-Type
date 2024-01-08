//
// Created by Xavier VINCENT on 14/12/23.
//

#pragma once
#include "MessageType.hpp"

#include <cstdint>

/**
 * @struct ResponseHeader
 * @brief Structure representing the header of a network message.
 *
 * This structure contains the client identifier, command, the identifier of the command,
 * the length of the data that follows in the message, the status of the command and the
 * status message.
 */
struct ResponseHeader {
  int clientId;            ///< Unique identifier for the client.
  char command[32];        ///< Command type in ASCII format.
  int commandId;           ///< Unique identifier for the command.
  uint32_t dataLength;     ///< Length of the following data in bytes.
  int status;              ///< Status of the command.
  char statusMessage[128]; ///< Status message of the command.
};

/**
 * @struct Response
 * @brief Structure representing a complete network message.
 *
 * This structure combines the ResponseHeader with the actual data payload, allowing
 * for easy manipulation and transmission of network messages.
 */
struct Response {
  MessageType type = MessageType::Message; ///< Type of the response.
  ResponseHeader header;                   ///< Header of the response.
  char data[];                             ///< Variable-length data payload.
};
