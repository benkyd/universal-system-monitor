#pragma once

#include <vector>
#include <thread>
#include <mutex>

class Memory {
public:
    Memory();

    std::mutex Memory_Mutex;

    long double MEMORY_TOTAL_MB;
    long double MEMORY_FREE_MB;
    long double MEMORY_AVAILABLE_MB;
    long double MEMORY_ACTIVE_MB;
    long double MEMORY_INACTIVE_MB;

    int UPDATE_INTERVAL; // s

    void START_MEMORY_POLLING();
    static void MEMORY_POLL(Memory* mem);
    void END_MEMORY_POLLING();

    virtual ~Memory();
private:
    std::thread* m_pollThread;
    bool m_isPolling;
};

static Memory* Memory_Instance;
