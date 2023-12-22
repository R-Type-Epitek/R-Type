//
// Created by Xavier VINCENT on 18/12/2023.
//

#pragma once

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <chrono>
#include <condition_variable>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <queue>
#include <sstream>
#include <thread>
#include <vector>

// Game Engine Network
#include "Client.hpp"
#include "Commands/IHandler.hpp"
#include "Constants.hpp"
#include "Room.hpp"
#include "ThreadSafeQueue.hpp"
#include "UDPServer.hpp"
#include "gameEngine/network/Commands.hpp"
#include "gameEngine/network/Messages.hpp"
#include "gameEngine/network/Responses.hpp"
#include "gameEngine/network/Statuses.hpp"

// Commands
#include "Commands/Hello.hpp"
#include "Commands/Input.hpp"
#include "Commands/JoinRoom.hpp"
#include "Commands/StartGame.hpp"
#include "Commands/UpdateName.hpp"
