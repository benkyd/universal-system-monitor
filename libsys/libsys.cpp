#include "libsys.h"

void initialize_libsys() {
    CPU_Instance = new CPU();
    Memory_Instance = new Memory();
    GPU_Instance = new GPU();
    System_Instance = new System();
}
