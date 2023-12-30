//
// Created by Xavier VINCENT on 24/12/23.
//

#pragma once

// Client
#include "network/Network.hpp"
#include "network/commands/IHandler.hpp"

namespace Client
{
  class ConnectToServerCommandHandler : public ICommandHandler {
   public:
    ConnectToServerCommandHandler(Network& network);
    void send() override;
    void onResponse(Response* response) override;

   protected:
   private:
    Network& network;
  };
}
