#include <iostream>
#include <cpu.h>

int main(int argc, char** argv) {
    CPU* cpu = GetCPUInstance();

    cpu->START_CPU_POLLING();

    while(1) {
        std::cout << cpu->CPU_PERCENT() << std::endl;
    }
}
