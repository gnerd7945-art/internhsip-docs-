// Since mem on heap is not cleared until delete is called ( which calls there destrcutor first before freeing mem)  we use  smart pointers to avoid memory leak which could happen via early returns or throw, 
or maybe simply forgetting to use delete.  the destructor is not called automatically when a pointer goes out of scope when mem is allocated on heap. We need to amage it via delete or smart pointers. 

// smart pointers are allocated on stack and when they go out of scope, they call there destructor which have delete in there code to remove memory of object.

// 1) to create unique pointer, instead of typing syntax of unique pointer, use make_unique since it's syntax is simpler and more meory safe 
// order of compilation is not fixed in compiler it might first allocate memory, then call fucntion which throws exception( return) thus unique pointer not able to wrap around that memory and that memory leaked. 
// although mem allocation is with unique pointer, order is not always l-r: process_data(std::unique_ptr<Document>(new Document()), get_priority_from_server());
// here new Document ahppended first, get_priority_from_server() gets called ( failed, thus return) cannot execute unique_ptr argument. 
// make unique is a single function call. it allocates memory and immediately calls unique pointer. 
// example intialization:     std::unique_ptr<Player> p2 = std::make_unique<Player>("Bob", 200); , std::unique_ptr<Player> p3(new Player("Charlie", 300));
//  int * p = new int(10); // single element 

