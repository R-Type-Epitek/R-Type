//
// Created by X-VINCENT on 12/14/23.
//

#pragma once

#include <iostream>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

#include "Commands.hpp"
#include "Errors.hpp"
#include "Messages.hpp"
#include "Responses.hpp"
#include "Status.hpp"

#define DEFAULT_IP "127.0.0.1"
#define DEFAULT_PORT "4242"
#define DEFAULT_ROOM_SIZE 4
#define NUMBER_OF_ROOMS 4
#define DEFAULT_IO (boost::asio::io_context){}

#define MAX_NAME_LENGTH 32