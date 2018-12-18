#pragma once

#include <cpu.h>
#include <temp.h>
#include <gpu.h>
#include <memstat.h>

struct Sys {
    unsigned long long SYSTEM_UPTIME;
    unsigned short CPU_CORES;

};

class System {
public:
    System();
    Sys getSystemSpec();
    virtual ~System();
private:
    Sys* m_Sys;
};

static System* System_Instance;
