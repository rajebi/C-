#include <iostream>
using namespace std;

// OOP and C++ tips
/*
1)  Encapsulation, Inheritance and polymorphism are the 3 major concepts of OOP
2)  If you want to suppress member functions in derivered class that are defined
    in base class, declare as private in the derived class. So, when this object
    is instantialted, only the base class function will be visible to the outside.
3)  Always define Destructor as virtual because if delete is used on an object it 
    always invokes the destructor of the type of the objet - static type. E.g if B 
    is derived from A. 
        A *a; 
        B *b;
        a = b;
        delete (a). If we don't declare destructor as virtual, in this case only the
                    destructor of A will be called. This will result in memory leak.
                    If its defined as virtual, then the destructor of B is called.
4)  To make a class read only, then define it as const. Then no non-const memeber function
    can be invoked 
        class A const{

        }
5)  If you don't want a class to be assgined or copied (e.g passing by value or return by value),
    keep copy constructor and assignment operator in private. Keeping copy constructor in private
    restricts pass by value. Keeping assignment operator in private, restricts assignments.
6)  Copy constructor parameter should be a reference, otherwise infinite recursion will happen
7)  Derivted class cannot access the base class's private members, but it can access the
    base class's protected and public.
8)  Outside class cannot access private and protected member.
9)  Use *res = dynamci_cast<calssType *>object to protect unexpted casting happening from 
    derived type to base type. If res = NULL, then the casting cannot be done, because the
    object is not of type classType.
10) reinterpret_cast should be used for resolving integer to pointer casting or casting func pointers
    e.g     unsigned car *pm1, *pm2
            pm1 = 0x8000 // illegal
            pm2 = reinterpret_case<unsigned char *>0x8000 // legal
    This is useful for memory mapped I/O    
11) Member initializers can be used for all data members, but the must be used if a class
    contains const, referene or member object.

    class A (int v1, int v2) : x(val), y(v2) {}
    
12) Composition: An object is constructed inside out, the member objects's constructors called before 
    the host object's constructor. That is, the member objects are constructed before the host object.
    But destructed in reverse order. The host object's destructor is called first
13) Default constructors are invoked only if an object has no constructors defined at all. 
    If an obhect has other constructors (non-default), then compilation error will happen if the 
    object is another object (composition). Default constructor is one that has no parameters.
14) A friend class/function can access the private member of a class
15) A static member function (class function) can access only static data member of a class
16) Constructors, assigment operators and friends are not inherited.
17) Derived class's destructor is invoked before base class's
18) Virtual constructor cannot exist, but it can be simulated using clone technique. 
19) Using cloning method (public method that returns copy of the object) is better than using
    copy constructor or assignment operator. Hence, declaring copy constr and assignment oper in 
    private is a good practive to avoid unwanted copying or assignment. if ther eis a real need 
    to copy an object to new one, then closing can be used.
20) A derived class can make a virtual method private, which is public in the base class. Thus
    this functionality is restricted in the derived class.
21) Singleton class: Make the constructor proted and provide a public method that returns
    a new instance of the class only if the static variable instance_count == 0, else retruns
    the same instance *this.
22) In C++, initialization occurs when a new object is created. (e.g A x = y). Here x is a new 
    object created. Initilization are performed by the constructor. One kind of initialization
    special in C++ the initialization of an object using the value of another object of that class.
    The contructor that performs that operation is called copy constructor.
23) Assginment operator changes the value of an existing object (e.g x = y). operator=

*/


// class/object association - done
// class/object aggregation - done 
// inheritance, - done
// multiple inheritance
// copy constructor
// assignment operator - done
// function overloading - done  (passing different type or number of arguments)
// virtual / abstract class
// singleton class - done
// static functions - done
// const functions - done
// virtial class - done
// interupt vector class
// function pointer
// union
// friend class

//============= example of function overriding and virtual function ============

// example of pure virtual class. pure virtial class cannot be instantiated.
class pure_virtual_class{ 
    int i;

    public:
        pure_virtual_class(){};
        virtual void doo() = 0; // this is what makes this class pure virtual.
};

class virtual_base: public pure_virtual_class{
    public:
        virtual_base(){};
        void doo(){ cout << "pure virtual function overridden" << endl;}; 
        virtual void foo(int val) {cout << "virtual_base; val = " << val << endl;};
        virtual void goo() {cout << "virtual_base" << endl;};
};

class derived_from_vritual: public virtual_base{
    public:
        derived_from_vritual(){};
        virtual void foo(int val, int v2) {cout << "derived_from_vritual val = " << val << " " << v2 << endl;};
        virtual void goo() {cout << "derived_from_vritual" << endl;};
        virtual void foo(int v1, int v2, int v3) {cout << "derived_from_vritual overloaded foo val = " << v1 << endl;}
};

