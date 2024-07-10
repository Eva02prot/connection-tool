#include "TimeHelper.h"

using namespace std::chrono;

timestamp_t CurTimestamp()
{
    return steady_clock::now();
}

double GetElapsedTime(const timestamp_t& start)
{
    timestamp_t curTime = steady_clock::now();
    duration<double> theDuration = duration_cast<duration<double> >(curTime - start);
    return theDuration.count();
}

double TimestampInDouble(const timestamp_t& ts)
{
    duration<double> theDuration = duration_cast<duration<double> >(ts.time_since_epoch());
    return theDuration.count();
}

double CurTimestampInDouble()
{
    timestamp_t curTime = steady_clock::now();
    duration<double> theDuration = duration_cast<duration<double> >(curTime.time_since_epoch());
    return theDuration.count();
}

tm LocalTime(int64_t timeVal)
{
    time_t t = (timeVal == 0)? time(nullptr) : (time_t)timeVal;
    tm timeInfo = *localtime(&t);
    return timeInfo;
}

