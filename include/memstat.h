#pragma once

#include <thread>
#include <mutex>
#include <cstring> // For memcpy 

struct MemStat {
    long double TOTAL_MB;
    long double FREE_MB;
    long double SHARED_MB;
    long double BUFFER_MB;
    short TOTAL_RUNNING_PROCS;
};

class Memory {
public:
    Memory();

    std::mutex Memory_Mutex;
    MemStat* memStat;

    MemStat getMemStat();

    int UPDATE_INTERVAL; // ms

    void START_MEMORY_POLLING();
    static void MEMORY_POLL(Memory* mem);
    void END_MEMORY_POLLING();

    virtual ~Memory();
private:
    std::thread* m_pollThread;
    bool m_isPolling;
};

static Memory* Memory_Instance;
