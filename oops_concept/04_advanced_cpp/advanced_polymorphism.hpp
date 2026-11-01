#ifndef ADVANCED_POLYMORPHISM_HPP
#define ADVANCED_POLYMORPHISM_HPP

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <typeinfo>

#include "../01_oop_pillars/polymorphism.hpp"

/**
 * ===============================================
 * ADVANCED POLYMORPHISM
 * ===============================================
 *
 * Moved here from 01_oop_pillars/polymorphism.hpp: operator overloading,
 * templates, functors, dynamic_cast/typeid and a vtable demo. Good to know for
 * C++ quiz questions; not needed to write LLD code.
 */

namespace AdvancedCpp {

/**
 * Operator Overloading - Compile-time polymorphism
 */
class Complex {
private:
    double real, imaginary;

public:
    Complex(double r = 0, double i = 0) : real(r), imaginary(i) {}
    
    // Operator overloading
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imaginary + other.imaginary);
    }
    
    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imaginary - other.imaginary);
    }
    
    Complex operator*(const Complex& other) const {
        return Complex(real * other.real - imaginary * other.imaginary,
                      real * other.imaginary + imaginary * other.real);
    }
    
    bool operator==(const Complex& other) const {
        return real == other.real && imaginary == other.imaginary;
    }
    
    // Assignment operator
    Complex& operator=(const Complex& other) {
        if (this != &other) {
            real = other.real;
            imaginary = other.imaginary;
        }
        return *this;
    }
    
    // Stream operators
    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << c.real;
        if (c.imaginary >= 0) os << "+";
        os << c.imaginary << "i";
        return os;
    }
    
    friend std::istream& operator>>(std::istream& is, Complex& c) {
        is >> c.real >> c.imaginary;
        return is;
    }
    
    // Getters
    double getReal() const { return real; }
    double getImaginary() const { return imaginary; }
};

/**
 * Function Template - one definition works for int, double, ...
 * (moved from Calculator in polymorphism.hpp)
 */
template<typename T>
T multiply(T a, T b) {
    return a * b;
}

/**
 * dynamic_cast - find out the real type behind a base class pointer
 */
void processShapePointer(const BasicConcepts::Shape* shape) {
    if (shape) {
        std::cout << "\n--- Processing Shape Pointer ---" << std::endl;
        shape->displayInfo();
        shape->draw();
        
        // Demonstrate dynamic_cast
        if (const BasicConcepts::Circle* circle = dynamic_cast<const BasicConcepts::Circle*>(shape)) {
            std::cout << "This is a circle with radius: " << circle->getRadius() << std::endl;
        } else if (const BasicConcepts::Rectangle* rect = dynamic_cast<const BasicConcepts::Rectangle*>(shape)) {
            std::cout << "This is a rectangle " << rect->getWidth() 
                      << "x" << rect->getHeight() << std::endl;
            if (rect->isSquare()) {
                std::cout << "It's actually a square!" << std::endl;
            }
        } else if (const BasicConcepts::Triangle* tri = dynamic_cast<const BasicConcepts::Triangle*>(shape)) {
            std::cout << "This is a " << tri->getTriangleType() << " triangle" << std::endl;
        }
    }
}

/**
 * Advanced Polymorphism - Function Objects (Functors)
 */
class Functor {
private:
    int multiplier;

public:
    Functor(int m) : multiplier(m) {}
    
    // Overload function call operator
    int operator()(int x) const {
        return x * multiplier;
    }
    
    // Overload for different types
    double operator()(double x) const {
        return x * multiplier;
    }
};

/**
 * Template-based polymorphism
 */
template<typename T>
class Container {
private:
    std::vector<T> data;

public:
    void add(const T& item) {
        data.push_back(item);
    }
    
    T get(size_t index) const {
        if (index < data.size()) {
            return data[index];
        }
        throw std::out_of_range("Index out of range");
    }
    
    size_t size() const {
        return data.size();
    }
    
    // Template method
    template<typename U>
    void addConverted(const U& item) {
        data.push_back(static_cast<T>(item));
    }
    
