#include <iostream>
#include <cpu.h>
#include <unistd.h>

int main(int argc, char** argv) {
    CPU* cpu = new CPU();
    CPU_Instance = cpu;

    cpu->START_CPU_POLLING();

    while(1) {
        std::cout << "TOTAL CPU USAGE: " << cpu->CPU_PERCENT() << std::endl;
        sleep(1);
    }
}
