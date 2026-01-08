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
 */

namespace BasicConcepts {

/**
 * Perfect Encapsulation Example
 * Demonstrates: Private data members, public interface, data validation
 */
class BankAccount {
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
    BankAccount(const std::string& holder, const std::string& accNum, 
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
 * Employee Class - Real-world Encapsulation Example
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

} // namespace BasicConcepts

#endif // ENCAPSULATION_HPP
