//
// Created by Xavier VINCENT on 24/12/23.
//

#include "RTypeClient.hpp"

namespace Client
{
  InputCommandHandler::InputCommandHandler(Network& network)
    : network(network)
  {
  }

  void InputCommandHandler::setKey(std::string key)
  {
    this->key = key;
  }

  const std::string& InputCommandHandler::getKey() const
  {
    return this->key;
  }

  void InputCommandHandler::send()
  {
    InputData data;
    strcpy(data.key, this->key.c_str());
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
