//
// Created by will on 28/03/24.
//

#include "MessageParser.h"

#include <iostream>
#include <nlohmann/json.hpp>

namespace pex {
	MessageParser::MessageParser(const std::function<void(const nlohmann::json& message)>& onJsonMessage)
		: onJsonMessage_(onJsonMessage)
	{
	}
	void MessageParser::onRawMessage(const std::string& rawMessage)
	{
		try
		{
			auto jsonMessage = nlohmann::json::parse(rawMessage);
			onJsonMessage_(jsonMessage);
		}
		catch (nlohmann::json::parse_error const & e)
		{
			std::cout << "parse error of incoming message" << std::endl;
		}
		catch (...)
		{}
	}
} // pex