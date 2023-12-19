//
// Created by Xavier VINCENT on 18/12/2023.
//

#pragma once

#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>

// Game Engine Network
#include "../../gameEngine/include/network/Commands.hpp"
#include "../../gameEngine/include/network/Errors.hpp"
#include "../../gameEngine/include/network/Messages.hpp"
#include "../../gameEngine/include/network/Responses.hpp"
#include "../../gameEngine/include/network/Status.hpp"

#include "Constants.hpp"
#include "Client.hpp"
#include "Room.hpp"
#include "ThreadSafeQueue.hpp"
#include "UDPServer.hpp"
