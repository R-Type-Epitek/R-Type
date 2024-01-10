//
// Created by Xavier VINCENT on 09/01/2024.
//

#pragma once

#include "RTypeNetwork.hpp"

namespace Network
{
  class KickPlayerCommandHandler : public ICommandHandler {
   public:
    KickPlayerCommandHandler(UDPServer &server);
    bool isAuthorized(int clientId) override;
    std::vector<char> handleCommand(Message *message) override;

   protected:
   private:
    UDPServer &server;
  };
} // namespace Network
