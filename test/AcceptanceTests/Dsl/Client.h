//
// Created by will on 03/04/24.
//

#pragma once
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

namespace acceptance {

class Client {
public:
    Client(std::function<void(std::string)> onMessageCallback);
    void run();
    void stopListening();

private:
    void onMessage(websocketpp::client<websocketpp::config::asio_client>* c, websocketpp::connection_hdl hdl, websocketpp::config::asio_client::message_type::ptr msg);
    websocketpp::client<websocketpp::config::asio_client> client_;

    std::function<void(std::string)> onMessageCallback_;
    websocketpp::connection_hdl connectionHandle_;

};

} // acceptance
