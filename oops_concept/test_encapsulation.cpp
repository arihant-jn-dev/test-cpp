#include "basic/encapsulation.hpp"
#include <iostream>

int main() {
    std::cout << "🧪 TESTING BASIC OOP CONCEPTS - Encapsulation\n" << std::endl;
    
    try {
        // Test BasicConcepts namespace
        std::cout << "===== ENCAPSULATION DEMO =====\n" << std::endl;
        
        // 1. Test BankAccount with PIN protection
        std::cout << "1. Bank Account with PIN Protection:" << std::endl;
        BasicConcepts::BankAccount account1("John Doe", "1234567890", "1234", 1000.0);
        std::cout << "Account holder: " << account1.getAccountHolder() << std::endl;
        std::cout << "Masked account: " << account1.getMaskedAccountNumber() << std::endl;
        std::cout << "Initial balance: $" << account1.getBalance("1234") << std::endl;
        
        account1.deposit(500.0, "1234");
        std::cout << "After deposit: $" << account1.getBalance("1234") << std::endl;
        
        bool withdrawResult = account1.withdraw(200.0, "1234");
        std::cout << "Withdrawal successful: " << (withdrawResult ? "Yes" : "No") << std::endl;
        std::cout << "After withdrawal: $" << account1.getBalance("1234") << std::endl;
        
        std::cout << "\n--- Testing PIN security ---" << std::endl;
        try {
            account1.getBalance("0000"); // Wrong PIN
        } catch (const std::exception& e) {
            std::cout << "Security protection works: " << e.what() << std::endl;
        }
        
        std::cout << std::endl;
        
        // 2. Test Employee class
        std::cout << "2. Employee Management System:" << std::endl;
        BasicConcepts::Employee emp1("Alice", "Johnson", "Engineering", 75000.0, 3);
        BasicConcepts::Employee emp2("Bob", "Smith", "Marketing", 65000.0, 2);
        
        emp1.displayInfo();
        emp2.displayInfo();
        
        std::cout << "\n--- Updating employee information ---" << std::endl;
        emp1.updateDepartment("Senior Engineering");
        emp1.increaseSalary(10.0); // 10% raise
        emp1.addExperience(1);
        emp1.addSkill("C++");
        emp1.addSkill("Python");
        emp1.addSkill("System Design");
        
        emp1.displayInfo();
        
        std::cout << "\n--- Employee skills ---" << std::endl;
        auto skills = emp1.getSkills();
        for (const auto& skill : skills) {
            std::cout << "- " << skill << std::endl;
        }
        
        std::cout << std::endl;
        
        // 3. Test validation and security
        std::cout << "3. Data Validation and Security:" << std::endl;
        
        try {
            // Test invalid account creation
            BasicConcepts::BankAccount invalidAccount("", "123", "12", -100.0);
        } catch (const std::exception& e) {
            std::cout << "Validation works - Invalid account: " << e.what() << std::endl;
        }
        
        try {
            // Test invalid employee creation
            BasicConcepts::Employee invalidEmp("", "Smith", "IT", -50000.0, -5);
        } catch (const std::exception& e) {
            std::cout << "Validation works - Invalid employee: " << e.what() << std::endl;
        }
        
        std::cout << std::endl;
        
        // 4. Test access control
        std::cout << "4. Access Control Demonstration:" << std::endl;
        BasicConcepts::BankAccount controlAccount("Test User", "1111111111", "1111", 100.0);
        
        std::cout << "Can access public methods:" << std::endl;
        std::cout << "Account holder: " << controlAccount.getAccountHolder() << std::endl;
        std::cout << "Masked account: " << controlAccount.getMaskedAccountNumber() << std::endl;
        
        std::cout << "Cannot access private data directly (compile-time protection)" << std::endl;
        // controlAccount.balance; // This would cause compilation error
        // controlAccount.pin; // This would cause compilation error
        
        std::cout << std::endl;
        
        // 5. Advanced features
        std::cout << "5. Advanced Encapsulation Features:" << std::endl;
        BasicConcepts::BankAccount advAccount("Advanced User", "5555555555", "5555", 1000.0);
        
        // PIN change
        bool pinChanged = advAccount.changePin("5555", "9999");
        std::cout << "PIN change successful: " << (pinChanged ? "Yes" : "No") << std::endl;
        
        // Test with new PIN
        std::cout << "Balance with new PIN: $" << advAccount.getBalance("9999") << std::endl;
        
        // Account deactivation
        advAccount.deactivateAccount("9999");
        
        try {
            advAccount.getBalance("9999"); // Should fail - account inactive
        } catch (const std::exception& e) {
            std::cout << "Account protection works: " << e.what() << std::endl;
        }
        
        // Reactivate
        advAccount.activateAccount("9999");
        std::cout << "Reactivated - Balance: $" << advAccount.getBalance("9999") << std::endl;
        
        std::cout << "\n✅ Encapsulation test completed successfully!" << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "❌ Exception occurred: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
