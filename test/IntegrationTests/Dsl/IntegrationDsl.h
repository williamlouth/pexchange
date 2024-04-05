//
// Created by will on 03/04/24.
//

#pragma once
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

#include "IntegrationExchange.h"

namespace websocketpp::config
{
    struct asio_client;
}

namespace integration {

class IntegrationDsl {
    public:
    void createUser(const std::string& user);
    std::string sendMessage(const std::string& message, const std::string& user);

private:
    IntegrationExchange exchange_;

    std::map<std::string,pex::ConnectionId> users_;

    pex::ConnectionId lastConnectionNumber_;
};

} // integration
