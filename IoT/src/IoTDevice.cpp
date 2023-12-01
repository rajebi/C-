#include <iostream>
#include "IoTDevice.h"

using namespace std;

// define the static variable instance for the IV table
ISRBaseClass* ISRBaseClass::IVT[MAX_INTERRUPTS] = {NULL}; 

Device1 d1(1, 5);

// this function simulates HW interrupts. 
void simulate_interrupts(){
    for (int i = 0; i < MAX_INTERRUPTS; i++){
        ISRBaseClass::invokeISR(i);
    }
}

// this function could not be inclined when forward declration for device_base class is used.
// it was giving comilation error. hence defined in .cpp
void ISRClass::ISR(){
    cout << "ISR handler invoked : " << interrupt_num << endl;
    device->process_data(interrupt_num);
}

void test_ISR_Table(){
    
    simulate_interrupts();

}

int main()
{
 
    cout << "Hello World - test" << endl;
   
    test_ISR_Table();
    return 0;
}