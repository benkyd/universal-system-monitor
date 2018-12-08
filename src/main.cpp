#include <iostream>
#include <cpu.h>
#include <unistd.h>

int main(int argc, char** argv) {
    CPU* cpu = new CPU();
    CPU_Instance = cpu;

    cpu->START_CPU_POLLING();

    while(1) {
        std::cout << "TOTAL CPU USAGE: " << cpu->CPU_PERCENT(0) << std::endl;
        // std::cout << "CORE 1 USAGE: " << cpu->CPU_PERCENT(1) << std::endl;
        // std::cout << "CORE 2 USAGE: " << cpu->CPU_PERCENT(2) << std::endl;
        // std::cout << "CORE 3 USAGE: " << cpu->CPU_PERCENT(3) << std::endl;
        // std::cout << "CORE 4 USAGE: " << cpu->CPU_PERCENT(4) << std::endl;
        std::cout << std::endl;
        sleep(1);
    }
}
