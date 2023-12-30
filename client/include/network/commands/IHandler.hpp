//
// Created by Xavier VINCENT on 24/12/23.
//

#pragma once
#include "RTypeClient.hpp"

namespace Client
{
  class ICommandHandler {
   public:
    virtual void send() = 0;
    virtual void onResponse(Response *response) = 0;
    virtual ~ICommandHandler() = default;
  };
}
