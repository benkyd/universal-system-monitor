#include <cpu.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <iostream>

CPU::CPU() {
    this->UPDATE_INTERVAL = 1000;
    this->m_isPolling = false;
}

void CPU::START_CPU_POLLING() {
    if (this->m_isPolling) {
        return;
    }
    std::thread t(&CPU::CPU_POLL);
    this->m_pollThread = &t; 
    this->m_isPolling = true;
    std::cout << "Worker CPU thread started" << std::endl;
}

void CPU::CPU_POLL() {
    CPU* cpu = GetCPUInstance();
    while (cpu->m_isPolling) {
        cpu->CPU_PREVIOUS_IDLE++;
        cpu->CPU_PREVIOUS_TOTAL++;
        cpu->CPU_IDLE++;
        cpu->CPU_TOTAL++;
        usleep(cpu->UPDATE_INTERVAL);
    }
}

void CPU::END_CPU_POLLING() {
    if (!this->m_isPolling) {
        return;
    }
    this->m_isPolling = false;
    usleep(this->UPDATE_INTERVAL + 5);
    m_pollThread->join();
    delete m_pollThread;
}

double CPU::CPU_PERCENT() {
    return (double)this->CPU_TOTAL;
}

CPU::~CPU() {
    CPU::m_pollThread->~thread();
}
