#include <iostream>
#include <memory>
#include <vector>
#include <string>

// Include all working header files
#include "basic/class_object.hpp"
#include "basic/encapsulation.hpp"
#include "basic/inheritance.hpp"

/**
 * 🎯 MASTER DEMO FILE - ALL C++ OOP CONCEPTS
 * 
 * This file demonstrates all core OOP concepts in a single, comprehensive example.
 * Each section is self-contained and can be understood independently.
 * 
 * INTERVIEW TOPICS COVERED:
 * ✅ Classes and Objects
 * ✅ Constructors and Destructors
 * ✅ Encapsulation (Data Hiding)
 * ✅ Inheritance (Single, Multiple, Virtual)
 * ✅ Access Control (Public, Private, Protected)
 * ✅ Static Members and Methods
 * ✅ Exception Handling
 * ✅ RAII (Resource Acquisition Is Initialization)
 */

// Function declarations
void demonstrateClassesAndObjects();
void demonstrateEncapsulationConcept();
void demonstrateInheritanceConcept();
void demonstrateAccessControl();
void demonstrateStaticMembers();
void demonstrateExceptionHandling();

int main() {
    std::cout << "=============================================" << std::endl;
    std::cout << "🎯 C++ OOP CONCEPTS - MASTER DEMONSTRATION" << std::endl;
    std::cout << "=============================================" << std::endl;
    std::cout << "" << std::endl;
    
    try {
        demonstrateClassesAndObjects();
        demonstrateEncapsulationConcept();
        demonstrateInheritanceConcept();
        demonstrateAccessControl();
        demonstrateStaticMembers();
        demonstrateExceptionHandling();
        
        std::cout << "=============================================" << std::endl;
        std::cout << "🎉 ALL DEMONSTRATIONS COMPLETED SUCCESSFULLY!" << std::endl;
        std::cout << "=============================================" << std::endl;
        std::cout << "" << std::endl;
        std::cout << "📚 CONCEPTS DEMONSTRATED:" << std::endl;
        std::cout << "✅ Classes, Objects, Constructors, Destructors" << std::endl;
        std::cout << "✅ Encapsulation and Data Hiding" << std::endl;
        std::cout << "✅ Single, Multiple, and Virtual Inheritance" << std::endl;
        std::cout << "✅ Access Control (Public, Private, Protected)" << std::endl;
        std::cout << "✅ Static Members and Methods" << std::endl;
        std::cout << "✅ Exception Handling and Security" << std::endl;
        std::cout << "✅ RAII and Resource Management" << std::endl;
        std::cout << "" << std::endl;
        std::cout << "🚀 Ready for C++ OOP interviews!" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "❌ Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}

void demonstrateClassesAndObjects() {
    std::cout << "📋 1. CLASSES AND OBJECTS" << std::endl;
    std::cout << "-------------------------" << std::endl;
    
    // Object creation with different constructors
    std::cout << "Creating Person objects:" << std::endl;
    BasicConcepts::Person person1("Alice Johnson", 25, "alice@example.com");
    BasicConcepts::Person person2("Bob Smith", 30, "bob@example.com");
    
    // Demonstrating getter methods
    std::cout << "Person 1: " << person1.getName() << ", Age: " << person1.getAge() << std::endl;
    std::cout << "Person 2: " << person2.getName() << ", Age: " << person2.getAge() << std::endl;
    
    // Method chaining demonstration
    person1.setDetails("Alice Johnson Updated", 26, "alice.updated@example.com");
    std::cout << "Updated Person 1: " << person1.getName() << ", Age: " << person1.getAge() << std::endl;
    
    // Static method call
    BasicConcepts::Person::printClassInfo();
    
    std::cout << "" << std::endl;
}

void demonstrateEncapsulationConcept() {
    std::cout << "🔒 2. ENCAPSULATION (DATA HIDING)" << std::endl;
    std::cout << "---------------------------------" << std::endl;
    
    try {
        // Bank account with PIN protection
        BasicConcepts::BankAccount account("Alice Johnson", "1234567890", "1234", 1000.0);
        
        std::cout << "Account holder: " << account.getAccountHolder() << std::endl;
        std::cout << "Masked account: " << account.getMaskedAccountNumber() << std::endl;
        
        // Valid operations
        account.deposit(500.0, "1234");
        std::cout << "Balance after deposit: $" << account.getBalance("1234") << std::endl;
        
        account.withdraw(200.0, "1234");
        std::cout << "Balance after withdrawal: $" << account.getBalance("1234") << std::endl;
        
        // Demonstrate security (this will throw an exception)
        std::cout << "Attempting access with wrong PIN..." << std::endl;
        try {
            account.getBalance("wrong");
        } catch (const std::exception& e) {
            std::cout << "Security protection works: " << e.what() << std::endl;
        }
        
    } catch (const std::exception& e) {
        std::cout << "Account error: " << e.what() << std::endl;
    }
    
    std::cout << "" << std::endl;
}

void demonstrateInheritanceConcept() {
    std::cout << "🏗️ 3. INHERITANCE" << std::endl;
    std::cout << "-----------------" << std::endl;
    
    std::cout << "Single Inheritance (Vehicle -> Car):" << std::endl;
    BasicConcepts::Car car("Toyota", "Camry", 2023, 30000.0, 4, "Gasoline", 2.5);
    std::cout << "Car: " << car.getBrand() << " " << car.getModel() 
              << ", Doors: " << car.getNumberOfDoors() 
              << ", Fuel: " << car.getFuelType() << std::endl;
    
    std::cout << "" << std::endl;
    std::cout << "Multiple Inheritance (Car + Performance):" << std::endl;
    BasicConcepts::SportsCar sports("Ferrari", "F8", 2023, 250000.0, 2, "Gasoline", 3.9, 340, 3.0, true);
    std::cout << "Sports car: " << sports.getBrand() << " " << sports.getModel()
              << ", Max speed: " << sports.getMaxSpeed() << " mph" 
              << ", Acceleration: " << sports.getAcceleration() << "s (0-60)" << std::endl;
    
    std::cout << "" << std::endl;
    std::cout << "Virtual Inheritance (Diamond Problem Solution):" << std::endl;
    BasicConcepts::CarEntertainmentSystem entertainment;
    std::cout << "Entertainment system demonstrates virtual inheritance" << std::endl;
    std::cout << "Prevents diamond problem in multiple inheritance" << std::endl;
    
    std::cout << "" << std::endl;
}

void demonstrateAccessControl() {
    std::cout << "🔐 4. ACCESS CONTROL IN INHERITANCE" << std::endl;
    std::cout << "-----------------------------------" << std::endl;
    
    std::cout << "Public Inheritance:" << std::endl;
    BasicConcepts::PublicDerived pubDerived;
    pubDerived.testAccess();
    
    std::cout << "" << std::endl;
    std::cout << "Private Inheritance:" << std::endl;
    BasicConcepts::PrivateDerived privDerived;
    privDerived.testAccess();
    
    std::cout << "" << std::endl;
    std::cout << "Protected Inheritance:" << std::endl;
    BasicConcepts::ProtectedDerived protDerived;
    protDerived.testAccess();
    
    std::cout << "" << std::endl;
}

void demonstrateStaticMembers() {
    std::cout << "📊 5. STATIC MEMBERS AND METHODS" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    
    std::cout << "Creating Counter objects (static member tracking):" << std::endl;
    BasicConcepts::Counter counter1;
    BasicConcepts::Counter counter2;
    BasicConcepts::Counter counter3;
    
    std::cout << "Counter 1 ID: " << counter1.getId() << std::endl;
    std::cout << "Counter 2 ID: " << counter2.getId() << std::endl;
    std::cout << "Counter 3 ID: " << counter3.getId() << std::endl;
    std::cout << "Total objects created: " << BasicConcepts::Counter::getTotalObjects() << std::endl;
    
    std::cout << "" << std::endl;
    std::cout << "Employee Management System:" << std::endl;
    BasicConcepts::Employee emp1("John", "Doe", "Engineering", 75000.0, 3);
    BasicConcepts::Employee emp2("Jane", "Smith", "Marketing", 65000.0, 2);
    
    emp1.displayInfo();
    emp2.displayInfo();
    
    std::cout << "" << std::endl;
}

void demonstrateExceptionHandling() {
    std::cout << "⚠️ 6. EXCEPTION HANDLING AND RAII" << std::endl;
    std::cout << "---------------------------------" << std::endl;
    
    // Demonstrate exception safety in bank operations
    try {
        BasicConcepts::BankAccount account("Test User", "1111111111", "0000", 100.0);
        
        std::cout << "Attempting valid withdrawal..." << std::endl;
        account.withdraw(50.0, "0000");
        std::cout << "Success! Balance: $" << account.getBalance("0000") << std::endl;
        
        std::cout << "Attempting overdraft..." << std::endl;
        account.withdraw(1000.0, "0000"); // This should fail
        
    } catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }
    
    // Demonstrate RAII with automatic cleanup
    std::cout << "" << std::endl;
    std::cout << "RAII Demonstration (automatic cleanup):" << std::endl;
    {
        std::cout << "Creating scoped objects..." << std::endl;
        BasicConcepts::Counter scopedCounter;
        std::cout << "Object ID: " << scopedCounter.getId() << std::endl;
        std::cout << "Leaving scope..." << std::endl;
    }
    std::cout << "Object automatically destroyed (RAII)" << std::endl;
    
    std::cout << "" << std::endl;
}
