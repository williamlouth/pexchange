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
    bool createUser(const pex::UserId& user);
    std::string createOrder(const pex::UserId& user, const pex::RoomId& room, const pex::Decimal& px, const pex::Decimal& sz, const pex::ClOrdId& clOrdId = 0);
    std::string sendMessage(const std::string& message, const pex::UserId& user);

    bool userContainsFullFill(const pex::UserId& user, const pex::ClOrdId& clOrdId, const pex::Decimal& fillAmount);
    bool userMessageContains(const pex::UserId& user, const std::string& message);
    void addRoom(const pex::RoomId& room);

private:
    IntegrationExchange exchange_;

    std::map<pex::UserId,pex::ConnectionId> users_;

    pex::ConnectionId lastConnectionNumber_;
};

} // integration
