#pragma once

#include <atomic>
#include <thread>

class CPU {
public:
    CPU();
    
    std::atomic<int> CPU_PREVIOUS_IDLE;
    std::atomic<int> CPU_PREVIOUS_TOTAL;
    std::atomic<int> CPU_IDLE;
    std::atomic<int> CPU_TOTAL;

    std::atomic<int> UPDATE_INTERVAL; // ms

    void START_CPU_POLLING();
    static void CPU_POLL();
    void END_CPU_POLLING();

    double CPU_PERCENT();

    virtual ~CPU();
private:
    std::thread* m_pollThread;
    std::atomic<bool> m_isPolling;
};

static CPU* instance;
static CPU* GetCPUInstance() {
    if (instance == (void*)0) {
        CPU cpu;
        instance = &cpu;
        return instance;
    }
    return instance;
}

