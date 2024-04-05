//
// Created by will on 28/03/24.
//

#pragma once
#include <websocketpp/server.hpp>
#include <websocketpp/config/asio_no_tls.hpp>

#include "Types.h"

namespace pex {

typedef websocketpp::server<websocketpp::config::asio> WebppServer;

class Server {
    public:
    Server(std::function<std::string(ConnectionId connectionId, const std::string&)> onStringMessage);

    void stopListening();
    void run();

private:
    void onMessage(websocketpp::connection_hdl connectionHandle, WebppServer::message_ptr msg);
    void onOpen(websocketpp::connection_hdl connectionHandle);
    void onClose(websocketpp::connection_hdl connectionHandle);

    WebppServer server_;
    std::function<std::string(ConnectionId connectionId, const std::string&)> onStringMessage_;

    std::map<websocketpp::connection_hdl,ConnectionId, std::owner_less<>> connections_;
    ConnectionId lastConnectionId_;

};

} // pex
