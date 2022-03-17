#pragma once

#include <chrono>
#include <thread>

struct
{

void sleep(int time_sec)
{
    std::this_thread::sleep_for(std::chrono::seconds(time_sec));
}
void msleep(int time_sec)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(time_sec));
}
void usleep(int time_sec)
{
    std::this_thread::sleep_for(std::chrono::microseconds(time_sec));
}

} tim;
