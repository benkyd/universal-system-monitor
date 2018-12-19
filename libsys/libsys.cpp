#include "libsys.h"

void initialize_libsys() {
    __cpu = new CPU();
    __mem = new Memory();
    __gpu = new GPU();
    __sys = new System();

    CPU_Instance = __cpu;
    Memory_Instance = __mem;
    GPU_Instance = __gpu;
    System_Instance = __sys;
}
