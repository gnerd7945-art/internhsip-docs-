// project having mini version of current architecture. stateful functors, sateful lambda, std::for_each, callback registry/ virtual inheritance/ dynamic injection. Smart pointeras and weak pointers. 

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
    std::isdigit(ch)// include <cctype> 
    std::to_string(some_int) // convert ot string
    std::stoi(some string) // convert to int 
    std::all_of(vec.begin(),vec.end(),::logic) // returns true if all elements satisfy 3rd arg logic. 3rg could be lambda too , lambda should return  bool 
    std:: remove_if(vec.begin(),vec.end().::logic) // reorders, does not chamge container size, just shift relevant ones to left, need to pair with erase. uses bool 
    std::find_if(vec.begin(),vec.end().::logic)// find and return only if logic meets( returns forst occurance), lambda return bool 
    std::find(vec.begin(),vec.end(),value)//  returns iterator to first occurance. or end() 
    std::transform(vec.begin(), vec.end(),another_vec.begin(),[](int& a)->int{re turn logic});// change range based loop with some logic or to a different container. It does element wise transfomration(lambda takes one input)
    std::optional<data type> var; 
    std::any_of(vec.begin(),vec.end(),[](int& i)->int{return i%2==0;}) // return bool , lambda returns bool or any value whihc converts to bool: eg: return x: int-> bool(0=f,else t) 
    std::isspace(string/ch); // check if char or string is space. 
    std::getline(read_from_string/ifstream_obj, dump_to_string);  // std::getline(std::cin>>std::ws,line);
    std::reverse(vec.begin(),vec.end()) // works for vector,queue,list,array,std::string
    std::alnum(ch) // check if alnum char , std::tolower(ch) // conver to lower 
int main() {
    std::vector<int> v = {1, 2, 3, 4, 5, 6};
    // Remove even numbers
    auto new_end = std::remove_if(v.begin(), v.end(), [](int n) { return n % 2 == 0; }); // new_end is next to last valid element. 
    
    // v is now {1, 3, 5, ?, ?, ?} - elements after new_end are unspecified // 1 3 5 2 4 6. 
    v.erase(new_end, v.end()); // v is now {1, 3, 5} 
    
    for (int n : v) std::cout << n << " "; // Output: 1 3 5
    // transform usage:-
    std::transform(input.begin(),input.end(),input.begin(),[](char&a)->char{return std::tolower(a);}); // 3rd input specify that transformation is done in input itself.we use transform since it allow us to save result on any other string and explicitly says we are doing range based logic
    std::transform(input.begin(),input.end(),input2.beign(),new_vec.begin() or std::back_inserter(new_vec),[](int a, int b)->int{return a+b;});  //new_vec.begin() if adequate size already allocated since std::trnasform does not rezise automatically for the container. DONT USE TRANSFORM FOR SORTING.
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
    it is a namepsace and not a class
    it is used to create/delete , iterate folder and files 
    namespace fs= std::filesystem;  shorting the namespace by creating yet another namespace 
    for(const auto entry&: fs::directory_iterator(parent_folder) // only iterate what's inside this folder in 1 level dont go inside  subfolders
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
        entry.is_regular_file()// txt,json,mp4, not: directory,symlink,sockets 
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
        json["name'.get<string>(); // gets value and convert
        

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
json.back() // gets last element  in json, back().is_object()// chekc if it is object()
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// iterators and vector:-
 std::vector<int>:: iterator it = vec.begin(); auto itn= vec.begin() +5; // random jumps work with vecotr, deque, array
    std::distance(it,itn) // return elements btw 2 iterators(5)
  std::vector<int> :: iterator  it = vec.erase(vec.begin()+2); return iterator next to erased element. 

//common vector usage:-
1) vector<bool> used(n,false); // initialize n vector with false value. 

2) for(const auto&[k,v] :ma){
    int key =k;
    std::vector<int> vec =v;}
3) std::vector<std::pair<int,int>> vp;
    vp.push_back({1,2});
    vp.emplace_back(1,2);

-------------------------------------------------------------------------------------------------------------------------------------------------------------------
 // for map and set:-
    std::advance(it, 3) // move it 3 steps forward. 
auto next_it = std::next(it,3)// return iterator  3 step forward, does not change it. 
    
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// string 
std::string name= 'sugam', prefix = sug 
name.starts_with(prefix);// t/f 
name.substr(1,3) //uga, start at 1 position and take 3 char   // s.substr(start,length) 
const char* c = "hi , you are hi "; 
c.rfind(c, index); // 13 , index : start searching backward from this index. 
std::string id = "bye"
name.replace(2,3,"hi" + id); // suhibye
// in substr() and replace() from starting index we start operating
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//lambda:-
 some_function([](int x )->{print(x)}) // we pass lambda to it. 
some_function(std::function<void(int)> func){
func(10);// executes lambda () applied

}
[](){}()-> lambda executed on the spot 
// more eg:-

#include <iostream>
#include <functional>
class EventChannel {
    std::function<void(int)> handler;

public:
    void setHandler(std::function<void(int)> h) {
        handler = h;  // store the lambda // store the lambda here 
    }✅ Case 2: Lambda is passed somewhere (still NOT called here)

    void simulateEvent() {
        if (handler) {
            handler(42);  // <-- lambda called here, () is overloaded in lambda class 
        }
    }
};
int main() {
    EventChannel channel;

    channel.setHandler([](int value) {
        std::cout << "Event received: " << value << "\n"; //  pass the lambda to this function 
    });

    channel.simulateEvent();  // triggers the lambda in some other function
}
// using mutable to edit capture by value, else defualt they are const. 
[x]() mutable{++x;}
// unique_ptr cannot be copied inside lambda, must use move:-
#include <iostream>
#include <memory>

