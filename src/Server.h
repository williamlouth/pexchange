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

private:
    WebppServer server_;

};

} // pex
