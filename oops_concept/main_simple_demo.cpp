#include <iostream>
#include "basic/class_object.hpp"
#include "basic/encapsulation.hpp"
#include "basic/inheritance.hpp"

/**
 * Simple demonstration of core OOP concepts for compilation testing
 */
int main() {
    std::cout << "=== C++ OOP Concepts Demo ===" << std::endl;
    
    try {
        // 1. Basic Classes and Objects
        std::cout << "\n1. Basic Classes and Objects:" << std::endl;
        BasicConcepts::Person person("Alice", 25, "alice@example.com");
        std::cout << "Person: " << person.getName() << ", Age: " << person.getAge() << std::endl;
        
        // 2. Encapsulation
        std::cout << "\n2. Encapsulation:" << std::endl;
        BasicConcepts::BankAccount account("Alice Johnson", "1234567890", "1234", 1000.0);
        account.deposit(500.0, "1234");
        std::cout << "Balance: $" << account.getBalance("1234") << std::endl;
        
        // 3. Inheritance  
        std::cout << "\n3. Inheritance:" << std::endl;
        BasicConcepts::Car car("Toyota", "Camry", 2023, 30000.0, 4, "Gasoline", 2.5);
        std::cout << "Car: " << car.getBrand() << " " << car.getModel() 
                  << ", Doors: " << car.getNumberOfDoors() << std::endl;
        
        std::cout << "\n=== All tests passed! ===" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
