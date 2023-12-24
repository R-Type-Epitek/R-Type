//
// Created by Xavier VINCENT on 24/12/23.
//

#include "RTypeClient.hpp"

namespace Client
{
  UpdateNameCommandHandler::UpdateNameCommandHandler(Network& network)
    : network(network)
  {
  }

  void UpdateNameCommandHandler::setName(std::string name)
  {
    this->name = name;
  }

  const std::string& UpdateNameCommandHandler::getName() const
  {
    return this->name;
  }

  void UpdateNameCommandHandler::send()
  {
    if (this->name.length() > MAX_NAME_LENGTH)
      throw std::runtime_error("The name is too long");

    UpdateNameData data;
    strcpy(data.name, this->name.c_str());
    char dataBuffer[sizeof(data)];
    memcpy(dataBuffer, &data, sizeof(data));

    this->network.sendMessage(UPDATE_NAME_COMMAND, dataBuffer, sizeof(data));
  }

  void UpdateNameCommandHandler::onResponse(Response* response)
  {
    UpdateNameData* data = (UpdateNameData*)response->data;
    this->network.setName(data->name);

    spdlog::info("Name successfully updated: {}", data->name);
  }
};
