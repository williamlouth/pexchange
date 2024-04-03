//
// Created by will on 03/04/24.
//

#include "AcceptanceDsl.h"
#include <Exchange.h>
#include <Room.h>

namespace acceptance {
	AcceptanceDsl::AcceptanceDsl()
		: serverThread_([this](){this->runExchange();})
		, client_([this](auto msg){this->onClientMessage(msg);})
		, clientThread_([this](){this->runClient();})
	{
		while(recvMessages_.empty()) //Waiting for Connected message from server
		{}
	}

	AcceptanceDsl::~AcceptanceDsl()
	{
		client_.stopListening();
		clientThread_.join();
		exchange_.stopListening();
		serverThread_.join();
	}
	void AcceptanceDsl::runExchange()
	{
		exchange_.runServer();
	}
	void AcceptanceDsl::runClient()
	{
		client_.run();
	}
	void AcceptanceDsl::onClientMessage(std::string message)
	{
		recvMessages_.emplace_back(message);
	}
} // acceptance