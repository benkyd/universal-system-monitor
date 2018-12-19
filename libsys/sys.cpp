#include "sys.h"

System::System() {
    this->m_Sys = new Sys();
}

Sys System::getSystemSpec() {
    Sys temp;
    memcpy(&temp, m_Sys, sizeof(Sys));
    return temp;
}

System::~System() {

}
