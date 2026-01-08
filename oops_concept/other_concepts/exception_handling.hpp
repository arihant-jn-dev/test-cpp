#ifndef EXCEPTION_HANDLING_HPP
#define EXCEPTION_HANDLING_HPP

#include <iostream>
#include <string>
#include <stdexcept>
#include <memory>
#include <vector>
#include <fstream>

/**
 * EXCEPTION HANDLING IN C++
 * - Try-catch-throw mechanism
 * - Exception safety guarantees
 * - RAII and exception safety
 * - Custom exceptions
 * - Common in interviews for robust code design
 */

// ======================= CUSTOM EXCEPTION CLASSES =======================
class BankException : public std::exception {
protected:
    std::string message;
    
public:
    BankException(const std::string& msg) : message("Bank Error: " + msg) {}
    
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class InsufficientFundsException : public BankException {
private:
    double attempted;
    double available;
    
public:
    InsufficientFundsException(double attemptedAmount, double availableAmount)
        : BankException("Insufficient funds"), attempted(attemptedAmount), available(availableAmount) {
        message += " (Attempted: $" + std::to_string(attempted) + 
                   ", Available: $" + std::to_string(available) + ")";
    }
    
    double getAttempted() const { return attempted; }
    double getAvailable() const { return available; }
};

class InvalidAccountException : public BankException {
private:
    std::string accountNumber;
    
public:
    InvalidAccountException(const std::string& account)
        : BankException("Invalid account number"), accountNumber(account) {
        message += ": " + accountNumber;
    }
    
    const std::string& getAccountNumber() const { return accountNumber; }
};

// ======================= EXCEPTION-SAFE BANK ACCOUNT =======================
class SafeBankAccount {
private:
    std::string accountNumber;
    double balance;
    std::vector<std::string> transactionHistory;
    
    void logTransaction(const std::string& transaction) {
        transactionHistory.push_back(transaction);
        std::cout << "📝 Transaction logged: " << transaction << std::endl;
    }
    
public:
    SafeBankAccount(const std::string& account, double initialBalance)
        : accountNumber(account), balance(initialBalance) {
        if (accountNumber.empty()) {
            throw InvalidAccountException("Empty account number");
        }
        if (initialBalance < 0) {
            throw std::invalid_argument("Initial balance cannot be negative");
        }
        std::cout << "🏦 Safe account created: " << accountNumber 
                  << " with balance $" << balance << std::endl;
    }
    
    void deposit(double amount) {
        if (amount <= 0) {
            throw std::invalid_argument("Deposit amount must be positive");
        }
        
        // Strong exception safety: either succeeds completely or leaves object unchanged
        try {
            double newBalance = balance + amount;
            std::string transaction = "Deposit: +$" + std::to_string(amount);
            
            // These operations might throw
            logTransaction(transaction);
            balance = newBalance; // Only update if logging succeeds
            
            std::cout << "✅ Deposited $" << amount << ". New balance: $" << balance << std::endl;
        } catch (...) {
            std::cout << "❌ Deposit failed for $" << amount << std::endl;
            throw; // Re-throw the exception
        }
    }
    
    void withdraw(double amount) {
        if (amount <= 0) {
            throw std::invalid_argument("Withdrawal amount must be positive");
        }
        
        if (amount > balance) {
            throw InsufficientFundsException(amount, balance);
        }
        
        // Strong exception safety
        try {
            double newBalance = balance - amount;
            std::string transaction = "Withdrawal: -$" + std::to_string(amount);
            
            logTransaction(transaction);
            balance = newBalance;
            
            std::cout << "✅ Withdrew $" << amount << ". New balance: $" << balance << std::endl;
        } catch (...) {
            std::cout << "❌ Withdrawal failed for $" << amount << std::endl;
            throw;
        }
    }
    
    void transfer(SafeBankAccount& toAccount, double amount) {
        if (amount <= 0) {
            throw std::invalid_argument("Transfer amount must be positive");
        }
        
        if (amount > balance) {
            throw InsufficientFundsException(amount, balance);
        }
        
        // Transaction safety: either both succeed or both fail
        std::cout << "🔄 Starting transfer of $" << amount 
                  << " to account " << toAccount.accountNumber << std::endl;
        
        try {
            // Withdraw from this account
            this->withdraw(amount);
            
            try {
                // Deposit to target account
                toAccount.deposit(amount);
                std::cout << "✅ Transfer completed successfully" << std::endl;
            } catch (...) {
                // Rollback: deposit back to this account
                std::cout << "🔄 Rolling back transfer..." << std::endl;
                this->deposit(amount);
                throw; // Re-throw the original exception
            }
        } catch (...) {
            std::cout << "❌ Transfer failed" << std::endl;
            throw;
        }
    }
    
