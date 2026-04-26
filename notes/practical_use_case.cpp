
// stoi with &pos
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::string input = "10 25 300 45abc";
    std::vector<int> numbers;
    size_t pos = 0;

    while (pos < input.length()) {
        // Skip whitespace
        while (pos < input.length() && std::isspace(input[pos])) {
            ++pos;
        }

        if (pos >= input.length()) break;

        try {
            int num = std::stoi(input, &pos); // gives first non number char. 
            numbers.push_back(num);
        }
        catch (...) {
            std::cout << "Invalid number at position " << pos << '\n';
            break;
        }
    }

    for (int n : numbers) {
        std::cout << n << " ";   // Output: 10 25 300 45
    }
}
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  // universal forwarding, allows both l and r and allow mutation:-
  #include <iostream>
#include <string>

int main() {
    auto lambda = [](auto&& arg) {
        std::cout << "Value: " << arg << "\n";

        // Check if it's lvalue or rvalue reference
        if constexpr (std::is_lvalue_reference_v<decltype(arg)>) {
            std::cout << "  → This is an lvalue reference\n";
        } else {
            std::cout << "  → This is an rvalue reference\n";
        }
    };

    int x = 42;
    std::string s = "Hello";

    lambda(x);           // lvalue → binds as int&
    lambda(100);         // rvalue → binds as int&&
    lambda(std::move(s)); // rvalue → binds as std::string&&

    return 0;
}
