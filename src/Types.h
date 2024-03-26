//
// Created by will on 24/03/24.
//

#pragma once
#include <chrono>
#include <cstdint>
#include <string>

namespace pex
{
	typedef uint64_t OrderId;
	typedef uint64_t ClOrdId;
	typedef std::string RoomId;
	typedef std::string UserId;
	typedef std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> TimePoint;
}