class second_derived_from_vritual: public derived_from_vritual{
    public:
        second_derived_from_vritual(){};
        virtual void goo() {cout << "second_derived_from_vritual" << endl;};
};

class derived_from_vritual_2: public virtual_base{
    public:
    derived_from_vritual_2(){};
    virtual void foo(string s) {cout << "derived_from_vritual_2 val = " << s << endl;};
};

class test_dynamic_binding_n_fn_overload{
    public:
        test_dynamic_binding_n_fn_overload(){};

        virtual_base vb;
        derived_from_vritual dfv;
        derived_from_vritual_2 dfv2;
        second_derived_from_vritual sdfv;
        virtual_base *vb_ptr = &vb;
        virtual_base &t = dfv;

        void test_dynamic_binding_function(){
            vb_ptr->goo();  // this will invoke the vritual bass goo
            vb_ptr = &dfv;
            vb_ptr->goo();  // this will invoke derived_from_vritual's gooo
            vb_ptr = &sdfv;
            vb_ptr->goo();  // this sill invoke  second_derived_from_vritual goo         
        }
        void test_function_overloading(){
            dfv.foo(4, 10); 
            dfv2.foo("test");
            t.foo(5); // this will invoke the base class function
            //t.foo(5, 6); // this will compilation error because overloaded function cannot exist across classes.
            dfv.foo(6, 7, 8); // this will invoke derived class' overloaded function

        }
};

class Singleton{
// Make all the constructors of the class private.
// Delete the copy constructor of the class. because compiler may create a default one.
// Make a private static pointer that can point to the same class object (singleton class).
// Make a public static method that returns the pointer to the same class object (singleton class).

private:
    // member variables
    string name, Id; 
    // static pointer which will points to the instance of this class
    static Singleton* instancePtr; 
    // Default constructor
    Singleton(){ };
public:
    /// deleting copy constructor
    Singleton(const Singleton& obj) = delete; 
    /* getInstance() is a static method that returns an instance when it is invoked. It returns the same
        instance if it is invoked more than once as an instance of Singleton class is already created. It is static
        because we have to invoke this method without any object of Singleton class 
        and static method can be invoked without object of class.
    
        As constructor is private so we cannot create object of Singleton class without a static method as they can be
        called without objects. We have to create an instance of this Singleton class by using getInstance() method. */
    static Singleton* getInstance() {
        // If there is no instance of class then we can create an instance.
        if (instancePtr == NULL) {
            // We can access private members within the class.
            instancePtr = new Singleton(); 
            return instancePtr; 
        } else {
            // if instancePtr != NULL that means the class already have an instance. 
            // So, we are returning that instance and not creating new one.
            return instancePtr;
        }
    }
    void set_members(string name, string Id){
        //cout << name << Id << endl;
        this->name = name; this->Id = Id;  // we need to use "this" explicitly because constructor is private.
    };
    void print_members(){cout << name << "," << Id << endl;};
};

// static funcion, const function, assgignment operator, copy constructor, operator overloading
class features{
private:
    static int val;
    int val_non_static;
public: 
    features(){};
    void foo() {};
    static void goo() {};
    // static function
    //----------------
    // It is a member function that is used to access only static data members. 
    // It cannot access non-static data members not even call non-static member functions. 
    // It can be called even if no objects of the class exist
    static void static_fn(int n){
        val = n;
        goo(); // ok because static function.
        //val_non_static = n; // this will give error because we are trying to change non static 
        // value using static function.
        //foo(); // this will also give error
        
    };
    void set_data(int m){ val = m;};
    void get_data(int &m) const {
        m = val_non_static;
        //val_non_static++;  // this will give error because const function is trying to modify a member value.
    }

    // Const function and object
    // -------------------------
    // When a function is declared as const, it can be called on any type of object. 
    // Non-const functions can only be called by non-const objects.      
    class obj_class{
        private:
            int v1 = 5;
        public:
            obj_class(){};
            int get_val(){return v1;};
            int get_val1() const {return v1;}
    };

    const obj_class obj;  // const object
    obj_class obj1; // non const object

    void access_const_obj(){
        // when a fn is declared const, it can be called on by both const and non-const objects
        obj1.get_val1(); 
        obj.get_val1();        
        // when a fn is not declared const, it can be called only non-const objects
        //obj.get_val(); // this will give error because we are accessing a const object.
        obj1.get_val();
    };

    // copy constructor and assignment operator
    // --------------------------------------
    class Test {
    private:
        int val; 
    public:
        Test() {}
        // copy constructor
        Test(const Test& t){ // parameter is const, because the passed in object should not be modified.
            cout << "Copy constructor called " << endl;
            // if deep copy is needed, that is, if a member's memory is a dynamically allocated 
            // the default copy constructor witll do only shallow copy. Hence, here 
            // we need to explicitly allocate memory for the target object's member and copy the content.
            val = t.val;
        }
        // assignment operator
        // -------------------
        Test & operator=(const Test& t){
            cout << "Assignment operator called " << endl;
            return *this;
        }
        void set_val(int v){val = v;}
        int get_val(){return val;}
    };

