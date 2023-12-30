//
// Created by Xavier VINCENT on 24/12/23.
//

#pragma once
#include "RTypeClient.hpp"

namespace Client
{
  class StartGameCommandHandler : public ICommandHandler {
   public:
    StartGameCommandHandler(Network& network);
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
