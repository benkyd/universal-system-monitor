#include <sys.h>

System::System() {
    this->m_Sys = new Sys();

    if (CPU_Instance = NULL) {
        CPU_Instance = new CPU();
    }

    if (Memory_Instance == NULL) {
        Memory_Instance = new Memory();
    }

    
}

Sys* System::getSystemSpec() {
    return m_Sys;
}

System::~System() {

}
