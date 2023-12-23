//
// Created by Xavier VINCENT on 17/12/23.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window/Window.hpp>

#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <memory>
#include <optional>
#include <functional>

// Game Engine Network
#include "../../gameEngine/include/network/Commands.hpp"
#include "../../gameEngine/include/network/Messages.hpp"
#include "../../gameEngine/include/network/MessageType.hpp"
#include "../../gameEngine/include/network/Responses.hpp"
#include "../../gameEngine/include/network/Statuses.hpp"

#include "Constants.hpp"
#include "Network.hpp"

// Components
#include "Components/Background.hpp"
#include "Components/Button.hpp"
#include "Components/InputText.hpp"

// Scenes
#include "Scenes/Manager.hpp"
#include "Scenes/Game.hpp"
#include "Scenes/Lobby.hpp"
#include "Scenes/Welcome.hpp"
