#include <iostream>
#include <iomanip>
#include "calculator.hpp"

/**
 * Main application file demonstrating the Calculator class
 * This shows how multiple source files are linked together using CMake
 */

void printHeader(const std::string& title) {
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "  " << title << std::endl;
    std::cout << std::string(50, '=') << std::endl;
}

void demonstrateBasicOperations() {
    printHeader("BASIC ARITHMETIC OPERATIONS");
    
    double a = 15.5, b = 4.2;
    
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Numbers: a = " << a << ", b = " << b << std::endl;
    std::cout << "Addition: " << a << " + " << b << " = " << Calculator::add(a, b) << std::endl;
    std::cout << "Subtraction: " << a << " - " << b << " = " << Calculator::subtract(a, b) << std::endl;
    std::cout << "Multiplication: " << a << " × " << b << " = " << Calculator::multiply(a, b) << std::endl;
    std::cout << "Division: " << a << " ÷ " << b << " = " << Calculator::divide(a, b) << std::endl;
}

void demonstrateAdvancedOperations() {
    printHeader("ADVANCED OPERATIONS");
    
    std::cout << "Power: 2^10 = " << Calculator::power(2, 10) << std::endl;
    std::cout << "Power: 3.5^2 = " << Calculator::power(3.5, 2) << std::endl;
    
    std::cout << "\nFactorials:" << std::endl;
    for (int i = 0; i <= 8; ++i) {
        std::cout << i << "! = " << Calculator::factorial(i) << std::endl;
    }
    
    std::cout << "\nPrime number check:" << std::endl;
    int numbers[] = {2, 3, 4, 17, 25, 29, 97, 100};
    for (int num : numbers) {
        std::cout << num << " is " << (Calculator::isPrime(num) ? "prime" : "not prime") << std::endl;
    }
}

void demonstrateErrorHandling() {
    printHeader("ERROR HANDLING DEMONSTRATION");
    
    try {
        std::cout << "Attempting division by zero..." << std::endl;
        Calculator::divide(10, 0);
    } catch (const std::exception& e) {
        std::cout << "Error caught: " << e.what() << std::endl;
    }
    
    try {
        std::cout << "Attempting factorial of negative number..." << std::endl;
        Calculator::factorial(-5);
    } catch (const std::exception& e) {
        std::cout << "Error caught: " << e.what() << std::endl;
    }
}

int main() {
    std::cout << "Welcome to the Calculator Demo - CMake Build!" << std::endl;
    std::cout << "This project demonstrates the CMake build system." << std::endl;
    
    demonstrateBasicOperations();
    demonstrateAdvancedOperations();
    demonstrateErrorHandling();
    
    printHeader("CMAKE BUILD SYSTEM INFORMATION");
    std::cout << "This program was compiled using:" << std::endl;
    std::cout << "- CMake build system with CMakeLists.txt" << std::endl;
    std::cout << "- Header files from: include/ directory" << std::endl;
    std::cout << "- Source files from: src/ directory" << std::endl;
    std::cout << "- Modern cross-platform build approach" << std::endl;
    std::cout << "- Automatic build file generation" << std::endl;
    
    return 0;
}
