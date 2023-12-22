//
// Created by Xavier VINCENT on 14/12/23.
//

#pragma once

#include "MessageType.hpp"

/**
 * @struct ResponseHeader
 * @brief Structure representing the header of a network response sent by the server.
 * 
 * This structure contains the client identifier, command, the length of the data,
 * the status code and the statusMessage that follows in the message.
 */
struct ResponseHeader {
  int clientId;                                   ///< Identifier of the client that sent the command.
  char command[32];                               ///< Command type in ASCII format.
  uint32_t dataLength;                            ///< Length of the following data in bytes.
  int status;                                     ///< Status code of the response.
  char statusMessage[128];                        ///< Status message of the response.
};

/**
 * @struct Response
 * @brief Structure representing a complete network response sent by the server.
 * 
 * This structure combines the ResponseHeader with the actual data payload, allowing
 * for easy manipulation and transmission of network responses.
 */
struct Response {
  const MessageType type = MessageType::Response; ///< Type of the message.
  ResponseHeader header;                          ///< Header of the message.
  char data[];                                    ///< Variable-length data payload.
};
