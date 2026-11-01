#ifndef CLASS_OBJECT_HPP
#define CLASS_OBJECT_HPP

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <stdexcept>

/**
 * ===============================================
 * CLASSES AND OBJECTS - FUNDAMENTAL OOP CONCEPT
 * ===============================================
 * 
 * A CLASS is a blueprint/template for creating objects
 * An OBJECT is an instance of a class
 * 
 * INTERVIEW QUESTIONS COVERED:
 * 1. What is the difference between class and struct in C++?
 * 2. What are constructors and destructors?
 * 3. What is the this pointer?
 * 4. What are different types of constructors?
 * 5. What is constructor chaining?
 */

namespace BasicConcepts {

/**
 * Basic Class Example
 * Demonstrates: Basic class structure, member variables, member functions
 */
class Person {
private:
    std::string name;
    int age;
    std::string email;

public:
    // Default Constructor
    Person() : name("Unknown"), age(0), email("") {
        std::cout << "Default constructor called\n";
    }
    
    // Parameterized Constructor
    Person(const std::string& n, int a, const std::string& e) 
        : name(n), age(a), email(e) {
        std::cout << "Parameterized constructor called for " << name << "\n";
    }
    
    // Copy Constructor
    Person(const Person& other) 
        : name(other.name), age(other.age), email(other.email) {
        std::cout << "Copy constructor called for " << name << "\n";
    }
    
    // Copy Assignment Operator
    // This operator is used to copy the contents of one object to another existing object.
    // It returns *this by reference so assignments can be chained (a = b = c).
    Person& operator=(const Person& other) {
        if (this != &other) { // Self-assignment check to avoid issues when assigning an object to itself
            name = other.name;
            age = other.age;
            email = other.email;
            std::cout << "Copy assignment called for " << name << "\n";
        }
        return *this;
    }
    
    // Destructor
    ~Person() {
        std::cout << "Destructor called for " << name << "\n";
    }
    
    // Getter methods (const functions)
    const std::string& getName() const { return name; }
    int getAge() const { return age; }
    const std::string& getEmail() const { return email; }
    
    // Setter methods
    void setName(const std::string& n) { name = n; }
    void setAge(int a) { 
        if (a >= 0) age = a; 
        else throw std::invalid_argument("Age cannot be negative");
    }
    void setEmail(const std::string& e) { email = e; }
    
    // Member function demonstrating 'this' pointer
    Person& setDetails(const std::string& n, int a, const std::string& e) {
        this->name = n;    // 'this' pointer usage (optional here)
        this->age = a;
        this->email = e;
        return *this;      // Return reference for method chaining
    }
    
    // Display method
    void display() const {
        std::cout << "Name: " << name << ", Age: " << age << ", Email: " << email << "\n";
    }
    
    // Static method (belongs to class, not object)
    static void printClassInfo() {
        std::cout << "This is Person class - represents a human being\n";
    }
};

/**
 * Class vs Struct Demonstration
 * 
 * INTERVIEW QUESTION: What's the difference between class and struct in C++?
 * ANSWER: 
 * - class: members are private by default
 * - struct: members are public by default
 * - Both can have constructors, destructors, inheritance, etc.
 * - struct is typically used for simple data holders (C-style)
 */

// Using struct for simple data holder
struct Point {
    double x, y;  // Public by default in struct
    
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    
    double distance() const {
        return sqrt(x * x + y * y);
    }
};

// Equivalent class (notice private by default)
class PointClass {
    double x, y;  // Private by default in class
    
public:
    PointClass(double x = 0, double y = 0) : x(x), y(y) {}
    
    double getX() const { return x; }
    double getY() const { return y; }
    
    double distance() const {
        return sqrt(x * x + y * y);
    }
};

/**
 * Static Members Demonstration
 */
class Counter {
private:
    static int totalObjects; // Static member variable
    int objectId;

public:
    Counter() : objectId(++totalObjects) {
        std::cout << "Counter object " << objectId << " created\n";
    }
    
    ~Counter() {
        std::cout << "Counter object " << objectId << " destroyed\n";
    }
    
