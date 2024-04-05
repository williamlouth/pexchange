//
// Created by will on 03/04/24.
//

#pragma once
#include <ExchangeInternal.h>
#include <Types.h>

namespace integration {

class IntegrationExchange : public pex::ExchangeInternal {
    public:

    std::string onMessage(pex::ConnectionId connectionId, const std::string& message);

protected:
		void sendMessage(const pex::ConnectionId& connection, const std::string& message) override;
};

} // integration
