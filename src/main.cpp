#include <iostream>
#include <cpu.h>
#include <unistd.h>

int main(int argc, char** argv) {
    CPU* cpu = new CPU();
    CPU_Instance = cpu;

    cpu->START_CPU_POLLING();

    usleep(1000000);
    while(1) {
        std::cout << cpu->CPU_PERCENT() << std::endl;

        sleep(1);
    }
}
