//
// Created by Xavier VINCENT on 24/12/23.
//

#include "network/commands/Input.hpp"

#include <spdlog/spdlog.h>

namespace Client
{
  InputCommandHandler::InputCommandHandler(Network& network)
    : network(network)
  {
  }

  void InputCommandHandler::setKey(GameEngine::Keybinds key)
  {
    this->key = key;
  }

  const GameEngine::Keybinds& InputCommandHandler::getKey() const
  {
    return this->key;
  }

  void InputCommandHandler::send()
  {
    InputData data = {
      .key = static_cast<int>(this->key),
    };
    char dataBuffer[sizeof(data)];
    memcpy(dataBuffer, &data, sizeof(data));

    this->network.sendMessage(INPUT_COMMAND, dataBuffer, sizeof(data));
  }

  void InputCommandHandler::onResponse(Response* response)
  {
    InputData* data = (InputData*)response->data;

    spdlog::info("Input received: {}", data->key);
  }
};
