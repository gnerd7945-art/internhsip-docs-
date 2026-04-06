#include <iostream>
#include <string>
1) Inititalization:-
class MyClass {
private:
    int id;
    std::string name;
    const int limit; // Const members must be initialized here

public:
    // Member initializer list
    MyClass(int i, const std::string& n) : id(i), name(n), limit(100) {
        // Constructor body: all members are already initialized here
        std::cout << "Constructor body executed." << std::endl;
    }
};

int main() {
    MyClass obj(1, "Example");
    return 0;
}



//// header file (Robot.h) describing definations
class Robot {
private:
    int _id;        // PERMANENT STORAGE: This is the "shelf" 
                    // It exists, but it's empty right now.

public:
    // This is just a PROMISE that a constructor exists.
    Robot(int id);  
    
    void sayHello(); 
};
///cpp file adding values to constructor
#include "Robot.h" // "Hey, give me that blueprint!"
#include <iostream>

// Robot::Robot means "The Robot constructor inside the Robot class"
Robot::Robot(int id) : _id(id) { 
    // Data has moved from the 'id' parameter 
    // into the '_id' permanent storage.
}

void Robot::sayHello() {
    std::cout << "Hello, my ID is " << _id << std::endl;
}


2) THREADS:-
    std:: thread worker(func_name,argument) // thread needs function address and argument seperately.



3) some imp funcitons:-
    std::to_string(some_int) // convert ot string
    std::stoi(some string) // convert to int 
