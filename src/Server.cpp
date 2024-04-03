//
// Created by will on 28/03/24.
//

#include "Server.h"

namespace pex {
	Server::Server(std::function<std::string(websocketpp::connection_hdl connectionHandle, const std::string&)> onStringMessage)
		: onStringMessage_{onStringMessage}
	{
	}
	void Server::stopListening()
	{
		server_.stop_listening();
	}
	void Server::run()
	{
		try
		{
			server_.set_access_channels(websocketpp::log::alevel::all);
			server_.clear_access_channels(websocketpp::log::alevel::frame_payload);

			server_.init_asio();
			server_.set_message_handler([this](auto connection_hdl, auto message_ptr)
			{
				this->onMessage(connection_hdl, message_ptr);
			});
			server_.set_open_handler([this](auto connection_hdl)
			{
				this->onOpen(connection_hdl);
			});

			server_.listen(9002);
			server_.start_accept();
			server_.run();
		}
		catch (websocketpp::exception const& e)
		{
			std::cout << e.what() << std::endl;
		}
		catch (...)
		{
			std::cout << "Other Websocketpp error" << std::endl;
		}
	}

	void Server::onMessage(websocketpp::connection_hdl connectionHandle, WebppServer::message_ptr messagePtr)
	{
		const auto returnMessage = onStringMessage_(std::move(connectionHandle), messagePtr->get_payload());
		server_.send(connectionHandle, returnMessage, websocketpp::frame::opcode::text);
	}
	void Server::onOpen(websocketpp::connection_hdl connectionHandle)
	{
		server_.send(connectionHandle, "Connected", websocketpp::frame::opcode::text);
	}
} // pex