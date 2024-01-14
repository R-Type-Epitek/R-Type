# Technical Documentation

### Introduction

Welcome to the comprehensive documentation for our project. This guide is designed to provide you with all the necessary
information to install, understand, and effectively utilize our software.

[TOC]

### Installation Guide

To install the project, please use the following command:

```bash
justfile
```

### Project Structure

Our project is structured into three main components, each serving a unique purpose in the overall functionality of the
software.

1. **The ECS (Entity Component System):** This part focuses on handling the data processing and logic of the software.

2. **The Server:** Responsible for managing the backend processes, the server can be launched using the command:

```bash
./r-type_server
```

1. **The Client:** The user interface and interaction component of our software. Start the client using:

```bash
./r-type_client
```

### Server / Client Protocol

The server and client communicate using a custom protocol. The protocol is based on the UDP protocol and is designed to
be lightweight and efficient.
The UDP is optimized for speed and is ideal for our use case. The protocol is designed to be as simple as possible, with
a minimal number of messages and fields.
The protocol is designed to be as simple as possible, with a minimal number of messages and fields.
The data is serialized to optimize the transmission speed and reduce the size of the packets.

The server and the clients communicate using a custom protocol. The protocol uses two main types of messages:

- Message
- Response

Here is the structure of a **message**:

```cpp
struct MessageHeader {
  int clientId;
  char command[32];
  int commandId;
  uint32_t dataLength;
};

struct Message {
  MessageType type = MessageType::Message;
  MessageHeader header;
  char data[];
};
```

Here is the structure of a **response**:

```cpp
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
```

#### Server to Client Messages

| Command                | Description                                                                                                           | Data                                                                                                                                                                                  |
|------------------------|-----------------------------------------------------------------------------------------------------------------------|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `/update_game`         | This command is sent automatically every 500ms when a room has the state RUNNING.                                     | `char data[]`<br>The data is a `std::vector<std::vector<char>>` serialized in binary and contains the entities and theirs components. (number of bytes defined in the message header) |
| `/check_connection`    | This command is sent automatically to a client, if the server has not received message from him in the last second.   |                                                                                                                                                                                       |
| `/client_disconnected` | This command is sent to all the players in the same room than the disconnected client when a client has disconnected. | `struct ServerClientDisconnectedData {int clientId;}` (8 bytes: defined in the message header)                                                                                        |                      |

#### Client to Server Messages

| Command           | Description                                                                                                                                                                                                                            | Data                                                                                                             |
|-------------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|------------------------------------------------------------------------------------------------------------------|
| `/connect`        | The client sent this command to the server when he wants to connect. <br><br>The server will then generate an id and send it back to the client.                                                                                       |                                                                                                                  |
| `/update_name`    | This client send this command to the server to execute his name.                                                                                                                                                                       | `char data[]`<br>The data is a `struct SendNameData {char name[32];}` (8 bytes: defined in the message header)   |
| `/join_room`      | The client send this command to the server to join a room.                                                                                                                                                                             | `char data[]`<br>The data is a `struct JoinRoomData {int roomId;};` (8 bytes: defined in the message header)     |
| `/join_room_auto` | The client send this command to the server to join a room automatically.                                                                                                                                                               |                                                                                                                  |
| `/input`          | The client send this command when he moves.                                                                                                                                                                                            |                                                                                                                  |
| `/join_game`      | The client send this command when he wants to start the game in his current room.<br>If the game will then start and the client will join the running game.<br><br>If the game is already running, the client will only join the room. | `char data[]`<br>The data is a `struct JoinGameData {int roomId;};` (8 bytes: defined in the message header)     |
| `/kick_player`    | The client send this command when he want to kick a player from the game, the player to kick must be in the same room.                                                                                                                 | `char data[]`<br>The data is a `struct KickPlayerData {int clientId;};` (8 bytes: defined in the message header) |
| `/god_mode`       | The client send this command when he want to set a player to god mode (unlimited lives).                                                                                                                                               | `char data[]`<br>The data is a `struct GodModeData {int clientId;};` (8 bytes: defined in the message header)    |
| `/spectate`       | The client send this command when he wants to spectate the game in his current room.                                                                                                                                                   | `char data[]`<br>The data is a `struct SpectateData {int roomId;};` (8 bytes: defined in the message header)     |

### Support and Contributions

For any assistance, queries, or contributions, please refer to our support guidelines or contact our team. We welcome
contributions and feedback to improve the project.

### Conclusion

We hope this documentation provides a clear understanding of our project and assists you in its effective utilization.
Thank you for choosing our software.

<div class="section_buttons">

| Previous          |                              Next |
|:------------------|----------------------------------:|
| [Home](README.md) | [Customization](customization.md) |

</div>