#pragma once

#include <thread>
#include <vector>
#include <mutex>
#include <map>
#include <cstring> // For memcpy 

struct CPUStat {
    std::string ARCHITECTURE;
    std::string MODEL_NAME;
    unsigned short HARDWARE_THREADS;
    long double MAX_FREQ;
    long double MIN_FREQ;
    long double FREQ;
    long double PERCENT_USAGE;
};

class CPU {
public:
    CPU();
    static CPU* Create();

    std::mutex CPU_Mutex;
    CPUStat* cpuStat;
    CPUStat getCPUStat();

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

    bool m_isPolling;

    virtual ~CPU(); 
private:        
    std::thread* m_pollThread;
};

static CPU* CPU_Instance;

class CPUFactory {
public:
    
private:
};
