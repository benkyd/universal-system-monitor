#pragma once

#include <atomic>
#include <thread>
#include <mutex>

class CPU {
public:
    CPU();
    
    std::mutex CPU_Mutex;
    int CPU_PREVIOUS_IDLE;
    int CPU_PREVIOUS_TOTAL;
    int CPU_IDLE;
    int CPU_TOTAL;

    int UPDATE_INTERVAL; // s

    void START_CPU_POLLING();
    static void CPU_POLL(CPU* cpu);
    void END_CPU_POLLING();

    double CPU_PERCENT();

    virtual ~CPU(); 
private:
    std::thread* m_pollThread;
    bool m_isPolling;
};

static CPU* CPU_Instance;
