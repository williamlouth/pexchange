//
// Created by will on 24/03/24.
//

#pragma once
#include <chrono>
#include <cstdint>
#include <string>

namespace pex
{
	using OrderId = uint64_t ;
	using ClOrdId = uint64_t ;
	using ConnectionId = uint64_t ;
	using RoomId = std::string;
	using UserId = std::string;
	using TimePoint = std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>;
}
