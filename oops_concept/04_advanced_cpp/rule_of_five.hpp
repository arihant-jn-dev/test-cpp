#ifndef RULE_OF_FIVE_HPP
#define RULE_OF_FIVE_HPP

#include <iostream>
#include <utility>

/**
 * ===============================================
 * RULE OF FIVE - MANUAL MEMORY MANAGEMENT
 * ===============================================
 *
 * Moved here from 01_oop_pillars/class_object.hpp. LLD code stores data in
 * std::string, std::vector or smart pointers, so it never needs to write
 * these five special members by hand. Useful for C++ quiz questions.
 *
 * Q: What is the Rule of Three/Five/Zero?
 * A: Rule of Three: If you define destructor, copy constructor, or copy assignment,
 *    define all three.
 *    Rule of Five: Add move constructor and move assignment (C++11)
 *    Rule of Zero: Use smart pointers and RAII to avoid manual resource management
 */

namespace AdvancedCpp {

/**
 * Constructor Types Demonstration
 */
class ConstructorDemo {
private:
    int* data;
    size_t size;

public:
    // 1. Default Constructor
    ConstructorDemo() : data(nullptr), size(0) {
        std::cout << "Default constructor\n";
    }
    
    // 2. Parameterized Constructor
    ConstructorDemo(size_t s) : size(s) {
        data = new int[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = static_cast<int>(i);
        }
        std::cout << "Parameterized constructor (size: " << size << ")\n";
    }
    
    // 3. Copy Constructor (Deep Copy)
    ConstructorDemo(const ConstructorDemo& other) : size(other.size) {
        if (other.data) {
            data = new int[size];
            for (size_t i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        } else {
            data = nullptr;
        }
        std::cout << "Copy constructor (deep copy)\n";
    }
    
    // 4. Move Constructor
    ConstructorDemo(ConstructorDemo&& other) noexcept 
        : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
        std::cout << "Move constructor\n";
    }
    
    // 5. Conversion Constructor
    ConstructorDemo(int value) : size(1) {
        data = new int[1];
        data[0] = value;
        std::cout << "Conversion constructor (from int: " << value << ")\n";
    }
    
    // Destructor
    ~ConstructorDemo() {
        delete[] data;
        std::cout << "Destructor called\n";
    }
    
    // Assignment operators
    ConstructorDemo& operator=(const ConstructorDemo& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            if (other.data) {
                data = new int[size];
                for (size_t i = 0; i < size; ++i) {
                    data[i] = other.data[i];
                }
            } else {
                data = nullptr;
            }
        }
        std::cout << "Copy assignment\n";
        return *this;
    }
    
    ConstructorDemo& operator=(ConstructorDemo&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
        }
        std::cout << "Move assignment\n";
        return *this;
    }
    
    void display() const {
        std::cout << "Size: " << size << ", Data: ";
        if (data) {
            for (size_t i = 0; i < size; ++i) {
                std::cout << data[i] << " ";
            }
        } else {
            std::cout << "nullptr";
        }
        std::cout << "\n";
    }
};

} // namespace AdvancedCpp

// ======================= DEMONSTRATION FUNCTION =======================
inline void demonstrateRuleOfFive() {
    std::cout << "\n===== RULE OF FIVE DEMO =====\n" << std::endl;

    std::cout << "1. Constructors:" << std::endl;
    AdvancedCpp::ConstructorDemo demo1;                      // Default
    AdvancedCpp::ConstructorDemo demo2(size_t(5));           // Parameterized (size)
    AdvancedCpp::ConstructorDemo demo3(demo2);               // Copy (deep copy)
    AdvancedCpp::ConstructorDemo demo4 = std::move(demo3);   // Move
    AdvancedCpp::ConstructorDemo demo5(42);                  // Conversion (from int)

    demo1.display();
    demo2.display();
    demo3.display();  // Moved-from: empty
    demo4.display();
    demo5.display();

    std::cout << "\n2. Assignment Operators:" << std::endl;
    demo1 = demo2;               // Copy assignment
    demo5 = std::move(demo4);    // Move assignment
    demo1.display();
    demo5.display();
}

#endif // RULE_OF_FIVE_HPP
