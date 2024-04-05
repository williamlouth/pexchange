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
    void createUser(const pex::UserId& user);
    std::string sendMessage(const std::string& message, const pex::UserId& user);

    bool userMessageContains(const pex::UserId& user, const std::string& message);
private:
    IntegrationExchange exchange_;

    std::map<pex::UserId,pex::ConnectionId> users_;

    pex::ConnectionId lastConnectionNumber_;
};

} // integration