    void test_copy_constructor_and_assignment_operator(){
        Test t1, t2;
        
        t2 = t1; // assignment operator is called. this is called when an object is assigned to another.
        Test t3 = t1;  // copy constructor is called. It is called when an object is instantiated.
    }

    // operator overloding
    // ------------------
    class Complex{
        private:
            int real; int imag;
        public:
            Complex(int r = 0, int i = 0){
                real = r; imag = i;
            }
        Complex operator+(const Complex & obj){
            Complex res;
            res.real = real + obj.real;
            res.imag = imag + obj.imag;
            return res;
        }
        void print() { cout << real << " + i" << imag << '\n'; }
    };
    void test_operator_overloading()
    {
        Complex c1(1, 2), c2(3, 4), c3;
        Complex c4 = c1 + c2;

        c3 = c1+c4;
        c4.print();  c3.print(); 
    }

    // Cloning
    // ---------
    // Using cloning method (public method that returns copy of the object) is better than using
    // copy constructor or assignment operator. Hence, declaring copy constr and assignment oper in 
    // private is a good practive to avoid unwanted copying or assignment. if there is a real need 
    // to copy an object to new one, then closing can be used.
    class cloning{
        public: 
            cloning(){}
            cloning *get_object(){ 
                cloning *cloned_obj = new cloning();
                // copy all the data of the current object to the new
                // ....                 
                return cloned_obj;
            }
    };

};

class write_only_register{
private:
    int w_reg;
    // leave these functions undefined, and keep them in private
    write_only_register(write_only_register const &); // copy constructor
    write_only_register & operator=(write_only_register const &); // assignment operator
public:
    write_only_register(){cout << "new value updated " << endl; }
    write_only_register(int v):w_reg(v) {cout << "new value updated " << w_reg << endl; }
    write_only_register & operator=(int v){
        w_reg = v;
        cout << "new value updated " << w_reg << endl; 
        return *this;
    }
    void test_write_only_register(){
        write_only_register reg(5);
        reg = 10; // this will update the value using the member function.
        // here copy constructor will be called, Since it is decalared as private, we will get compile time failre
        //write_only_register reg1 = reg; 
        //cout << reg.w_reg; // trying to access pvt valieable.
        write_only_register reg2; 
        //reg2 = reg; // this will als fail because assignment operator is pvt.
    }    
};

//========================== multiple derivered class ================

class A {
    private:
        int a_private = 10;
    protected:
        int a_protected = 20;
    public:
        A(){};
        A(int a): a_private(a){};
        int a = 1;
        void a_test(){cout << "class A" << endl;}
};

class B {
    public:
        B(){};
        B(int b): b(b) {};
        int b = 2;
        void b_test(){cout << "class B" << endl;}
};

class D; // forward declaration
class C : public A, public B {
    private:
        int c_private = 10;

    public:

        C(int c):c_private(c){};

        void c_test(){cout << "class C" << endl;}
        void d_test(){
            a_test();  // able to access base class member function
            b_test();
        }
    friend D;
};
class D{
    private:
        int d;
        A a;
        B b;
        C c; 
    public:
        D(int x, int y, int z, int d):a(x), b(y), c(z), d(d){};
        void test_derived_from_multiple_class_and_friend_class(){
            class C c(3);
            // since C is derived from both A and B, it can access both A and B's public and protected members.
            cout << "access base class A's member a = " << c.a << "; access base class B's member b = " << c.b << endl;
            cout << "access base class A's protected member  = " << c.a_protected << endl;
            //cout << "access base class A's private member  = " << c.a_private << endl; cannnot access private member
            c.a_test();
            c.b_test();
            cout << "D is friend of C, accessing C's private data : " << c.c_private << endl;
        }
};

// this is the main test calss which implements all the test cases for the class defined above. This 
// will be invoked from the basics.cpp main()
Singleton* Singleton::instancePtr = NULL; 
class basic_test_main{
    public:
        basic_test_main(){};

        // initializing instancePtr with NULL. Since this is a static variable, this cannot be defined inside
        // another class.         
        //Singleton* Singleton::instancePtr = NULL; 

        // this function implements all the test cases
        void cpp_basic_tests(){
            //pure_virtual_class pc; // this will give compilation error
            test_dynamic_binding_n_fn_overload tdb;
            tdb.test_dynamic_binding_function();   
            tdb.test_function_overloading();

            // test features
            features f;
            f.access_const_obj();
            f.test_copy_constructor_and_assignment_operator();
            f.test_operator_overloading();

            // test singleton class
            Singleton* someSingleton = Singleton::getInstance();
            someSingleton->set_members("single", "10");
            someSingleton->print_members();

            // test write only register
            write_only_register w_o;
            w_o.test_write_only_register();

            // multiple class drivative and friend class access
            D d(1, 2, 3, 4);
            d.test_derived_from_multiple_class_and_friend_class();
        }
};


