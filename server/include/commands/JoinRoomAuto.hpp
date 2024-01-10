//
// Created by Xavier VINCENT on 09/01/2024.
//

#pragma once

#include "RTypeNetwork.hpp"

namespace Network
{
  class JoinRoomAutoCommandHandler : public ICommandHandler {
   public:
    JoinRoomAutoCommandHandler(UDPServer &server);
    bool isAuthorized(int clientId) override;
    std::vector<char> handleCommand(Message *message) override;

   protected:
   private:
    UDPServer &server;
  };
} // namespace Network