    double getBalance() const noexcept { return balance; }
    const std::string& getAccountNumber() const noexcept { return accountNumber; }
    
    void printTransactionHistory() const noexcept {
        std::cout << "📋 Transaction history for " << accountNumber << ":" << std::endl;
        for (const auto& transaction : transactionHistory) {
            std::cout << "  " << transaction << std::endl;
        }
    }
};

// ======================= RAII AND EXCEPTION SAFETY =======================
class FileManager {
private:
    std::unique_ptr<std::ofstream> file;
    std::string filename;
    
public:
    FileManager(const std::string& name) : filename(name) {
        file = std::make_unique<std::ofstream>(filename);
        if (!file->is_open()) {
            throw std::runtime_error("Failed to open file: " + filename);
        }
        std::cout << "📁 File opened: " << filename << std::endl;
    }
    
    ~FileManager() {
        if (file && file->is_open()) {
            file->close();
            std::cout << "📁 File closed: " << filename << std::endl;
        }
    }
    
    // Delete copy constructor and assignment (RAII resource)
    FileManager(const FileManager&) = delete;
    FileManager& operator=(const FileManager&) = delete;
    
    // Move constructor
    FileManager(FileManager&& other) noexcept 
        : file(std::move(other.file)), filename(std::move(other.filename)) {}
    
    void write(const std::string& content) {
        if (!file || !file->is_open()) {
            throw std::runtime_error("File is not open for writing");
        }
        
        *file << content << std::endl;
        if (file->fail()) {
            throw std::runtime_error("Failed to write to file: " + filename);
        }
        
        std::cout << "✍️  Written to file: " << content << std::endl;
    }
    
    void flush() {
        if (file && file->is_open()) {
            file->flush();
            std::cout << "💾 File flushed: " << filename << std::endl;
        }
    }
};

// ======================= EXCEPTION SAFETY LEVELS =======================
class ExceptionSafetyDemo {
public:
    // Basic guarantee: object is in valid but unspecified state
    static void basicGuaranteeExample() {
        std::cout << "\n--- BASIC EXCEPTION SAFETY ---" << std::endl;
        
        std::vector<int> numbers = {1, 2, 3, 4, 5};
        std::cout << "Original vector size: " << numbers.size() << std::endl;
        
        try {
            // This might throw during reallocation
            numbers.reserve(1000000000); // Huge allocation that might fail
            numbers.push_back(6);
        } catch (const std::exception& e) {
            std::cout << "Exception caught: " << e.what() << std::endl;
            std::cout << "Vector size after exception: " << numbers.size() << std::endl;
            // Vector is still valid and usable
        }
    }
    
    // Strong guarantee: operation either succeeds or leaves object unchanged
    static void strongGuaranteeExample() {
        std::cout << "\n--- STRONG EXCEPTION SAFETY ---" << std::endl;
        
        try {
            SafeBankAccount account1("ACC001", 1000.0);
            SafeBankAccount account2("ACC002", 500.0);
            
            std::cout << "Before transfer - Account1: $" << account1.getBalance() 
                      << ", Account2: $" << account2.getBalance() << std::endl;
            
            // This will fail due to insufficient funds
            account1.transfer(account2, 1500.0);
            
        } catch (const InsufficientFundsException& e) {
            std::cout << "Transfer failed: " << e.what() << std::endl;
            // Accounts are in their original state
        }
    }
    