    // Function template for operations
    template<typename Func>
    void applyFunction(Func f) {
        for (auto& item : data) {
            item = f(item);
        }
    }
};

/**
 * Virtual Function Table Demonstration
 */
class VTableDemo {
public:
    virtual void func1() { std::cout << "VTableDemo::func1" << std::endl; }
    virtual void func2() { std::cout << "VTableDemo::func2" << std::endl; }
    virtual void func3() { std::cout << "VTableDemo::func3" << std::endl; }
    
    void nonVirtualFunc() { std::cout << "VTableDemo::nonVirtualFunc" << std::endl; }
    
    virtual ~VTableDemo() = default;
};

class DerivedVTable : public VTableDemo {
public:
    void func1() override { std::cout << "DerivedVTable::func1" << std::endl; }
    // func2 not overridden - uses base version
    void func3() override { std::cout << "DerivedVTable::func3" << std::endl; }
    
    void derivedSpecific() { std::cout << "DerivedVTable::derivedSpecific" << std::endl; }
};

} // namespace AdvancedCpp

/**
 * ===============================================
 * INTERVIEW QUESTIONS AND ANSWERS
 * ===============================================
 *
 * Q1: When to use dynamic_cast?
 * A1: - Safe downcasting in inheritance hierarchy
 *     - Returns nullptr if cast fails (for pointers)
 *     - Throws std::bad_cast if cast fails (for references)
 *     - Requires polymorphic classes (with virtual functions)
 * 
 */

// ======================= DEMONSTRATION FUNCTION =======================
inline void demonstrateAdvancedPolymorphism() {
    std::cout << "\n===== ADVANCED POLYMORPHISM DEMO =====\n" << std::endl;

    std::cout << "1. Operator Overloading (Complex):" << std::endl;
    AdvancedCpp::Complex c1(3, 4);
    AdvancedCpp::Complex c2(1, -2);
    std::cout << "c1 + c2 = " << (c1 + c2) << std::endl;
    std::cout << "c1 * c2 = " << (c1 * c2) << std::endl;
    std::cout << "c1 == c2: " << (c1 == c2 ? "true" : "false") << std::endl;

    std::cout << "\n2. Function Template:" << std::endl;
    std::cout << "multiply(3, 4) = " << AdvancedCpp::multiply(3, 4) << std::endl;
    std::cout << "multiply(2.5, 2.0) = " << AdvancedCpp::multiply(2.5, 2.0) << std::endl;

    std::cout << "\n3. Class Template (Container):" << std::endl;
    AdvancedCpp::Container<int> intContainer;
    intContainer.add(10);
    intContainer.add(20);
    intContainer.add(30);
    intContainer.applyFunction([](int x) { return x * 2; });
    std::cout << "First element after doubling: " << intContainer.get(0) << std::endl;

    AdvancedCpp::Container<std::string> stringContainer;
    stringContainer.add("Hello");
    stringContainer.add("World");
    std::cout << "String container size: " << stringContainer.size() << std::endl;

    std::cout << "\n4. Functor (overloaded operator()):" << std::endl;
    AdvancedCpp::Functor triple(3);
    std::cout << "triple(5) = " << triple(5) << std::endl;
    std::cout << "triple(1.5) = " << triple(1.5) << std::endl;

    std::cout << "\n5. dynamic_cast and typeid:" << std::endl;
    BasicConcepts::Circle circle("Red", 5.0);
    BasicConcepts::Rectangle square("Blue", 4.0, 4.0);
    AdvancedCpp::processShapePointer(&circle);
    AdvancedCpp::processShapePointer(&square);
    std::cout << "typeid(circle).name(): " << typeid(circle).name() << std::endl;

    std::cout << "\n6. VTable (overridden vs inherited virtual functions):" << std::endl;
    AdvancedCpp::DerivedVTable derived;
    AdvancedCpp::VTableDemo* base = &derived;
    base->func1();
    base->func2();
    base->func3();
    base->nonVirtualFunc();
}

#endif // ADVANCED_POLYMORPHISM_HPP
