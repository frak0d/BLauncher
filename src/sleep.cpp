#pragma once

#include <chrono>
#include <thread>
#include <string_view>

void sleep_for(float value, const std::string_view& unit)
{
    unsigned long duration;

    if (unit == "s")
        duration = value * 1e9;
    else if (unit == "ms")
        duration = value * 1e6;
    else if (unit == "us")
        duration = value * 1e3;
    else if (unit == "ns")
        duration = value;

    std::this_thread::sleep_for(std::chrono::nanoseconds(duration));
}