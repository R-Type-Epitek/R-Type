//
// Created by Xavier VINCENT on 18/12/2023.
//

#pragma once

#include <boost/asio.hpp>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>

#include "Constants.hpp"
#include "Client.hpp"
#include "Room.hpp"
#include "ThreadSafeQueue.hpp"
#include "UDPServer.hpp"
