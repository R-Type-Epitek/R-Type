//
// Created by Xavier VINCENT on 20/12/2023.
//

#pragma once

#include "RTypeNetwork.hpp"

namespace Network
{
    class StartGameCommandHandler : public ICommandHandler {
        public:
            StartGameCommandHandler(UDPServer& server);
            bool isAuthorized(int clientId) override;
            Response handleCommand(Message* message) override;

        protected:
        private:
            UDPServer& server;
    };
}
