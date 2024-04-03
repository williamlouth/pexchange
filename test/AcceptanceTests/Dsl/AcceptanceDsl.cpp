//
// Created by will on 03/04/24.
//

#include "AcceptanceDsl.h"
#include <Exchange.h>
#include <Room.h>
#include <nlohmann/json.hpp>

namespace acceptance {
	AcceptanceDsl::AcceptanceDsl()
		: serverThread_([this](){this->runExchange();})
		, client_([this](auto msg){this->onClientMessage(msg);})
		, clientThread_([this](){this->runClient();})
	{
		waitForMessage("Connected", std::chrono::seconds{10});
	}

	AcceptanceDsl::~AcceptanceDsl()
	{
		client_.stopListening();
		clientThread_.join();
		exchange_.stopListening();
		serverThread_.join();
	}
	void AcceptanceDsl::logOn()
	{
		nlohmann::json message;
		message["type"] = "LogOn";
		message["Username"] = "user";
		client_.sendMessage(message.dump());
	}
	bool AcceptanceDsl::waitForMessage(const std::string& message, const std::chrono::seconds& timeout)
	{
		const auto waitingStart = std::chrono::system_clock::now();
		while(std::chrono::system_clock::now() - waitingStart < timeout)
		{
			{
				std::lock_guard<std::mutex> lock(recvMessageMutex_);
				if (std::ranges::find(recvMessages_, message) != recvMessages_.end())
				{
					return true;
				}
			}
			std::this_thread::sleep_for(std::chrono::seconds{1});
		}
		return false;
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
		std::lock_guard<std::mutex> lock(recvMessageMutex_);
		std::cout << message << std::endl;
		recvMessages_.emplace_back(message);
	}
} // acceptance