    int getId() const { return objectId; }
    
    // Static member function
    static int getTotalObjects() {
        return totalObjects; // Can only access static members
    }
    
    static void resetCounter() {
        totalObjects = 0;
    }
};

// Static member definition (required outside class)
int Counter::totalObjects = 0;

} // namespace BasicConcepts

/**
 * ===============================================
 * INTERVIEW QUESTIONS AND ANSWERS
 * ===============================================
 * 
 * Q1: What is the difference between class and struct in C++?
 * A1: In class, members are private by default. In struct, members are public by default.
 *     Both support constructors, destructors, inheritance, etc.
 * 
 * Q2: What are the different types of constructors?
 * A2: 1. Default constructor (no parameters)
 *     2. Parameterized constructor
 *     3. Copy constructor
 *     4. Move constructor (C++11)
 *     5. Conversion constructor (single parameter)
 *     Examples of 4 and 5: 04_advanced_cpp/rule_of_five.hpp
 *
 * Q3: What is the Rule of Three/Five/Zero?
 * A3: Rule of Three: If you define destructor, copy constructor, or copy assignment,
 *     define all three.
 *     Rule of Five: Add move constructor and move assignment (C++11)
 *     Rule of Zero: Use smart pointers and RAII to avoid manual resource management
 *     Example: 04_advanced_cpp/rule_of_five.hpp
 *
 * Q4: What is the 'this' pointer?
 * A4: 'this' is a pointer that points to the current object. Used to:
 *     - Resolve naming conflicts
 *     - Return reference to current object
 *     - Pass current object to other functions
 * 
 * Q5: What are static members?
 * A5: Static members belong to the class, not to any specific object.
 *     - Static variables: Shared among all objects
 *     - Static functions: Can be called without creating objects
 * 
 * Q6: What is a friend function?
 * A6: A friend function can access private and protected members of a class.
 *     It's not a member of the class but has special access privileges.
 * 
 * Q7: What is the mutable keyword?
 * A7: mutable allows modification of a member variable even in const methods.
 *     Used for members that don't affect the logical state of the object.
 */

// ======================= DEMONSTRATION FUNCTION =======================
inline void demonstrateClassObject() {
    std::cout << "\n===== CLASSES AND OBJECTS DEMO =====\n" << std::endl;
    
    // Basic class usage
    std::cout << "1. Basic Class Usage:" << std::endl;
    BasicConcepts::Person person1("Alice", 25, "alice@email.com");
    person1.display();
    person1.setAge(26);
    person1.display();
    
    BasicConcepts::Person person2; // Default constructor
    person2.display();
    
    // Static members and methods
    std::cout << "\n2. Static Methods:" << std::endl;
    BasicConcepts::Person::printClassInfo();
    
    BasicConcepts::Counter counter1;
    BasicConcepts::Counter counter2;
    std::cout << "Counter objects created" << std::endl;
    
    // Constructor demonstration
    std::cout << "\n3. Constructor Types:" << std::endl;
    BasicConcepts::Person defaultPerson;                           // Default
    BasicConcepts::Person bob("Bob", 40, "bob@email.com");         // Parameterized
    BasicConcepts::Person bobCopy(bob);                            // Copy
    BasicConcepts::Person assigned;
    assigned = bob;                                                // Copy assignment

    // Method chaining with this pointer
    std::cout << "\n4. Method Chaining with 'this' pointer:" << std::endl;
    BasicConcepts::Person person3;
    person3.setDetails("Charlie", 30, "charlie@email.com").display();
    
    // Point class demonstration
    std::cout << "\n5. Point Class Usage:" << std::endl;
    BasicConcepts::PointClass p1(3.0, 4.0);
    BasicConcepts::PointClass p2;
    
    std::cout << "Point 1: (" << p1.getX() << ", " << p1.getY() << ")" << std::endl;
    std::cout << "Point 2: (" << p2.getX() << ", " << p2.getY() << ")" << std::endl;
}

#endif // CLASS_OBJECT_HPP
