//
// Created by Xavier VINCENT on 24/12/23.
//

#pragma once
#include "RTypeClient.hpp"

namespace Client
{
  class InputCommandHandler : public ICommandHandler {
  public:
    InputCommandHandler(Network& network);
    void setKey(std::string key);
    const std::string& getKey() const;
    void send() override;
    void onResponse(Response* response) override;

  protected:
  private:
    Network& network;
    std::string key;
  };
}