    // No-throw guarantee: operation never throws
    static void noThrowGuaranteeExample() noexcept {
        std::cout << "\n--- NO-THROW EXCEPTION SAFETY ---" << std::endl;
        
        try {
            SafeBankAccount account("ACC003", 750.0);
            
            // These operations are marked noexcept
            double balance = account.getBalance();
            const std::string& accNum = account.getAccountNumber();
            
            std::cout << "Account " << accNum << " has balance $" << balance << std::endl;
            
        } catch (...) {
            // This should never happen for noexcept operations
            std::cout << "Unexpected exception in noexcept operation!" << std::endl;
        }
    }
};

// ======================= NESTED TRY-CATCH EXAMPLE =======================
void processComplexOperation() {
    std::cout << "\n--- NESTED EXCEPTION HANDLING ---" << std::endl;
    
    try {
        SafeBankAccount account("ACC004", 2000.0);
        
        try {
            // File operations
            FileManager logFile("transaction_log.txt");
            logFile.write("Starting complex operation");
            
            try {
                // Banking operations
                account.deposit(500.0);
                account.withdraw(300.0);
                
                logFile.write("Banking operations completed");
                
                // Simulate an error
                throw std::runtime_error("Simulated processing error");
                
            } catch (const BankException& e) {
                std::cout << "Banking error: " << e.what() << std::endl;
                throw; // Re-throw to outer catch
            }
            
        } catch (const std::runtime_error& e) {
            std::cout << "Runtime error: " << e.what() << std::endl;
            // Handle file-related errors
            throw; // Re-throw to outermost catch
        }
        
    } catch (const std::exception& e) {
        std::cout << "Operation failed: " << e.what() << std::endl;
    } catch (...) {
        std::cout << "Unknown error occurred" << std::endl;
    }
}

// ======================= EXCEPTION SPECIFICATION EXAMPLES =======================
class ExceptionSpecificationDemo {
public:
    // Function that doesn't throw
    static int safeDivision(int a, int b) noexcept {
        if (b == 0) {
            std::cout << "Division by zero detected, returning 0" << std::endl;
            return 0;
        }
        return a / b;
    }
    
    // Function that might throw
    static double checkedDivision(double a, double b) {
        if (b == 0.0) {
            throw std::invalid_argument("Division by zero");
        }
        return a / b;
    }
    
    // Function with conditional noexcept
    template<typename T>
    static auto conditionalNoexcept(T&& value) noexcept(std::is_nothrow_move_constructible_v<T>) {
        return std::forward<T>(value);
    }
};

// ======================= DEMONSTRATION FUNCTION =======================
inline void demonstrateExceptionHandling() {
    std::cout << "\n===== EXCEPTION HANDLING DEMO =====\n" << std::endl;
    
    // Basic exception handling
    std::cout << "1. Basic Exception Handling:" << std::endl;
    try {
        SafeBankAccount account("ACC001", 1000.0);
        account.deposit(200.0);
        account.withdraw(1500.0); // This will throw
    } catch (const InsufficientFundsException& e) {
        std::cout << "Specific exception: " << e.what() << std::endl;
        std::cout << "Attempted: $" << e.getAttempted() 
                  << ", Available: $" << e.getAvailable() << std::endl;
    } catch (const BankException& e) {
        std::cout << "Bank exception: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Standard exception: " << e.what() << std::endl;
    }
    
    // Exception safety guarantees
    ExceptionSafetyDemo::basicGuaranteeExample();
    ExceptionSafetyDemo::strongGuaranteeExample();
    ExceptionSafetyDemo::noThrowGuaranteeExample();
    
    // Complex exception handling
    processComplexOperation();
    
    // Exception specifications
    std::cout << "\n2. Exception Specifications:" << std::endl;
    std::cout << "Safe division 10/0: " << ExceptionSpecificationDemo::safeDivision(10, 0) << std::endl;
    
    try {
        std::cout << "Checked division 10/0: ";
        double result = ExceptionSpecificationDemo::checkedDivision(10.0, 0.0);
        std::cout << result << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    // RAII demonstration
    std::cout << "\n3. RAII and Automatic Cleanup:" << std::endl;
    try {
        FileManager file("test_file.txt");
        file.write("First line");
        file.write("Second line");
        
        // Simulate an error
        throw std::runtime_error("Simulated error");
        
        file.write("This won't be written");
    } catch (const std::exception& e) {
        std::cout << "File operation failed: " << e.what() << std::endl;
        std::cout << "File was automatically closed due to RAII" << std::endl;
    }
    
    std::cout << "\n===== EXCEPTION HANDLING BEST PRACTICES =====\n" << std::endl;
    std::cout << "✅ Use RAII for automatic resource cleanup" << std::endl;
    std::cout << "✅ Throw by value, catch by reference" << std::endl;
    std::cout << "✅ Use specific exception types" << std::endl;
    std::cout << "✅ Provide strong exception safety when possible" << std::endl;
    std::cout << "✅ Use noexcept for functions that don't throw" << std::endl;
    std::cout << "✅ Clean up resources in destructors" << std::endl;
    std::cout << "❌ Don't catch exceptions you can't handle" << std::endl;
    std::cout << "❌ Don't throw exceptions from destructors" << std::endl;
    std::cout << "❌ Don't use exception specifications (except noexcept)" << std::endl;
}

#endif // EXCEPTION_HANDLING_HPP