int main() {
    auto up = std::make_unique<int>(42);

    // Move unique_ptr into lambda (C++14+)
    auto lambda = [ptr = std::move(up)]() mutable {   // mutable is often needed
        if (ptr) {
            *ptr = 100;
            std::cout << "Inside lambda: " << *ptr << '\n';
            ptr.reset();        // You can reset or modify
        }
    };

    lambda();

    std::cout << "After lambda: " << (up ? "still alive" : "moved away") << '\n';
}
// statefull lambda: basically same as above( capture value and use mutable to add something to it) -> intenrally converts to stateful functors( () overloaded, and also have some attribute where we accumulate argument)
int total = 0;

// The [total] captures the state, 'mutable' allows the lambda to modify it
auto accLambda = [total](int value) mutable {
    total += value;
    return total;
};

std::cout << accLambda(5)  << "\n"; // Outputs: 5
std::cout << accLambda(10) << "\n"; // Outputs: 15
//  stateful functor example:-
class Mul{
public: 
    int val;
    Mul(int num):val(num){}
    void operator()(int element){ //  passed by value 
     val*=element;
    }
 };
int main(){
Mul multiplier(10);
multiplier(3);
std::vector<int> v={1,2,3,4,5}
// for_each returns function/ functor passed to it. 
Mul m = std::for_each(v.begin(),v.end(),Mul(11)); -> Mul(11) creates temp obj and for_each calls obj(v_element) -> () overload gets triggered. , if normal function lambda was there as  3rd arg then func(v_element).
// same Mul(11) object is paased on each iteration. 

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // varinats:-

    #include<variant>
#include <iostream>
#include<string>

int main()
{
    std::variant<int,std::string> v;
    v =10;
   // std::cout<<v<<std::endl; does not work 
    std::visit([](auto&& arg)->void{std::cout<<arg<<std::endl;},v); // v passed to arg 
    v= "hi";
    if(int* i = std::get_if<int>(&v)){
        std::cout<<*i<<std::endl;
    }
    else if(std::string* s = std::get_if<std::string>(&v)){ // return nullptr if not matched, if cond.  converts it to false 
        
        std::cout<<*s<<std::endl;
    }
    v = "bye";
   std::string s =  std::move(std::get<std::string>(v));
   std::cout<<s<<std::endl;
   
    
    return 0;

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
// renoving const_cast,adding const to pointer,:-
    1) adapting for legvacy_api( removing const from pointer) :-
    void legacy_c_print(char* str); // Does not modify str, but lacks 'const'

void safe_cpp_print(const std::string& msg) {
    // legacy_c_print(msg.c_str()); // Compile error: const char* cannot convert to char*
    
    // Correct usage: Temporarily strip const safety because we trust the C API
    legacy_c_print(const_cast<char*>(msg.c_str())); 
}
2) adding const in pointer:-
    const char* getter(char* s) const{
    return s[5];}
const char* constgetter(char* s) const{
return const_cast<const char*>(s[5]); }
3) problomatic code:-
    // SAFE: Original object 'x' is mutable
int x = 42;
const int& ref = x;
const_cast<int&>(ref) = 100; // Safe. 'x' is now 100. removes const ref 

// UNDEFINED BEHAVIOR: Original object 'y' is truly read-only
const int y = 42;
const int& ref_y = y;
const_cast<int&>(ref_y) = 100; // CRASH or unexpected behavior! The compiler optimized 'y' into read-only memory.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //heap and priority queue
    #include<algorithm>
    #include<vector>
    #include<queue>
    
    priority_queue<int>maxi;
maxi.push(x);
maxi.top();
maxi.pop();
maxi.empty();
2) min heap pq:-
    priority_queue<int,std::vector<int>,std::greater<int>> pq; -> call same above func
3) vector and heap:-
    std::vector<int>  vec{4,7,2,5,9,2,5,2};
    std::make_heap(vec.begin(),vec.end());
    vec.push_back(40);
    std::push_heap(vec.begin(),vec.end());
    std::cout<<vec.front()<<std::endl;
    std::pop_heap(vec.begin(),vec.end());
    vec.pop_back() // not pop as we want last element of vector ( heap switched it with front). 
4) vectyor and min heap:-
        make_heap(heap.begin(), heap.end(), greater<int>());
        push_heap(heap.begin(), heap.end(), greater<int>());
        pop_heap(heap.begin(), heap.end(), greater<int>());
        .. rest same
    


--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// rules:-
1) avoid using raw pointer to access value/address of containers. 
2) variable = (condition) ? value_if_true : value_if_false; // not == btw variable and condition 
3)        int slow=0,fast =0;
4) if in param you do: const class_name& obj. Then inside that function(which uses that params)  you can only call const function  of that obj, func() const allow func() to be called if obj const 
5) almost always if return type  is private reference, make it const in function declaration or make it const if function is const, return by value, then const not needed. 
6) unordered_map can't be sorted.Convert it to vector of pairs and sort them, unordered_map<char,int> map{{'a',1},{'b',2}};
7) adding space:   std::cout<<longest<<" " ;  normal, not new line: std::cout << "Hello ";
8)     if (!(ss >> ch)) break; needs checking else ss keep last known value when stream ends. 
9) no ; in {} for constructor, also attribute order in class should be followed when filling in constructor , when overriding a function: returntype func_name(arg) override{};
10) std::sort() returns bool, only care about arrangement and not what you are returning: return p1.second> p2.seocnd and not if() return p1.first;
11) cout -> directly display on screen, ostringstream -> build string first, then use it






