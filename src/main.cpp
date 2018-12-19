#include <libsys.h>

#include <iostream>
#include <unistd.h>

int main(int argc, char** argv) {
    initialize_libsys();
        sleep(1);

    CPU_Instance->START_CPU_POLLING();
    Memory_Instance->START_MEMORY_POLLING();

    std::cout << std::endl;
    Sys sys = System_Instance->getSystemSpec();

    while(1) {
        sleep(1);
        std::cout << std::endl;
        for (unsigned int thread = 0; thread <= CPU_Instance->CPU_HARDWARE_THREADS; thread++) {
            std::cout << "CORE " << thread << " USAGE: " << CPU_Instance->CPU_PERCENT(thread) << std::endl;
        }
        std::cout << "CPU FREQUENCY: " << CPU_Instance->cpuStat->FREQ << "MHz" << std::endl;
    }
}
