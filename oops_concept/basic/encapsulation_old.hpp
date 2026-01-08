#ifndef ENCAPSULATION_HPP
#define ENCAPSULATION_HPP

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

/**
 * ===============================================
 * ENCAPSULATION - DATA HIDING AND ACCESS CONTROL
 * ===============================================
 * 
 * Encapsulation is the bundling of data and methods that work on that data
 * within one unit (class), and restricting access to some of the object's components.
 * 
 * INTERVIEW QUESTIONS COVERED:
 * 1. What is encapsulation and why is it important?
 * 2. What are access specifiers in C++?
 * 3. What are getter and setter methods?
 * 4. How to achieve data hiding?
 * 5. What is the difference between private, protected, and public?
 */

namespace BasicConcepts {

/**
 * Perfect Encapsulation Example
 * Demonstrates: Private data members, public interface, data validation
 */
class SecureBankAccount {
private:
    // Private data members - hidden from outside world
    std::string accountHolder;
    std::string accountNumber;
    double balance;
    std::string pin;
    bool isActive;
    
    // Private helper methods
    bool validatePin(const std::string& inputPin) const {
        return pin == inputPin;
    }
    
    bool isAccountActive() const {
        return isActive;
    }
    
    void logTransaction(const std::string& operation, double amount) {
        std::cout << "[LOG] " << operation << " of $" << amount 
                  << " on account " << accountNumber << std::endl;
    }

public:
    // Constructor with validation
    SecureBankAccount(const std::string& holder, const std::string& accNum, 
                const std::string& userPin, double initialBalance = 0.0) {
        if (holder.empty()) {
            throw std::invalid_argument("Account holder name cannot be empty");
        }
        if (accNum.length() < 10) {
            throw std::invalid_argument("Account number must be at least 10 digits");
        }
        if (userPin.length() != 4) {
            throw std::invalid_argument("PIN must be exactly 4 digits");
        }
        if (initialBalance < 0) {
            throw std::invalid_argument("Initial balance cannot be negative");
        }
        
        accountHolder = holder;
        accountNumber = accNum;
        pin = userPin;
        balance = initialBalance;
        isActive = true;
        
        std::cout << "Bank account created for " << accountHolder << std::endl;
    }
    
    // Controlled access through public methods
    
    // Read-only access to account holder (getter)
    const std::string& getAccountHolder() const {
        return accountHolder;
    }
    
    // Read-only access to account number (masked for security)
    std::string getMaskedAccountNumber() const {
        if (accountNumber.length() >= 4) {
            return "****" + accountNumber.substr(accountNumber.length() - 4);
        }
        return "****";
    }
    
    // Controlled access to balance (requires authentication)
    double getBalance(const std::string& inputPin) const {
        if (!isAccountActive()) {
            throw std::runtime_error("Account is not active");
        }
        if (!validatePin(inputPin)) {
            throw std::runtime_error("Invalid PIN");
        }
        return balance;
    }
    
    // Controlled deposit operation
    void deposit(double amount, const std::string& inputPin) {
        if (!isAccountActive()) {
            throw std::runtime_error("Account is not active");
        }
        if (!validatePin(inputPin)) {
            throw std::runtime_error("Invalid PIN");
        }
        if (amount <= 0) {
            throw std::invalid_argument("Deposit amount must be positive");
        }
        
        balance += amount;
        logTransaction("Deposit", amount);
        std::cout << "Deposited $" << amount << ". New balance: $" << balance << std::endl;
    }
    
    // Controlled withdrawal operation
    bool withdraw(double amount, const std::string& inputPin) {
        if (!isAccountActive()) {
            throw std::runtime_error("Account is not active");
        }
        if (!validatePin(inputPin)) {
            throw std::runtime_error("Invalid PIN");
        }
        if (amount <= 0) {
            throw std::invalid_argument("Withdrawal amount must be positive");
        }
        if (amount > balance) {
            std::cout << "Insufficient funds. Available balance: $" << balance << std::endl;
            return false;
        }
        
        balance -= amount;
        logTransaction("Withdrawal", amount);
        std::cout << "Withdrawn $" << amount << ". New balance: $" << balance << std::endl;
        return true;
    }
    
    // Controlled PIN change
    bool changePin(const std::string& oldPin, const std::string& newPin) {
        if (!validatePin(oldPin)) {
            std::cout << "Invalid current PIN" << std::endl;
            return false;
        }
        if (newPin.length() != 4) {
            std::cout << "New PIN must be exactly 4 digits" << std::endl;
            return false;
        }
        
        pin = newPin;
        std::cout << "PIN changed successfully" << std::endl;
        return true;
    }
    
    // Account management
    void deactivateAccount(const std::string& inputPin) {
        if (!validatePin(inputPin)) {
            throw std::runtime_error("Invalid PIN");
        }
        isActive = false;
        std::cout << "Account deactivated" << std::endl;
    }
    