// example of inheritance, aggrgation, function overloading.
class Company{
    string name;
    public:
        Company(string name){
            name = name;
        };
        virtual ~Company(){};
};

class Employee{
private:
    int emp_num = 0;
    string emp_name;
public: 
    Employee(){cout << "Employee object is created" << endl;};
    Employee(string name){  // constructor
        cout << "Employee object is created" << endl;
        emp_name = name;
        emp_num++;
    };
    void update_name(string name){
        emp_name = name;
        emp_num++;
    };
    string get_name(){
        return emp_name;
    };

    virtual ~Employee(){cout << "Employee object is destroyed" << endl;};  // destructor

};

class Department{

private:
    Employee e[3];
    Employee *dept_head; 
    int dept_id = 0;
    string dept_name;
    int num_of_emps = 0;
    int pvt_member_chek = 0;
    int test_var1 = 0;

public:
    Department(): dept_name("test"), test_var1(5) { // example of initializing member variables before the body of the function
       cout << "Department object created" << endl;
    };

    //Department(string dep_name, string dep_head_name){  // constructor
      //  Department(); // call the other contructor
        //dept_head = new Employee(dep_head_name);
        //dept_name = dep_name;
        //dept_id++;
    //};
    void add_new_empl(string name);
    //void update_dept_name(string name);

    void print_emps(){
        for (int i = 0; i < num_of_emps; i++){
            cout << e[i].get_name() << endl;
        }
    }
    virtual ~Department(){  // destructor
        //delete dept_head;  // release the allocated memeory
        cout << "Department object is destroyed" << endl;
    };
};

// public inheritance makes public members of the base class public in the derived class, and the protected 
// members of the base class remain protected in the derived class. The private members are NOT accessible 
// by the derived class.
// protected inheritance makes the public and protected members of the base class protected in the derived class.
// private inheritance makes the public and protected members of the base class private in the derived class. This
// means derived class object cannot access base class members. 

class Team: public Department{

    int teamId;
    string name;
    string team_lead;

public: 
    Team(int Id, string name){
        cout << "Team object is created" << endl;
        teamId = Id;
        name = name;
        //pvt_member_chek = 5; this will give error because it is decalred private in the base calss
    };
    
    void assign_team_lead(string name){team_lead = name; };
    void add_new_empl(string name){
        // since both derived class and base calss function have the same signature
        // we need to use the scope resolution to call the base class method.
        cout << "Team derived class add_new_empl is invoked for " << name << endl;
        Department::add_new_empl(name); 
    };

    void add_new_empl(string name, int type){
        // this will invoke Team's add_new_empl()
        add_new_empl(name); 
        if (type){team_lead = name; };
    };

    //void get_departmentId();
    void print_employees(){
        // print team lead, which is not appliecable to department.
        cout << "team lead = " << team_lead << endl; 
        Department::print_emps();
        
    };

    void update_teamId(int Id) const{ };

    ~Team(){
        cout << "Team object is destroyed" << endl;
    };
};

// public, protected and private derived class
class Base {
  public:
    int x;
  protected:
    int y;
  private:
    int z;
};

class PublicDerived: public Base {
  // x is public
  // y is protected
  // z is not accessible from PublicDerived
};

class ProtectedDerived: protected Base {
  // x is protected
  // y is protected
  // z is not accessible from ProtectedDerived
};

class PrivateDerived: private Base {
  // x is private
  // y is private
  // z is not accessible from PrivateDerived
};


#define MAX_INTERRUPTS 3


class Interrupt_base_class{

    private:
        Interrupt_base_class* ISRVectorTable[MAX_INTERRUPTS];

    public:
        Interrupt_base_class(){}
        void register_intr(int num, Interrupt_base_class* ISRObjectThisPtr){
            ISRVectorTable[num] = ISRObjectThisPtr;
        }
        //static void invokeISR(int i){
        //    ISRVectorTable[i]->ISR();
        //}
        virtual void ISR() = 0; 
};

class ISRClass: public Interrupt_base_class{
    private:
        int num = 0;

    public:
        ISRClass(int n): num(n){
            cout << "ISR handler created : " << n << endl;
            Interrupt_base_class::register_intr(num, this);
        }
        virtual void ISR(){
            cout << "ISR handler invoked : " << num << endl;
        }

    friend class Device;    
};

class Device{
    
    private:
        char buf[10];
    public:
        Device(){}
        void process_data(){
             cout << "Device: process_data : " << endl;   
        } 
};

