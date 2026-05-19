#pragma diag_suppress 20,77,70,18,65,135,147,757,311,144,169,8,79,260

// pass by value:-
void movePlayer(Player p) { 
    p.x += 10; // Only changes the LOCAL copy
}
// Called as:
Player p1(0);
movePlayer(p1); // p1.x is still 0. A full copy was made.


// pass by pointer:-
void renamePlayer(Player* p, std::string newName) {
    if (p != nullptr) {
        p->name = newName; // Changes the ORIGINAL object
    }
}
// Called as:
Player p1("Sugam");
renamePlayer(&p1, "Hi_Sugam"); // Pass the address using & or pass pointer name, in this case object is optional (you can pass nullptr)


// pass by reference 
void levelUp(Player& p) {
    p.level++; // Changes the ORIGINAL object
}
// Called as:
Player p1(1);
levelUp(p1); // p1.level is now 2. No '&' or '*' needed at call site, use when  must modify object.


// pass by const reference 
void displayInfo(const Player& p) {
    // p.level++; // ERROR: Cannot modify const
    std::cout << p.name << " Level: " << p.level;
}
// Called as:
Player p1("Sugam", 5);
displayInfo(p1);           // 1. Works with L-value (Variable)
displayInfo(Player("Bot",0)); // 2. Works with R-value (Temporary)


// pass by r value:-
void storePlayer(Player&& p) {
    Player internalStore = std::move(p); // "Steals" memory from the temporary
}
// Called as:
storePlayer(Player("Temp")); // Only works with temporaries (R-values)


// returning args:-
 int func(){
    retun val; // retun by value ( copy) 
 }
  int& func(){
    retun  val; // return reference to val, if val in stack(local) then it will be garbage, use static. 
  }
 int* func(){
    return some_ptr; // return  a new pointer where some_ptr was pointing to. , int* p = func();, p points to same as some_ptr, some_ptr is address
 }
 int* func(){
    return &val; // pass val address and retun  a pointer to it( if val lives in stac(local)  then the pointer will point to garbage), do static int val =10; retun &val, static make ssure it lives entire duration of program.  
 } // int* p = func()   , int*  means returning a pointer and  pointer  and address are same thing( in all cases).  int* p = address( func() retuns address)
 itn*& func(){
    retun some_ptr; // refrence to pointer was made, no new pointer created. int*& p = func() , p is same(reference) to some_ptr 
 }

// could also do:-
// obj.func()->setname("hii"), if pointer is to an object, same as User* usr = obj.findById("E123"); usr->setName("Hacker");

int x = 10;

// Case A: Pointer to const  (const data)
const int* p1 = &x;        // You cannot change *p1
*p1 = 20;   // ERROR

// Case B: Const pointer     (const pointer)
int* const p2 = &x;        // You cannot change p2 (where it points)
p2 = nullptr;  // ERROR

--------------------------------------------------------------------------------------------------------------------------------------------------------------
a->func(); -> internally does:-
(a.operator->()) -> func(); 
//When the compiler sees:
a->func();
//It always translates it into:
(a.operator->()) -> func()    //a.operator->() returns pointer( we overloaded), extra -> hardcoded by compiler act as normal -> 
(ptr)->func(); 
//translates to:-
(*ptr).func();
----------------------------------------------------------------------------------------------------------------------------------------------------------------
Parameter Type,                       Can Bind to Lvalue?,           Can Bind to Rvalue?,           Can Modify Original?,      Use Case
auto&& arg,                                 Yes                              Yes                          Yes              Perfect Forwarding
const auto& arg,                            Yes                               Yes                          No                 Read-only access
auto& arg,                                  Yes                                No                           Yes                 Only lvalues
myClass&& arg                               no                                 yes                            yes                  only r value
-------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include <iostream>
#include <string>

class MyClass {
public:
    std::string name;
    MyClass(std::string n) : name(std::move(n)) {}
};

void func1(MyClass&& arg) {          // ← Only rvalue reference
    std::cout << "func1 called with: " << arg.name << '\n';
    arg.name = "Modified inside func1";   // Can modify
}

void func2(auto&& arg) {             // ← Forwarding reference
    std::cout << "func2 called with: " << arg.name << '\n';
}

int main() {
    MyClass obj("Original");

    // func1(obj);           // ERROR! Cannot pass lvalue to MyClass&&

    func1(std::move(obj));   // OK - only rvalues allowed

    func2(obj);              // OK - auto&& accepts lvalue
    func2(MyClass("Temp"));  // OK - auto&& accepts rvalue

    return 0;
}
-----------------------------------------------------------------------------------------------------------------------------------------------------
The Two-Step Hand-Off( once to get it into the constructor, and once to get it from the constructor's parameter into the class member.)
Step 1: The Call Site (The "Giveaway")

You must use std::move when passing the object to the constructor. This converts your variable into an rvalue. 

std::vector<Grade> myGrades = { {"Math", 95} };
// HAND-OFF #1: 'myGrades' is moved into the constructor parameter 'g'
Student st("Alice", std::move(myGrades)); 

Step 2: The Constructor Definition (The "Takeover")

Inside the constructor, the parameter g is a local variable. Even though it was moved into the function, it is still an "lvalue" (it has a name). To move it from the parameter into your private member _list, you must move it again.
// HAND-OFF #2: Parameter 'g' is moved into member variable '_list'
Student::Student(std::string s, std::vector<Grade> g) : _name(std::move(s)),_list(std::move(g)){}






// constructors called step by step:-

  grades.push_back(Grade("science", 70));
  1) calls :-
   Grade(std::string sub, double marks) // normal constructor defined and then: Grade("science",70)--> science is string literal, std::string calls it's paramterized constructor.
    inside this normal constructor : subject(std::move(sub)), marks(marks) {} //  subject is string, marks is bool             
                                        ---- >std::move constructor called by subject(std::string subject = std::move(sub)),not moves assignment since initializer list used not traditional.               
   -> we have Grade&& rvalue here from step1

  2)push_back() calls:-
   vector invokes rvalue overlaod for push_back(since rvalue is passed): void push_back(Grade&& value);        // push_back overload
                                                                                           ---> value is a rvalue reference pointing to temp Grade from step1. 

  3) vector allocate memory and uses code:-
  void* memory = /* already allocated by vector */;
  new (memory) Grade(std::move(value)); // value refers to step1 Grade, consturct at exact memory 

  4) When the compiler sees new (memory) Grade(std::move(value)), it looks at all available constructors of Grade and picks the best match:-
    Grade(std::string sub, double marks);   // candidate 1
    Grade(const Grade& g);                  // candidate 2 — copy constructor
    Grade(Grade&& g);                       // candidate 3 — move constructo
    check argumet: std::move(value) generates non const r value , candidate 3 best match, used it to construct object(move constructor)

    // all containers try do above 
    --------------------------------------------------------------------------------------------------------------------------
    #include <new> // Required for placement new

char* buffer = new char[sizeof(MyClass)]; // Pre-allocated memory
MyClass* obj = new (buffer) MyClass();    // Placement new to exactly preallocated memory. 
// we can overlaod new too. 


------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //basic pointer logic:-
    Stack Memory
─────────────────────────────────────
x  at 0x1000 : 42     int x =42;
p  at 0x2000 : 0x1000 int* p =&x;
q  at 0x3000 : 0x1000 int* q = p;
─────────────────────────────────────

| Expression | Meaning                     | Value    |
| ---------- | --------------------------- | -------- |
| `p`        | Address stored in pointer   | `0x1000` |
| `*p`       | Object at that address      | `42`     |
| `&p`       | Address of pointer variable | `0x2000` |

