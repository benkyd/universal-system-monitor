#pragma once

#include <thread>
#include <vector>
#include <mutex>
#include <map>

class CPU {
public:
    CPU();
    
    std::mutex CPU_Mutex;
    int CPU_PREVIOUS_WORK;
    int CPU_PREVIOUS_TOTAL;
    int CPU_WORK;
    int CPU_TOTAL;

    int UPDATE_INTERVAL; // ms

    std::map<int, std::map<int, int>> CPU_PREVIOUS_CORES_WORK_AND_TOTAL;
    std::map<int, std::map<int, int>> CPU_CORES_WORK_AND_TOTAL;
    int CPU_HARDWARE_THREADS = std::thread::hardware_concurrency();

    void START_CPU_POLLING();
    static void CPU_POLL(CPU* cpu);
    void END_CPU_POLLING();

    double CPU_PERCENT(int core);
    std::vector<double> CPU_CORE_PERCENT();

    virtual ~CPU(); 
private:        
    std::thread* m_pollThread;
    bool m_isPolling;
};

static CPU* CPU_Instance;
