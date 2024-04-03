//
// Created by will on 03/04/24.
//

#include "AcceptanceDsl.h"
#include <Exchange.h>
#include <Room.h>

namespace acceptance {
	AcceptanceDsl::AcceptanceDsl()
		: thread_([this](){this->runExchange();})
	{
		std::this_thread::sleep_for(std::chrono::seconds{1}); //TODO: ew should wait for ability to connect
	}

	AcceptanceDsl::~AcceptanceDsl()
	{
		exchange_.stopListening();
		thread_.join();
	}
	void AcceptanceDsl::runExchange()
	{
		exchange_.runServer();
	}
} // acceptance