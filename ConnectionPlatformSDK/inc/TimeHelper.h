#pragma once

#include <stdint.h>
#include <time.h>
#include <chrono>
#include <thread>

typedef std::chrono::steady_clock::time_point timestamp_t;
#define __timestampZero timestamp_t();

timestamp_t CurTimestamp();
double GetElapsedTime(const timestamp_t& start);

double TimestampInDouble(const timestamp_t& ts);
double CurTimestampInDouble();

tm LocalTime(int64_t timeVal = 0);

inline void SleepInMilliseconds(int64_t milliseconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

inline void SleepInMicroseconds(int64_t microseconds)
{
    std::this_thread::sleep_for(std::chrono::microseconds(microseconds));
}
