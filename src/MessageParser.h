//
// Created by will on 28/03/24.
//

#pragma once
#include <functional>
#include <string>
#include <nlohmann/json_fwd.hpp>

namespace pex {

class MessageParser {
    public:
	explicit MessageParser(const std::function<void(const nlohmann::json& message)>& onJsonMessage);
	void onRawMessage(const std::string& rawMessage);
private:
        std::function<void(const nlohmann::json& message)> onJsonMessage_;

};

} // pex
