#include <iostream>
#include <cpu.h>
#include <unistd.h>

int main(int argc, char** argv) {
    CPU* cpu = new CPU();
    CPU_Instance = cpu;

    cpu->START_CPU_POLLING();

    while(1) {
        sleep(1);
        // for (unsigned int thread = 0; thread < cpu->CPU_HARDWARE_THREADS; thread++) {
        //     std::cout << "CORE " << thread << " USAGE: " << cpu->CPU_PERCENT(thread) << std::endl;
        // }

        for (unsigned int thread = 0; thread <= cpu->CPU_HARDWARE_THREADS; thread++) {
            std::cout << "CORE " << thread << " USAGE: " << cpu->CPU_PERCENT(thread) << std::endl;
        }
        std::cout << std::endl;
    }
}
