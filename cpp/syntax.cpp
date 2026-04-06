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
    std::all_of(vec.begin(),vec.end(),::logic) // returns true if all elements satisfy 3rd arg logic. 3rg could be lambda too 
    std:: remove_if(vec.begin(),vec.end().::logic) // reorders, does not chamge container size, just shift relevant ones to left, need to pair with erase. 
int main() {
    std::vector<int> v = {1, 2, 3, 4, 5, 6};
    // Remove even numbers
    auto new_end = std::remove_if(v.begin(), v.end(), [](int n) { return n % 2 == 0; }); // new_end is next to last valid element. 
    
    // v is now {1, 3, 5, ?, ?, ?} - elements after new_end are unspecified // 1 3 5 2 4 6. 
    v.erase(new_end, v.end()); // v is now {1, 3, 5} 
    
    for (int n : v) std::cout << n << " "; // Output: 1 3 5
}