    void activateAccount(const std::string& inputPin) {
        if (!validatePin(inputPin)) {
            throw std::runtime_error("Invalid PIN");
        }
        isActive = true;
        std::cout << "Account activated" << std::endl;
    }
};

/**
 * Access Specifiers Demonstration
 * Shows difference between private, protected, and public
 */
class AccessSpecifierDemo {
private:
    int privateVar;        // Only accessible within this class
    
    void privateMethod() {
        std::cout << "Private method called" << std::endl;
    }

protected:
    int protectedVar;      // Accessible in this class and derived classes
    
    void protectedMethod() {
        std::cout << "Protected method called" << std::endl;
    }

public:
    int publicVar;         // Accessible everywhere
    
    AccessSpecifierDemo() : privateVar(1), protectedVar(2), publicVar(3) {}
    
    void publicMethod() {
        std::cout << "Public method called" << std::endl;
        // Can access all members within the same class
        privateMethod();
        protectedMethod();
        std::cout << "Private var: " << privateVar << std::endl;
        std::cout << "Protected var: " << protectedVar << std::endl;
        std::cout << "Public var: " << publicVar << std::endl;
    }
    
    // Getters for private members (controlled access)
    int getPrivateVar() const { return privateVar; }
    
    // Setters with validation
    void setPrivateVar(int value) {
        if (value >= 0) {
            privateVar = value;
        } else {
            throw std::invalid_argument("Private var must be non-negative");
        }
    }
};

// Derived class to demonstrate protected access
class DerivedAccessDemo : public AccessSpecifierDemo {
public:
    void demonstrateAccess() {
        std::cout << "In derived class:" << std::endl;
        
        // Can access public members
        publicVar = 10;
        publicMethod();
        
        // Can access protected members
        protectedVar = 20;
        protectedMethod();
        
        // Cannot access private members directly
        // privateVar = 30;  // This would cause compilation error
        // privateMethod();  // This would cause compilation error
        
        // Must use public interface to access private members
        setPrivateVar(30);
        std::cout << "Private var through getter: " << getPrivateVar() << std::endl;
    }
};

/**
 * Employee Class - Real-world Encapsulation Example
 * Demonstrates: Data validation, business logic encapsulation, controlled modification
 */
class Employee {
private:
    static int nextEmployeeId;  // Static counter for unique IDs
    
    int employeeId;
    std::string firstName;
    std::string lastName;
    std::string department;
    double salary;
    int yearsOfExperience;
    bool isActive;
    std::vector<std::string> skills;
    
    // Private validation methods
    bool isValidName(const std::string& name) const {
        return !name.empty() && name.length() <= 50;
    }
    
    bool isValidSalary(double sal) const {
        return sal >= 0 && sal <= 1000000; // Max salary cap
    }
    
    bool isValidExperience(int years) const {
        return years >= 0 && years <= 50;
    }

public:
    Employee(const std::string& fName, const std::string& lName, 
             const std::string& dept, double sal, int exp) 
        : employeeId(++nextEmployeeId), isActive(true) {
        
        if (!isValidName(fName) || !isValidName(lName)) {
            throw std::invalid_argument("Invalid name");
        }
        if (!isValidSalary(sal)) {
            throw std::invalid_argument("Invalid salary");
        }
        if (!isValidExperience(exp)) {
            throw std::invalid_argument("Invalid experience");
        }
        
        firstName = fName;
        lastName = lName;
        department = dept;
        salary = sal;
        yearsOfExperience = exp;
        
        std::cout << "Employee " << getFullName() << " created with ID: " 
                  << employeeId << std::endl;
    }
    
    // Read-only access methods
    int getEmployeeId() const { return employeeId; }
    std::string getFullName() const { return firstName + " " + lastName; }
    const std::string& getDepartment() const { return department; }
    double getSalary() const { return salary; }
    int getExperience() const { return yearsOfExperience; }
    bool getActiveStatus() const { return isActive; }
    
    // Controlled modification methods
    void updateDepartment(const std::string& newDept) {
        if (!isActive) {
            throw std::runtime_error("Cannot update inactive employee");
        }
        department = newDept;
        std::cout << "Department updated to: " << newDept << std::endl;
    }
    
    void increaseSalary(double percentage) {
        if (!isActive) {
            throw std::runtime_error("Cannot update inactive employee");
        }
        if (percentage < 0 || percentage > 100) {
            throw std::invalid_argument("Invalid percentage");
        }
        
        double increase = salary * (percentage / 100.0);
        double newSalary = salary + increase;
        
        if (!isValidSalary(newSalary)) {
            throw std::runtime_error("Salary increase would exceed maximum limit");
        }
        
        salary = newSalary;
        std::cout << "Salary increased by " << percentage << "% to $" << salary << std::endl;
    }
    
    void addExperience(int additionalYears) {
        if (!isActive) {
            throw std::runtime_error("Cannot update inactive employee");
        }
        if (additionalYears < 0) {
            throw std::invalid_argument("Additional years cannot be negative");
        }
        
        int newExperience = yearsOfExperience + additionalYears;
        if (!isValidExperience(newExperience)) {
            throw std::runtime_error("Total experience would exceed maximum limit");
        }
        
        yearsOfExperience = newExperience;
        std::cout << "Experience updated to " << yearsOfExperience << " years" << std::endl;
    }
    
