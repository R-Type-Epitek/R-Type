//
// Created by Xavier VINCENT on 24/12/23.
//

#pragma once
#include "network/Network.hpp"
#include "network/commands/IHandler.hpp"

namespace Client
{
  class UpdateNameCommandHandler : public ICommandHandler {
   public:
    UpdateNameCommandHandler(Network& network);
    void setName(std::string name);
    const std::string& getName() const;
    void send() override;
    void onResponse(Response* response) override;

   protected:
   private:
    Network& network;
    std::string name;
  };
}
