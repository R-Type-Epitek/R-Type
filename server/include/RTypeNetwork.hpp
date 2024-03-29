//
// Created by Xavier VINCENT on 18/12/2023.
//

#pragma once

#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <chrono>
#include <unordered_map>
#include <spdlog/spdlog.h>

#include "gameEngine/constants/Keybinds.hpp"

// Game Engine Network
#include "gameEngine/network/Commands.hpp"
#include "gameEngine/network/Messages.hpp"
#include "gameEngine/network/MessageType.hpp"
#include "gameEngine/network/Responses.hpp"
#include "gameEngine/network/Statuses.hpp"

#include "commands/IHandler.hpp"
#include "Constants.hpp"
#include "Client.hpp"
#include "Room.hpp"
#include "ThreadSafeQueue.hpp"
#include "UDPServer.hpp"
#include "tools/EndianConverter.hpp"
#include "tools/Logs.hpp"

// commands
#include "commands/ConnectToServer.hpp"
#include "commands/GodMode.hpp"
#include "commands/Input.hpp"
#include "commands/JoinGame.hpp"
#include "commands/JoinRoom.hpp"
#include "commands/JoinRoomAuto.hpp"
#include "commands/KickPlayer.hpp"
#include "commands/Spectate.hpp"
#include "commands/UpdateName.hpp"