    void addSkill(const std::string& skill) {
        if (!isActive) {
            throw std::runtime_error("Cannot update inactive employee");
        }
        if (skill.empty()) {
            throw std::invalid_argument("Skill cannot be empty");
        }
        
        // Check if skill already exists
        for (const auto& existingSkill : skills) {
            if (existingSkill == skill) {
                std::cout << "Skill '" << skill << "' already exists" << std::endl;
                return;
            }
        }
        
        skills.push_back(skill);
        std::cout << "Skill '" << skill << "' added" << std::endl;
    }
    
    std::vector<std::string> getSkills() const {
        return skills; // Return copy, not reference
    }
    
    void deactivate() {
        isActive = false;
        std::cout << "Employee " << getFullName() << " deactivated" << std::endl;
    }
    
    void activate() {
        isActive = true;
        std::cout << "Employee " << getFullName() << " activated" << std::endl;
    }
    
    void displayInfo() const {
        std::cout << "\n--- Employee Information ---" << std::endl;
        std::cout << "ID: " << employeeId << std::endl;
        std::cout << "Name: " << getFullName() << std::endl;
        std::cout << "Department: " << department << std::endl;
        std::cout << "Salary: $" << salary << std::endl;
        std::cout << "Experience: " << yearsOfExperience << " years" << std::endl;
        std::cout << "Status: " << (isActive ? "Active" : "Inactive") << std::endl;
        std::cout << "Skills: ";
        for (size_t i = 0; i < skills.size(); ++i) {
            std::cout << skills[i];
            if (i < skills.size() - 1) std::cout << ", ";
        }
        std::cout << std::endl;
    }
};

// Static member initialization
int Employee::nextEmployeeId = 1000;

/**
 * Encapsulation with Composition Example
 * Demonstrates: How encapsulation works with object composition
 */
class Address {
private:
    std::string street;
    std::string city;
    std::string state;
    std::string zipCode;

public:
    Address(const std::string& st, const std::string& c, 
            const std::string& s, const std::string& zip)
        : street(st), city(c), state(s), zipCode(zip) {}
    
    // Read-only access
    const std::string& getStreet() const { return street; }
    const std::string& getCity() const { return city; }
    const std::string& getState() const { return state; }
    const std::string& getZipCode() const { return zipCode; }
    
    std::string getFullAddress() const {
        return street + ", " + city + ", " + state + " " + zipCode;
    }
    
    // Controlled modification
    void updateStreet(const std::string& newStreet) {
        if (!newStreet.empty()) {
            street = newStreet;
        }
    }
};

class Person {
private:
    std::string name;
    int age;
    Address address; // Composition - Person HAS-A Address

public:
    Person(const std::string& n, int a, const Address& addr)
        : name(n), age(a), address(addr) {}
    
    // Encapsulated access to composed object
    const std::string& getName() const { return name; }
    int getAge() const { return age; }
    std::string getAddress() const { return address.getFullAddress(); }
    
    // Controlled modification of composed object
    void updateAddress(const Address& newAddress) {
        address = newAddress;
    }
    
    void updateStreet(const std::string& newStreet) {
        address.updateStreet(newStreet); // Delegation to composed object
    }
};

} // namespace BasicConcepts

/**
 * ===============================================
 * INTERVIEW QUESTIONS AND ANSWERS
 * ===============================================
 * 
 * Q1: What is encapsulation and why is it important?
 * A1: Encapsulation is bundling data and methods together and hiding internal
 *     implementation details. Benefits:
 *     - Data protection from unauthorized access
 *     - Code maintainability
 *     - Flexibility to change implementation
 *     - Data validation and consistency
 * 
 * Q2: What are the access specifiers in C++?
 * A2: - private: Accessible only within the same class
 *     - protected: Accessible within the class and its derived classes
 *     - public: Accessible from anywhere
 * 
 * Q3: What are getter and setter methods?
 * A3: - Getters: Provide read access to private data (const methods)
 *     - Setters: Provide controlled write access with validation
 *     - They maintain encapsulation while allowing controlled access
 * 
 * Q4: How to achieve data hiding in C++?
 * A4: - Make data members private
 *     - Provide public interface through methods
 *     - Use validation in setter methods
 *     - Return copies instead of references when needed
 * 
 * Q5: What is the difference between encapsulation and abstraction?
 * A5: - Encapsulation: Hiding implementation details and data
 *     - Abstraction: Hiding complexity and showing only essential features
 *     - Encapsulation is achieved through access specifiers
 *     - Abstraction is achieved through abstract classes/interfaces
 * 
 * Q6: Can private members be accessed outside the class?
 * A6: No, except through:
 *     - Public methods of the same class
 *     - Friend functions/classes
 *     - Static member functions of the same class
 * 
 * Q7: What is information hiding?
 * A7: Information hiding is a principle where internal implementation details
 *     are hidden from users, providing only necessary interface.
 *     It's achieved through encapsulation.
 */

#endif // ENCAPSULATION_HPP
