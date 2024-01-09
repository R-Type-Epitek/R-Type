//
// Created by Xavier VINCENT on 20/12/2023.
//

#pragma once

#include "RTypeNetwork.hpp"

namespace Network
{
  class SpectateCommandHandler : public ICommandHandler {
   public:
    SpectateCommandHandler(UDPServer &server);
    bool isAuthorized(int clientId) override;
    std::vector<char> handleCommand(Message *message) override;

   protected:
   private:
    UDPServer &server;
  };
} // namespace Network
