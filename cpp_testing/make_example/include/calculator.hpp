#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

/**
 * Calculator class that demonstrates various mathematical operations
 * This header file shows how to organize code for Make builds
 */
class Calculator {
public:
    /**
     * Basic arithmetic operations
     */
    static double add(double a, double b);
    static double subtract(double a, double b);
    static double multiply(double a, double b);
    static double divide(double a, double b);
    
    /**
     * Advanced operations
     */
    static double power(double base, double exponent);
    static double factorial(int n);
    static bool isPrime(int n);
};

#endif // CALCULATOR_HPP
