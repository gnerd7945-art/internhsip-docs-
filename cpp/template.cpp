#include <iostream>
#include <cstring>

// 1. Generic Function Template
template <typename T>
T myMax(T a, T b) {
    return (a > b) ? a : b;
}

// 2. Template Specialization for const char* (C-strings)
template <>
const char* myMax<const char*>(const char* a, const char* b) {
    return (strcmp(a, b) > 0) ? a : b;
}

int main() {
    // Uses the generic template
    std::cout << myMax(10, 20) << "\n";         // Output: 20
    std::cout << myMax(3.14, 2.71) << "\n";     // Output: 3.14

    // Uses the specialized template
    const char* str1 = "apple";
    const char* str2 = "banana";
    std::cout << myMax(str1, str2) << "\n";     // Output: banana
}

#include <iostream>

// 1. Generic Class Template
template <typename T>
class Printer {
public:
    void print(T value) {
        std::cout << "Generic value: " << value << "\n";
    }
};

// 2. Class Specialization for bool
template <>
class Printer<bool> {
public:
    void print(bool value) {
        std::cout << "Bool value: " << (value ? "true" : "false") << "\n";
    }
};

int main() {
    Printer<int> intPrinter;
    intPrinter.print(42);         // Output: Generic value: 42

    Printer<bool> boolPrinter;
    boolPrinter.print(true);       // Output: Bool value: true
}
