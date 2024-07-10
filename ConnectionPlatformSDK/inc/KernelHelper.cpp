#include "KernelHelper.h"

void Event::Notify()
{
    std::lock_guard<std::mutex> lock(_mtx);

    _signaled = true;
    _cv.notify_all();
}

void Event::Wait()
{
    std::unique_lock<std::mutex> lock(_mtx);

    if (!_signaled)
    {
        _cv.wait(lock);
    }
    _signaled = false;
}

int Event::Wait(int timeoutUs)
{
    if (timeoutUs <= 0)
    {
        std::lock_guard<std::mutex> lock(_mtx);

        if (!_signaled)
        {
            return -1;
        }
        _signaled = false;
        return 0;
    }
    else
    {
        std::unique_lock<std::mutex> lock(_mtx);

        if (!_signaled)
        {
            if (_cv.wait_for(lock, std::chrono::microseconds(timeoutUs)) == std::cv_status::timeout)
            {
                return -1;
            }
        }
        _signaled = false;
        return 0;
    }
}

void Semaphore::Notify()
{
    std::lock_guard<std::mutex> lock(_mtx);

    ++_semaCount;
    _cv.notify_one();
}

void Semaphore::Wait()
{
    std::unique_lock<std::mutex> lock(_mtx);

    while (_semaCount <= 0)
    {
        _cv.wait(lock);
    }
    --_semaCount;
}

int Semaphore::Wait(int timeoutUs)
{
    if (timeoutUs <= 0)
    {
        std::lock_guard<std::mutex> lock(_mtx);

        if (_semaCount <= 0)
        {
            return -1;
        }
        --_semaCount;
        return 0;
    }
    else
    {
        std::unique_lock<std::mutex> lock(_mtx);

        while (_semaCount <= 0)
        {
            if (_cv.wait_for(lock, std::chrono::microseconds(timeoutUs)) == std::cv_status::timeout)
            {
                return -1;
            }
        }
        --_semaCount;
        return 0;
    }
}
