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
    std::transform(vec.begin(), vec.end(),another_vec.begin(),[](int& a)->int{re turn logic});// change range based loop with some logic or to a different container. 
    std::optional<data type> var; 
    std::any_of(vec.begin(),vec.end(),[](int& i)->int{return i%2==0;})

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5, 6};
    // Remove even numbers
    auto new_end = std::remove_if(v.begin(), v.end(), [](int n) { return n % 2 == 0; }); // new_end is next to last valid element. 
    
    // v is now {1, 3, 5, ?, ?, ?} - elements after new_end are unspecified // 1 3 5 2 4 6. 
    v.erase(new_end, v.end()); // v is now {1, 3, 5} 
    
    for (int n : v) std::cout << n << " "; // Output: 1 3 5
    // transform usage:-
    std::transform(input.begin(),input.end(),input.begin(),[](char&a)->char{return std::tolower(a);}); // 3rd input specify that transformation is done in input itself.we use transform since it allow us to save result on any other string and explicitly says we are doing range based logic
    std::optional<std::string> var = empl.get_manager();
    if(var.has_value()){
        std::cout<<*var<<std::endl; // * val gives value not val( it is wrapped in std:::optional) 
        
}
