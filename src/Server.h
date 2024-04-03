//
// Created by will on 28/03/24.
//

#pragma once
#include <websocketpp/server.hpp>
#include <websocketpp/config/asio_no_tls.hpp>

namespace pex {

typedef websocketpp::server<websocketpp::config::asio> WebppServer;

class Server {
    public:
    Server(std::function<std::string(websocketpp::connection_hdl connectionHandle, const std::string&)> onStringMessage);

    void stopListening();
    void run();

private:
    void onMessage(websocketpp::connection_hdl connectionHandle, WebppServer::message_ptr msg);

    WebppServer server_;
    std::function<std::string(websocketpp::connection_hdl connectionHandle, const std::string&)> onStringMessage_;

};

} // pex
