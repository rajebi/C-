#include <iostream>
using namespace std;
#include "basics.h"

// singleton class
// class/object association
// class/object aggregation
// inheritance, multiple inheritance
// const function
// copy constructor
// assignment operator 
// functional overloading
// virtual / abstract class

class test_class{

    private:
        int ref_count = 0;
    public: 
        test_class(){
            cout << "basic class instantiated" << endl;
            ref_count++;
        };

        // Data  Members 
        string name = "test class"; 
        // Member Functions() 
        void printname() { cout << "class name is:" << name << ", ref_count = " << ref_count << endl; }     
};

void Department::add_new_empl(string name){

    e[num_of_emps].update_name(name);
    num_of_emps++;
    //cout << "new emp" << endl;
};

void test_derived_class()
{
    Team t(1, "dev");
    Department &d = t;
    
    t.add_new_empl("tom", 1); // this invokes overrided Team class function.
    t.add_new_empl("sam");
    d.add_new_empl("jon"); // base class function is invoked.
    t.print_employees();
    // this invokes department base class method
    t.print_emps();

    // this should invoke base class, but not working. need to check. 
    //((Department)t).add_new_empl("job"); 
};

void pass_by_reference(int *i, int &j){
        (*i)++; j++;
};

void pass_by_reference_test()
{
    int m = 5, n = 10;
    pass_by_reference(&m, n);
    cout << m << "," << n << endl;

};

void test_write_only_register()
{
    write_only_register reg(5);
    reg = 10; // this will update the value using the member function.
   // here copy constructor will be called, Since it is decalared as private, we will get compile time failre
   //write_only_register reg1 = reg; 
   //cout << reg.w_reg; // trying to access pvt valieable.
   write_only_register reg2; 
   //reg2 = reg; // this will als fail because assignment operator is pvt.

}

void test_ISR_Table(){

    Device device;
    ISRClass *ISR;

    //ISR = new ISRClass(0);
    //ISR->ISR();

    //Interrupt_base_class::register_intr(0, ISR);

    // register ISR
    for (int i = 0; i < MAX_INTERRUPTS; i++){
        ISR = new ISRClass(i);
    }
    // invoke ISR
    for (int i = 0; i < MAX_INTERRUPTS; i++){
        //Interrupt_base_class::invokeISR(i);
    }
}


int main()
{
 
    cout << "Hello World" << endl;
    basic_test_main btst;

    btst.cpp_basic_tests();

    //test_class t;
    //t.printname();

    //pass_by_reference_test();

    //test_derived_class();

    //test_function_overriding();
    //test_pure_virtual();
    //singleton_example();
    //test_features();
    //test_ISR_Table();



    return 0;
}