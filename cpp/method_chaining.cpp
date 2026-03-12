#include <iostream>
#include <string>

class Car {
private:
    std::string brand;
    std::string color;
    int horsepower = 0;
    bool turbo = false;

public:
    // Constructor (not needed for chaining, but useful)
    Car() = default;

    // All setter-like methods return *this → enables chaining
    Car& setBrand(const std::string& b) {
        brand = b;
        return *this;           // ← the magic line
    }

    Car& setColor(const std::string& c) {
        color = c;
        return *this;
    }

    Car& setHorsepower(int hp) {
        horsepower = hp;
        return *this;
    }

    Car& enableTurbo() {
        turbo = true;
        return *this;
    }

    // A getter (usually does NOT return *this — breaks chain)
    void print() const {
        std::cout << "Car: " << brand
                  << ", Color: " << color
                  << ", HP: " << horsepower
                  << ", Turbo: " << (turbo ? "Yes" : "No")
                  << "\n";
    }
};

int main()
{
    // ------------------------------
    // Classic way (without chaining)
    // ------------------------------
    Car myCar1;
    myCar1.setBrand("BMW");
    myCar1.setColor("Black");
    myCar1.setHorsepower(530);
    myCar1.enableTurbo();
    myCar1.print();

    // ------------------------------
    // With method chaining (fluent style)
    // ------------------------------
    Car myCar2;
    myCar2
        .setBrand("Porsche")
        .setColor("Guards Red")
        .setHorsepower(640)
        .enableTurbo()
        .print();               // ← also works if print returned *this, but usually doesn't

    // Even nicer: create + configure in one expression
    Car myCar3;
    myCar3.setBrand("Tesla")
          .setColor("Pearl White")
          .setHorsepower(1020)
          .enableTurbo()
          .print();

    // Or even shorter (temporary object)
    Car()
        .setBrand("Audi")
        .setColor("Nardo Grey")
        .setHorsepower(630)
        .enableTurbo()
        .print();

    return 0;
}
