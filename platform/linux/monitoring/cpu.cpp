#include <cpu.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <iostream>

CPU::CPU() {
    this->UPDATE_INTERVAL = 1000;
    this->m_isPolling = false;
    std::cout << "CPU Class Instantated" << std::endl;
}

void CPU::START_CPU_POLLING() {
    if (this->m_isPolling) {
        return;
    }
    this->m_isPolling = true;
    std::thread* t = new std::thread(&CPU::CPU_POLL, this);
    this->m_pollThread = t; 
    std::cout << "Worker CPU thread started" << std::endl;
}

void CPU::CPU_POLL(CPU* cpu) {
    std::cout << "From CPU Thread Start" << std::endl;
    while (true) {
        cpu->CPU_Mutex.lock();
        if (!cpu->m_isPolling) {
            cpu->CPU_Mutex.unlock();
            return;
        }
        cpu->CPU_PREVIOUS_IDLE++;
        cpu->CPU_PREVIOUS_TOTAL++;
        cpu->CPU_IDLE++;
        cpu->CPU_TOTAL++;
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

    this->CPU_Mutex.unlock();
    return (double)this->CPU_TOTAL;
}

CPU::~CPU() {
    this->m_isPolling = false;
    m_pollThread->join();
    delete m_pollThread;
}
