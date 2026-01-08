#include "calculator.hpp"
#include <cmath>
#include <stdexcept>

/**
 * Calculator implementation file
 * This demonstrates how source files work with CMake
 */

// Basic arithmetic operations
double Calculator::add(double a, double b) {
    return a + b;
}

double Calculator::subtract(double a, double b) {
    return a - b;
}

double Calculator::multiply(double a, double b) {
    return a * b;
}

double Calculator::divide(double a, double b) {
    if (b == 0) {
        throw std::runtime_error("Division by zero!");
    }
    return a / b;
}

// Advanced operations
double Calculator::power(double base, double exponent) {
    return std::pow(base, exponent);
}

double Calculator::factorial(int n) {
    if (n < 0) {
        throw std::runtime_error("Factorial of negative number is undefined!");
    }
    if (n == 0 || n == 1) {
        return 1;
    }
    
    double result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

bool Calculator::isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}
