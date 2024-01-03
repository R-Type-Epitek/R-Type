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
#include "game/rtype/RtypeGame.hpp"
#include "Client.hpp"
#include "Room.hpp"
#include "ThreadSafeQueue.hpp"
#include "UDPServer.hpp"
#include "tools/Logs.hpp"

// commands
#include "commands/ConnectToServer.hpp"
#include "commands/Input.hpp"
#include "commands/JoinRoom.hpp"
#include "commands/JoinGame.hpp"
#include "commands/UpdateName.hpp"
