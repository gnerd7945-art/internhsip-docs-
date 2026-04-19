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
    std::isspace(string/ch); // check if char or string is space. 
    std::getline(read_from_string/ifstream_obj, dump_to_string);

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5, 6};
    // Remove even numbers
    auto new_end = std::remove_if(v.begin(), v.end(), [](int n) { return n % 2 == 0; }); // new_end is next to last valid element. 
    
    // v is now {1, 3, 5, ?, ?, ?} - elements after new_end are unspecified // 1 3 5 2 4 6. 
    v.erase(new_end, v.end()); // v is now {1, 3, 5} 
    
    for (int n : v) std::cout << n << " "; // Output: 1 3 5
    // transform usage:-
    std::transform(input.begin(),input.end(),input.begin(),[](char&a)->char{return std::tolower(a);}); // 3rd input specify that transformation is done in input itself.we use transform since it allow us to save result on any other string and explicitly says we are doing range based logic
    // optional use case:-
    std::optional<std::string> var = empl.get_manager();
    if(var.has_value()){
        std::cout<<*var<<std::endl; // * val gives value not val( it is wrapped in std:::optional)
------------------------------------------------------------------------------------------------------------------------------------------------------------------
   //fstream:-
    it is used to open, read and write to files. 
    // fstream obj > getline> ss, then dump to variable 
    std::ifstream file("some_folder_path"); // creates file object and immediately attempts to open file. 
    std::string line;
    
    while(std::getline(file, line)){
        std::istringstream iss(line);
        if(iss>>key>>value){ // 1st word become key and second becomes value
            //condition 
        }     
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    //std::filesystem:-
    it is used to create/delete , iterate folder and files 
    namespace fs= std::filesystem;
    for(const auto entry& : fs::recusive_directory_iterator(parent_folder){// iterate over sub folder, .path() gives object and .string() converts to string, find() is string method
    if(entry.path().string().find(some_name) != std::string::npos)){
        const auto toName{entry.parent_path() / (camName + streamStr)}; // '/' is overloaded to concat path. 
        auto errorCode{std::error_code{}};
        fs::rename(entry.path().string(), toName, errorCode); // errorcode do not let crash if unsucessfull, can skip 
        fs::exist(toName);// check if sucess

        fs::create_directories("logs/camera_1/errors");//  Unlike "create_directory"  which only makes one folder, this makes the entire chain of folders at once.

        fs::remove_all("/tmp/comm/old_fifos"); This is the C++ equivalent of rm -rf. It deletes a folder and everything inside it instantly.
    }
    }; 
 -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------   
// chrono:-
const auto now = std::chrono::system_clock::now() // advance  math time ( huge integer) representing tick from jan1, 1970
std::time_t now_time = std::chrono::system_clock::to_time_t(now) // represent seconds ( looses some micro/nano seconds) from 1970 to now. std::time_t is middleperson which is required to talk with other tools, as they dont  understands chrono.  std::chrono::system_clock::to_time_t is required as it acknoweldges that you are okay with loosing nano seconds of time 
std::tm t{} // a strcut which holds time in month,year,day var 
add value to struct:-
#if defined(_WIN32)
    gmtime_s(&t, &nowTime); // Windows, use localtime_r/s for local , r and s makes it thread_safe. 
#else
    gmtime_r(&t, &timeStruct); // Linux/Mac
#endif
std::ostringstream ostream; 
ostream<< std::put_time(&t, "format"); // put time converts struct data to date format
return ostream.str() // convert obj mem variable to string 
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // function pointers:-
    void hello(){
    std::cout<<"hello<<std::endl;
    }
     void callback(void(*passed_func)()){
         *passed_func(); // passed_func() would also have worked, automatic dereference.
     }
    -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// JSON in CPP:-
        #include <nlohmann/json.hpp>
        using json = nlohmann::json;
        json::parse(string) // convert string to json obj

        json["key] = another_json.value("another_key",0) /// assign value at another_key in another_json, if not found then return 0 to beassigned to key. 
        json.contains("key") // return t/f 

        json data = { {"name", "Alice"}, {"stats", {10, 20, 30}} };
        fstream fstream_obj("path to some file);
        json some_json{};
        fstream_obj >> json // dump file content to json 
        

    try {
        // Successful access
        std::string name = data.at("name"); 
        int first_stat = data.at("stats").at(0);
        
        std::cout << name << " has stat: " << first_stat << "\n";

        // This will FAIL and throw an exception because "age" doesn't exist
        int age = data.at("age"); 

    } catch (json::out_of_range& e) {
        // Catching the error if the key is missing or index is out of bounds
        std::cerr << "Error: " << e.what() << "\n";
    }
}
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// iterators:-
 std::vector<int>:: iterator it = vec.begin(); auto itn= vec.begin() +5;
    std::distance(it,itn) // return elements btw 2 iterators(5) 
    std::advance(it, 3) // move it 3 steps forward. 


-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// rules:-
1) avoid using raw pointer to access value/address of containers. 
2) variable = (condition) ? value_if_true : value_if_false; // not == btw variable and condition 





