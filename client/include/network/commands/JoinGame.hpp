//
// Created by Xavier VINCENT on 24/12/23.
//

#pragma once
#include "network/Network.hpp"
#include "network/commands/IHandler.hpp"

namespace Client
{
  class JoinGameCommandHandler : public ICommandHandler {
   public:
    JoinGameCommandHandler(Network& network);
    void setRoomId(int roomId);
    int getRoomId() const;
    void send() override;
    void onResponse(Response* response) override;

   protected:
   private:
    Network& network;
    int roomId;
  };
}
