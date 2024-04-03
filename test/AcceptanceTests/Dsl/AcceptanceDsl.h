//
// Created by will on 03/04/24.
//

#pragma once
#include <Exchange.h>
#include <memory>
#include <thread>

#include "Client.h"

namespace acceptance {

class AcceptanceDsl {
    public:
    AcceptanceDsl();
    ~AcceptanceDsl();

private:
    void runExchange();
    void runClient();
    void onClientMessage(std::string message);

    pex::Exchange exchange_;
    std::thread serverThread_;

    acceptance::Client client_;
    std::thread clientThread_;

    std::vector<std::string> recvMessages_;
};

} // acceptance
