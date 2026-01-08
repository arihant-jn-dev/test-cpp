#include <iostream>
#include <memory>
#include <vector>

// Include only basic concepts that we know work
#include "basic/class_object.hpp"
#include "basic/encapsulation.hpp"
#include "basic/inheritance.hpp"

/**
 * Simplified Working C++ OOP Demo
 * This version only includes concepts that compile and run successfully
 */

int main() {
    std::cout << "=== C++ OOP CONCEPTS WORKING DEMO ===" << std::endl;
    std::cout << "Demonstrating: Classes, Encapsulation, Inheritance" << std::endl;
    
    try {
        // 1. Classes and Objects
        std::cout << "\n1. Classes and Objects:" << std::endl;
        BasicConcepts::Person person("Alice Johnson", 25, "alice@example.com");
        std::cout << "Person: " << person.getName() << ", Age: " << person.getAge() << std::endl;
        
        // Static member demo
        BasicConcepts::Counter counter1;
        BasicConcepts::Counter counter2;
        std::cout << "Counter 1 ID: " << counter1.getId() << std::endl;
        std::cout << "Counter 2 ID: " << counter2.getId() << std::endl;
        std::cout << "Total objects created: " << BasicConcepts::Counter::getTotalObjects() << std::endl;
        
        // 2. Encapsulation (Data Hiding and Access Control)
        std::cout << "\n2. Encapsulation:" << std::endl;
        BasicConcepts::BankAccount account("Alice Johnson", "1234567890", "1234", 1000.0);
        std::cout << "Account holder: " << account.getAccountHolder() << std::endl;
        std::cout << "Masked account: " << account.getMaskedAccountNumber() << std::endl;
        
        account.deposit(500.0, "1234");
        std::cout << "Balance after deposit: $" << account.getBalance("1234") << std::endl;
        
        account.withdraw(200.0, "1234");
        std::cout << "Balance after withdrawal: $" << account.getBalance("1234") << std::endl;
        
        // Try with wrong PIN (will throw exception)
        try {
            account.getBalance("wrong");
        } catch (const std::exception& e) {
            std::cout << "Security error: " << e.what() << std::endl;
        }
        
        // 3. Inheritance (Single, Multiple, Virtual)
        std::cout << "\n3. Inheritance:" << std::endl;
        
        // Single inheritance
        BasicConcepts::Car car("Toyota", "Camry", 2023, 30000.0, 4, "Gasoline", 2.5);
        std::cout << "Car: " << car.getBrand() << " " << car.getModel() 
                  << ", Doors: " << car.getNumberOfDoors() 
                  << ", Fuel: " << car.getFuelType() << std::endl;
        
        // Multiple inheritance
        BasicConcepts::SportsCar sports("Ferrari", "F8", 2023, 250000.0, 2, "Gasoline", 3.9, 340, 3.0, true);
        std::cout << "Sports car: " << sports.getBrand() << " " << sports.getModel()
                  << ", Max speed: " << sports.getMaxSpeed() << " mph" << std::endl;
        
        // Virtual inheritance demo
        BasicConcepts::CarEntertainmentSystem entertainment;
        std::cout << "Entertainment system demonstrates virtual inheritance to avoid diamond problem" << std::endl;
        
        // 4. Access Control Demo
        std::cout << "\n4. Access Control in Inheritance:" << std::endl;
        BasicConcepts::PublicDerived pubDerived;
        BasicConcepts::PrivateDerived privDerived;
        BasicConcepts::ProtectedDerived protDerived;
        
        pubDerived.testAccess();
        privDerived.testAccess();
        protDerived.testAccess();
        
        // 5. Employee System (Advanced Encapsulation)
        std::cout << "\n5. Employee Management System:" << std::endl;
        BasicConcepts::Employee emp1("John", "Doe", "Engineering", 75000.0, 3);
        BasicConcepts::Employee emp2("Jane", "Smith", "Marketing", 65000.0, 2);
        
        emp1.displayInfo();
        emp2.displayInfo();
        
        std::cout << "John's salary: $" << emp1.getSalary() << std::endl;
        std::cout << "Jane's department: " << emp2.getDepartment() << std::endl;
        
        std::cout << "\n=== DEMO COMPLETED SUCCESSFULLY! ===" << std::endl;
        std::cout << "✅ All basic OOP concepts demonstrated:" << std::endl;
        std::cout << "   • Classes and Objects with constructors/destructors" << std::endl;
        std::cout << "   • Encapsulation with private/protected/public access" << std::endl;
        std::cout << "   • Single, multiple, and virtual inheritance" << std::endl;
        std::cout << "   • Access control in inheritance hierarchies" << std::endl;
        std::cout << "   • Static members and methods" << std::endl;
        std::cout << "   • Exception handling for security" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "\nError: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
