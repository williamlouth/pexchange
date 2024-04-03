//
// Created by will on 03/04/24.
//

#pragma once
#include <Exchange.h>
#include <memory>
#include <thread>

namespace acceptance {

class AcceptanceDsl {
    public:
    AcceptanceDsl();
    ~AcceptanceDsl();

private:
    void runExchange();

    pex::Exchange exchange_;
    std::thread thread_;
};

} // acceptance
