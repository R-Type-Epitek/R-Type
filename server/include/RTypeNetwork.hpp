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

// Game Engine Network
#include "../../gameEngine/include/network/Commands.hpp"
#include "../../gameEngine/include/network/Messages.hpp"
#include "../../gameEngine/include/network/MessageType.hpp"
#include "../../gameEngine/include/network/Responses.hpp"
#include "../../gameEngine/include/network/Statuses.hpp"

#include "Commands/IHandler.hpp"
#include "Constants.hpp"
#include "Client.hpp"
#include "Room.hpp"
#include "ThreadSafeQueue.hpp"
#include "UDPServer.hpp"

// Commands
#include "Commands/Hello.hpp"
#include "Commands/Input.hpp"
#include "Commands/JoinRoom.hpp"
#include "Commands/StartGame.hpp"
#include "Commands/UpdateName.hpp"
