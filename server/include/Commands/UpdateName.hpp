//
// Created by Xavier VINCENT on 20/12/2023.
//

#pragma once

#include "RTypeNetwork.hpp"

namespace Network {
class UpdateNameCommandHandler : public ICommandHandler {
 public:
  UpdateNameCommandHandler(UDPServer& server);
  bool isAuthorized(int clientId) override;
  Response handleCommand(Message* message) override;

 protected:
 private:
  UDPServer& server;
};
}  // namespace Network
