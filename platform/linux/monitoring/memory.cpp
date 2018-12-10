#include <memstat.h>

#include <iostream>
#include <unistd.h>
#include <sys/sysinfo.h>

// struct sysinfo {
//     long uptime;             /* Seconds since boot */
//     unsigned long loads[3];  /* 1, 5, and 15 minute load averages */
//     unsigned long totalram;  /* Total usable main memory size */
//     unsigned long freeram;   /* Available memory size */
//     unsigned long sharedram; /* Amount of shared memory */
//     unsigned long bufferram; /* Memory used by buffers */
//     unsigned long totalswap; /* Total swap space size */
//     unsigned long freeswap;  /* swap space still available */
//     unsigned short procs;    /* Number of current processes */
//     unsigned long totalhigh; /* Total high memory size */
//     unsigned long freehigh;  /* Available high memory size */
//     unsigned int mem_unit;   /* Memory unit size in bytes */
//     char _f[20-2*sizeof(long)-sizeof(int)]; /* IDFK what this does, it doesnt work without it*/
// };

Memory::Memory() {
    this->UPDATE_INTERVAL = 1000;
    this->m_isPolling = false;
    memStat = new MemStat();
    struct sysinfo info;
    sysinfo(&info);
    std::cout << "Total RAM Memory supported: " << info.totalram / 1.049e+6 << "MB" << std::endl;
}

MemStat Memory::getMemStat() {
    MemStat stat;
    this->Memory_Mutex.lock();
    memcpy(&stat, this->memStat, sizeof(MemStat));
    this->Memory_Mutex.unlock();
    return stat;
}

void Memory::START_MEMORY_POLLING() {
    if (this->m_isPolling) {
        return;
    }
    this->m_isPolling = true;
    std::cout << "Starting memory worker thread" << std::endl;
    m_pollThread = new std::thread(&Memory::MEMORY_POLL, this);
}

void Memory::MEMORY_POLL(Memory* mem) {
    std::cout << "New memory worker thread" << std::endl;

    while (true) {
        mem->Memory_Mutex.lock();
        if (!mem->m_isPolling) {
            mem->Memory_Mutex.unlock();
            return;
        }
        mem->Memory_Mutex.unlock();

        struct sysinfo info;
        sysinfo(&info);

        mem->Memory_Mutex.lock();

        mem->memStat->TOTAL_MB  = info.totalram  / 1.049e+6;
        mem->memStat->FREE_MB   = info.freeram   / 1.049e+6;
        mem->memStat->SHARED_MB = info.sharedram / 1.049e+6;
        mem->memStat->BUFFER_MB = info.bufferram / 1.049e+6;
        mem->memStat->TOTAL_RUNNING_PROCS = info.procs;

        mem->Memory_Mutex.unlock();

        sleep(1);
    }
}

void Memory::END_MEMORY_POLLING() {
    if (!this->m_isPolling) {
        return;
    }
    this->m_isPolling = false;
    m_pollThread->join();
    delete m_pollThread;
}

Memory::~Memory() {
    this->m_isPolling = false;
    m_pollThread->join();
    delete m_pollThread;
}
