// C++ program for demonstrating the use of
// move constructor
#include <iostream>
#include <vector>
using namespace std;

// Base Class
class Base {
private:
    // Declare the raw pointer as
    // the data member of class
    int* data;

public:
    // Constructor( normal when object created)
    Base(int d)
    {
        // Declare object in the heap
        data = new int;
        *data = d;
        cout << "Constructor is called for " << d << endl;
    };

    // Copy Constructor, call normal constructo too then does it's own work. 
    Base(const Base& source)
        : Base{ *source.data }
    {

        // Copying the data by making
        // deep copy
        cout << "Copy Constructor is called -"
             << "Deep copy for " << *source.data << endl;
    }

    // Base Constructor
    Base(Base&& source)
        : data{ source.data }
    {

        cout << "move Constructor for " << *source.data
             << endl;
        source.data = nullptr;
    }

    // Destructor
    ~Base()
    {
        if (data != nullptr)

            // If pointer is not pointing
            // to nullptr
            cout << "Destructor is called for " << *data
                 << endl;
        else

            // If pointer is pointing
            // to nullptr
            cout << "Destructor is called"
                 << " for nullptr " << endl;

        // Free up the memory assigned to
        // The data member of the object
        delete data;
    }
};

// Driver Code
int main()
{
    // Vector of Base Class
    vector<Base> vec;
    Base b(10);
    //vec.push_back(b);
    vec.push_back(std::move(b)); // labbels b ar r value, push_back see's this and calls move constructor. 
    // Inserting Object of Base Class
    //vec.emplace_back((Base{ 10 })); // Base{10} creates tmeporary object, calls normal constructor of move, 
    // since it's temporary and vector needs to store permamnanetly, it calls move constructor of this class. 
                       
    
   // vec.push_back(Base{ 20 });
    return 0;
} //noexcep constructor: during resizing, makes vecotor use move constructor. A(A&& obj) noexcept{}
