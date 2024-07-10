#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include <array>

struct SignalObject
{
    std::mutex _mtx;
    std::condition_variable _cv;

    virtual void Notify() = 0;
    virtual void Wait() = 0;
    virtual int Wait(int timeoutUs) = 0;
};

struct Event : SignalObject
{
    bool _signaled = false;

    virtual void Notify() override;
    virtual void Wait() override;
    virtual int Wait(int timeoutUs) override;
};

struct Semaphore : SignalObject
{
    int _semaCount = 0;

    virtual void Notify() override;
    virtual void Wait() override;
    virtual int Wait(int timeoutUs) override;
};

class SyncObject
{
    using lock_t = std::unique_lock<std::mutex>;
public:
#if defined(_Analysis_suppress_lock_checking_)
    _Analysis_suppress_lock_checking_(_mtx)
#endif

    inline void Lock() { _mtx.lock(); }
    inline void Unlock() { _mtx.unlock(); }
    inline bool TryLock() { return _mtx.try_lock(); }

    inline std::unique_lock<std::mutex> AutoLock() { return lock_t(_mtx); }

    inline std::array<lock_t, 2> AutoLock(std::mutex& mtx1)
    { 
        std::array<lock_t, 2> locks = { { lock_t(_mtx, std::defer_lock), lock_t(mtx1, std::defer_lock) } };
        std::lock(_mtx, mtx1);
        return locks;
    }
    inline std::array<lock_t, 2> AutoLock(SyncObject& obj) { return AutoLock(obj._mtx); }

private:
    std::mutex _mtx;
};
