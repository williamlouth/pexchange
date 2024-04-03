//
// Created by will on 03/04/24.
//

#include "Client.h"

namespace acceptance {
	Client::Client(std::function<void(std::string)> onMessageCallback)
		: onMessageCallback_{std::move(onMessageCallback)}
	{
        // Set logging to be pretty verbose (everything except message payloads)
        client_.set_access_channels(websocketpp::log::alevel::all);
        client_.clear_access_channels(websocketpp::log::alevel::frame_payload);

        // Initialize ASIO
        client_.init_asio();

        // Register our message handler
        client_.set_message_handler([this](auto hdl, auto msg){this->onMessage(&client_, hdl, msg);});

        websocketpp::lib::error_code ec;
        connection_ = client_.get_connection("ws://localhost:9002", ec);
        if (ec) {
            std::cout << "could not create connection because: " << ec.message() << std::endl;
            return;
        }

        // Note that connect here only requests a connection. No network messages are
        // exchanged until the event loop starts running in the next line.
        client_.connect(connection_);
	}
	void Client::run()
	{
		try {

        // Start the ASIO io_service run loop
        // this will cause a single connection to be made to the server. client_.run()
        // will exit when this connection is closed.
        client_.run();
    } catch (websocketpp::exception const & e) {
        std::cout << e.what() << std::endl;
    }
	}
	void Client::stopListening()
	{
		try
		{
			client_.close(connection_->get_handle(), websocketpp::close::status::value(0), "done");
		}
		catch (websocketpp::exception const & e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	void Client::sendMessage(const std::string& message)
	{
		try
		{
			client_.send(connection_->get_handle(), message, websocketpp::frame::opcode::text);
		}
		catch (websocketpp::exception const & e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	void Client::onMessage(websocketpp::client<websocketpp::config::asio_client>*,
	                       websocketpp::connection_hdl,
	                       websocketpp::config::asio_client::message_type::ptr msg)
	{
		onMessageCallback_(msg->get_payload());
	}
} // acceptance