#pragma once
#include "pch.h"
#include <chrono>
#include "Util.hpp"

double TimeUtils::getTimestamp() {
	static bool timeZeroCalculated = false;
	static std::chrono::system_clock::time_point time0;
	if (!timeZeroCalculated) {
		time0 = std::chrono::system_clock::now();
		timeZeroCalculated = true;
	}
	auto tstamp = std::chrono::system_clock::now() - time0;
	long long delta = std::chrono::duration_cast<std::chrono::nanoseconds>(tstamp).count();
	return delta * 0.000000001;
}