#pragma once

#include <vector>
#include <thread>
#include <mutex>

class CPU {
public:
    CPU();
    
    std::mutex CPU_Mutex;
    int CPU_PREVIOUS_WORK;
    int CPU_PREVIOUS_TOTAL;
    int CPU_WORK;
    int CPU_TOTAL;

    int UPDATE_INTERVAL; // s

    std::vector<std::vector<int>> CPU_CORES_WORK_AND_TOTAL;

    void START_CPU_POLLING();
    static void CPU_POLL(CPU* cpu);
    void END_CPU_POLLING();

    double CPU_PERCENT();
    std::vector<double> CPU_CORE_PERCENT();

    virtual ~CPU(); 
private:
    std::thread* m_pollThread;
    bool m_isPolling;
};

static CPU* CPU_Instance;
