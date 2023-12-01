#include <iostream>
using namespace std;

// This file defines 
//  class definitions for the IoT device software architecure, and 
//  interruptvector table in C++
//
// Problem statement
// 
// There are 3 types are IoT devices : device 1, device 2, device 3 (e.g UPS, PowerGrid, TempControl)
// There are 3 types of northbound intefaces for these devices : BLE, Ethernet, WiFi
// 
// The microcontrolers in these devices controls the core functionality. They provide 
// periodic status updates from the devices to the cloud through one of the Norhtbound 
// interface. Note, same device type can have either WiFi or BLE or Ethernet. There is no
// 1-to-1 mapping.

// We need to define two class hierarchy 1) device type 2) interface type. And interrupt vector. 
// There are two options possible for the end device abstraction
//     1) end-device has an interface relatation. In this case device will contain interface class.
//     2) end-device is a type of device and a type of interface to rest of the world. In this case.
//        we need derive end-device class from both device type and interface type hierarchy.



#define MAX_INTERRUPTS 2

//===================== interrupt class hierarchy ============================

class Device_base; // forward declaration

class ISRBaseClass{
    private:
        static ISRBaseClass* IVT[MAX_INTERRUPTS]; // ISR Vector Table
        
    public:
        ISRBaseClass(int n,  ISRBaseClass* ISR){
            // here in the constructor we are able to access the static variable. No need for static function.
            IVT[n] = ISR;  
            cout << "ISR registered with base class : " << n << endl;
        }
        static void invokeISR(int i){
            IVT[i]->ISR();
        }

        virtual void ISR() = 0; 

        virtual ~ISRBaseClass(){};
};

class ISRClass: public ISRBaseClass{
    private:
        int interrupt_num; // currently this has the same value as the IQRNum, but it can be set to different if needed.
        // interrupt owner, this is needed, hence the device specific proecessing can be
        // invoked using device->process_data()
        Device_base *device;
    public:
        ISRClass(int IRQNum, Device_base *d): ISRBaseClass(IRQNum, this), interrupt_num(IRQNum), device(d){
            cout << "ISR class created : " << IRQNum << endl;
        }
        int get_int_num(){return interrupt_num;}
        virtual void ISR();
};

//===================== Device class Hierarchy ==============================
// Device abstract class  (pure virtual class)
class Device_base{
    private:
        int device_id;
        char buf[10];  // device data
        // device has interrupts, hence ISR needs to be an association. Here we are
        // assuming this device has more than 1 interrupt. 
        ISRClass *ISR[MAX_INTERRUPTS];        

    public:
        Device_base(int Id): device_id(Id){
            // register the ISRs for the device. Also registers the device pointer to the ISR class.
            for (int i = 0; i < MAX_INTERRUPTS; i++)
                ISR[i] = new ISRClass(i, this);            
        };
   
        int get_device_Id() { return device_id;}
        virtual void display(int val) {cout << "virtual_base; val = " << val << endl;};
        virtual int get_device_type() = 0;  // this will be implemented by the individual device types.
        virtual void process_data(int n) = 0;

        virtual ~Device_base(){};
};

// Device1 class
class Device1: public Device_base{
    private:
        int device_type;
        struct _Device1_{
            int device_data;
            int Device1_specific;
        };
        struct _Device1_ context;
    public:
        
        Device1(int Id, int t): device_type(t), Device_base(Id) {}
                
        int get_device_type() { return device_type;}
        int get_device_data() { return context.device_data;}

        // process data when interrupt is received.
        virtual void process_data(int n){
             cout << "Device Id: " << get_device_Id() << ": process_data for interrupt : " << n << endl;   
        } 
        //friend ISRClass;

        virtual ~Device1(){};
};

// Device1 class
class Device2: public Device_base{
    private:
        int device_type;
        struct _Device2_{
            int device_data;
            int Device2_specific;
        };
        struct _Device2_ context;
    public:
        Device2(int t, int Id): device_type(t), Device_base(Id) {}
        int get_device_type() { return device_type;}
        int get_device_data() { return context.device_data;} 

        // process data when interrupt is received.
        virtual void process_data(int n){
             cout << "Device: process_data for interrupt : " << n << endl;   
        } 

        virtual ~Device2(){};
};
