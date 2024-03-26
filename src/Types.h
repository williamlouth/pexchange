//
// Created by will on 24/03/24.
//

#pragma once
#include <chrono>
#include <cstdint>

namespace pex
{
	typedef uint64_t OrderId;
	typedef std::string RoomId;
	typedef std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> TimePoint;
}
