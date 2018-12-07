#include <cpu.h>

#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <math.h> 

CPU::CPU() {
    this->UPDATE_INTERVAL = 1000;
    this->m_isPolling = false;
}

void CPU::START_CPU_POLLING() {
    if (this->m_isPolling) {
        return;
    }
    this->m_isPolling = true;
    std::cout << "Starting CPU worker thread" << std::endl;
    std::thread* t = new std::thread(&CPU::CPU_POLL, this);
    this->m_pollThread = t; 
}

void CPU::CPU_POLL(CPU* cpu) {
    std::cout << "New CPU worker thread" << std::endl;

    while (true) {
        cpu->CPU_Mutex.lock();
        if (!cpu->m_isPolling) {
            cpu->CPU_Mutex.unlock();
            return;
        }
        cpu->CPU_Mutex.unlock();

        // READ TOTAL CPU
        unsigned long long luser, nice, system, idle, iowait,
            irq, softirq;
        FILE* file = fopen("/proc/stat", "r");
        fscanf(file, "cpu %llu %llu %llu %llu %llu %llu %llu", &luser, 
            &nice, &system, &idle, &iowait, &irq, &softirq);
        fclose(file);

        cpu->CPU_Mutex.lock();

        // CALCULATE TOTAL CPU
        cpu->CPU_PREVIOUS_TOTAL = cpu->CPU_TOTAL;
        cpu->CPU_PREVIOUS_WORK = cpu->CPU_WORK;
        cpu->CPU_TOTAL = luser + nice + system + idle + iowait + irq + softirq;
        cpu->CPU_WORK = luser + nice + system;

        cpu->CPU_Mutex.unlock();
        sleep(1);
    }
}

void CPU::END_CPU_POLLING() {
    if (!this->m_isPolling) {
        return;
    }
    this->m_isPolling = false;
    m_pollThread->join();
    delete m_pollThread;
}

double CPU::CPU_PERCENT() {
    this->CPU_Mutex.lock();
    long double workOverTime = this->CPU_PREVIOUS_WORK - this->CPU_WORK;
    long double totalOverTime = this->CPU_PREVIOUS_TOTAL - this->CPU_TOTAL;
    this->CPU_Mutex.unlock();

    double percent = (workOverTime / totalOverTime) * 100;
    if (isnan(percent)) percent = -1;
    return (double)percent;
}

std::vector<double> CPU::CPU_CORE_PERCENT() {
    std::vector<double> output;
    return output;    
}

CPU::~CPU() {
    this->m_isPolling = false;
    m_pollThread->join();
    delete m_pollThread;
}
