// class -> blueprint for creating object ( compiles code of class) , class template-> blueprint of creating class. ( does not compile the class code until  object of it is instantiated)
// template member function code is compiled  by compiler  only  when function is called or used. 
#include <iostream>
template<typename T>
class A {
public:
    void fun(T i) {
        std::cout << i << std::endl;
    }

    template<typename U>
    void fun(U i) {
        std::cout << i << std::endl;
        std::cout << "i got exec U" << '\n';
    }

    // Every member function template declared inside a class needs its own template<typename U> prefix.( local to every function)
    template<typename U>
    void external_fun(U input);
};

// need redeclare templates for class and fucntion. 
template<typename T>
template<typename U>
void A<T>::external_fun(U input) {  // When defining out-of-line, you must write A<T>:: (not just A::) because A is a class template.
    std::cout << " hi from U " << input << std::endl;
}

// 1. The Primary Template
template <typename T>
class Base {
public:
    void sayHello() { std::cout << "Hello!\n"; }
};

// 2. The Specialization (e.g., for bool)
// This completely REPLACES Base for the 'bool' type.
template <>
class Base<bool> {
public:
    // Notice: There is NO sayHello() function here!
    void doSomethingElse() { std::cout << "Doing boolean things.\n"; }
};

// 3. The Derived Template
template <typename T>
class Derived : public Base<T> {
public:
    void run() {
        sayHello(); // ❌ non dependent name, in phase 1 compiler look for global function and fails: this->sayHello();, Base<T>::sayHello(); makes it dependent name and this get resolved in phase 2.
    }
};

int main() {
    A<double> a;
    a.fun(5.1);
    a.fun<int>(5.33);
    a.external_fun(9.99); // Deduces U = double
    a.external_fun(9);    // Deduces U = int
    return 0;
}
/*
1) You are reading the Derived<T> class for the very first time (Phase 1). You don't know what T is yet.

    You see the call to sayHello(). You look at the primary Base<T> and think: "Well, the primary Base has a sayHello(). Should I just connect this function call to that one?"
    
    If the compiler said "Yes", here is the disaster that would happen:
    Later in main(), someone writes:
    C++
    Derived<bool> d;
    d.run();
    
    Now T is bool. Derived<bool> inherits from Base<bool>. But wait—Base<bool> doesn't have a sayHello() function!
    If the compiler had aggressively locked in the sayHello() function during Phase 1 based on the primary template, it would generate corrupted code for Derived<bool>.

2)-> enum var/ const static var or inline static var  in a class/struct are STATIC CONST( except for inline)  i.e no object initalization needed for using them(
    cout<< A::a<<'\n'; is enough) , const staic are immutable whereas inline staic are mutable and follows ODR(one defination rule)->there is only a single instance of
     a var  shared across all translation units (.cpp files).
  -> static var in a function or outside,  inside a clas is initialized once( inside function one is only initalized the very first time fucntion is called)
     and shared across objects. 
  -> static outside class makes them global but also makes them internal linkage( only class/func inside that cpp file can access it, UNLIKE global var(could be used by
      different cpp file by extern keyword)).
  -> static vs inline staic-> linker behanves differently( stsaic is declaration only and required out of line defination whereas inline is declarationa nd defincation 
      in single line.Linker in case of inline let 2 seprate cpp file def and dec inline var as weak sybol and combine them as one.( chane in var in 1 cpp changes in another).
    

*/
