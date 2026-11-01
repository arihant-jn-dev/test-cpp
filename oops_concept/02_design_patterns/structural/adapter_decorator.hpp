#ifndef ADAPTER_DECORATOR_HPP
#define ADAPTER_DECORATOR_HPP

#include <iostream>
#include <memory>
#include <string>
#include <vector>

/**
 * ADAPTER & DECORATOR DESIGN PATTERNS
 * 
 * ADAPTER PATTERN:
 * - Allows incompatible interfaces to work together
 * - Wraps existing class with new interface
 * - Common in interviews: Legacy system integration, third-party libraries
 * 
 * DECORATOR PATTERN:
 * - Adds new functionality to objects dynamically
 * - Alternative to subclassing for extending functionality
 * - Common in interviews: GUI components, middleware, data processing
 */

// ======================= ADAPTER PATTERN =======================

// Legacy Payment System (Incompatible interface)
class LegacyPaymentGateway {
public:
    void makePayment(double amount, const std::string& currency) {
        std::cout << "🏛️  Legacy Gateway: Processing " << currency << " " << amount 
                  << " through old system" << std::endl;
        std::cout << "   Using legacy protocols..." << std::endl;
        std::cout << "   Payment processed successfully!" << std::endl;
    }
    
    bool checkStatus(const std::string& transactionId) {
        std::cout << "🏛️  Legacy Gateway: Checking status for " << transactionId << std::endl;
        return true;
    }
};

// Modern Payment Interface (Expected by new system)
class ModernPaymentInterface {
public:
    virtual ~ModernPaymentInterface() = default;
    virtual bool processPayment(double amount, const std::string& method) = 0;
    virtual std::string getTransactionStatus(const std::string& id) = 0;
    virtual std::string getPaymentType() const = 0;
};

// Adapter to make legacy system compatible with modern interface
class PaymentAdapter : public ModernPaymentInterface {
private:
    std::unique_ptr<LegacyPaymentGateway> legacyGateway;
    std::string currency;
    
public:
    PaymentAdapter(std::unique_ptr<LegacyPaymentGateway> legacy, const std::string& curr = "USD")
        : legacyGateway(std::move(legacy)), currency(curr) {}
    
    bool processPayment(double amount, const std::string& method) override {
        std::cout << "🔄 Adapter: Converting modern call to legacy format" << std::endl;
        std::cout << "   Method: " << method << " -> Currency: " << currency << std::endl;
        
        // Adapt the call to legacy interface
        legacyGateway->makePayment(amount, currency);
        return true;
    }
    
    std::string getTransactionStatus(const std::string& id) override {
        std::cout << "🔄 Adapter: Converting status request" << std::endl;
        bool status = legacyGateway->checkStatus(id);
        return status ? "SUCCESS" : "FAILED";
    }
    
    std::string getPaymentType() const override {
        return "Legacy Payment Gateway (Adapted)";
    }
};

// Modern Payment System
class ModernPaymentGateway : public ModernPaymentInterface {
public:
    bool processPayment(double amount, const std::string& method) override {
        std::cout << "💳 Modern Gateway: Processing $" << amount 
                  << " via " << method << std::endl;
        std::cout << "   Using REST APIs and secure protocols" << std::endl;
        std::cout << "   Payment successful!" << std::endl;
        return true;
    }
    
    std::string getTransactionStatus(const std::string& id) override {
        std::cout << "💳 Modern Gateway: Real-time status for " << id << std::endl;
        return "COMPLETED";
    }
    
    std::string getPaymentType() const override {
        return "Modern Payment Gateway";
    }
};

// Client code that works with modern interface
class PaymentProcessor {
private:
    std::unique_ptr<ModernPaymentInterface> gateway;
    
public:
    void setGateway(std::unique_ptr<ModernPaymentInterface> newGateway) {
        gateway = std::move(newGateway);
        std::cout << "🔧 Payment processor using: " << gateway->getPaymentType() << std::endl;
    }
    
    void processTransaction(double amount, const std::string& method, const std::string& txnId) {
        if (!gateway) {
            std::cout << "❌ No payment gateway configured!" << std::endl;
            return;
        }
        
        std::cout << "\n💰 Processing Transaction ID: " << txnId << std::endl;
        bool success = gateway->processPayment(amount, method);
        
        if (success) {
            std::string status = gateway->getTransactionStatus(txnId);
            std::cout << "✅ Transaction Status: " << status << std::endl;
        }
    }
};

// ======================= DECORATOR PATTERN =======================

// Base Coffee Interface
class Coffee {
public:
    virtual ~Coffee() = default;
    virtual std::string getDescription() const = 0;
    virtual double getCost() const = 0;
    virtual void prepare() const = 0;
};

// Concrete Coffee Implementation
class SimpleCoffee : public Coffee {
public:
    std::string getDescription() const override {
        return "Simple Coffee";
    }
    
    double getCost() const override {
        return 2.0;
    }
    
    void prepare() const override {
        std::cout << "☕ Brewing simple black coffee..." << std::endl;
    }
};

class Espresso : public Coffee {
public:
    std::string getDescription() const override {
        return "Espresso";
    }
    
    double getCost() const override {
        return 3.0;
    }
    
    void prepare() const override {
        std::cout << "☕ Preparing rich espresso shot..." << std::endl;
    }
};

// Base Decorator
class CoffeeDecorator : public Coffee {
protected:
    std::unique_ptr<Coffee> coffee;
    
public:
    CoffeeDecorator(std::unique_ptr<Coffee> c) : coffee(std::move(c)) {}
    
    std::string getDescription() const override {
        return coffee->getDescription();
    }
    
    double getCost() const override {
        return coffee->getCost();
    }
    
    void prepare() const override {
        coffee->prepare();
    }
};

// Concrete Decorators
class MilkDecorator : public CoffeeDecorator {
public:
    MilkDecorator(std::unique_ptr<Coffee> c) : CoffeeDecorator(std::move(c)) {}
    
    std::string getDescription() const override {
        return coffee->getDescription() + " + Milk";
    }
    
    double getCost() const override {
        return coffee->getCost() + 0.5;
    }
    
    void prepare() const override {
        coffee->prepare();
        std::cout << "🥛 Adding creamy steamed milk..." << std::endl;
    }
};

class SugarDecorator : public CoffeeDecorator {
public:
    SugarDecorator(std::unique_ptr<Coffee> c) : CoffeeDecorator(std::move(c)) {}
    
    std::string getDescription() const override {
        return coffee->getDescription() + " + Sugar";
    }
    
    double getCost() const override {
        return coffee->getCost() + 0.2;
    }
    
    void prepare() const override {
        coffee->prepare();
        std::cout << "🍯 Adding sweet sugar..." << std::endl;
    }
};

class VanillaDecorator : public CoffeeDecorator {
public:
    VanillaDecorator(std::unique_ptr<Coffee> c) : CoffeeDecorator(std::move(c)) {}
    
    std::string getDescription() const override {
        return coffee->getDescription() + " + Vanilla";
    }
    
    double getCost() const override {
        return coffee->getCost() + 0.7;
    }
    
    void prepare() const override {
        coffee->prepare();
        std::cout << "🌟 Adding aromatic vanilla flavor..." << std::endl;
    }
};

class WhippedCreamDecorator : public CoffeeDecorator {
public:
    WhippedCreamDecorator(std::unique_ptr<Coffee> c) : CoffeeDecorator(std::move(c)) {}
    
    std::string getDescription() const override {
        return coffee->getDescription() + " + Whipped Cream";
    }
    
    double getCost() const override {
        return coffee->getCost() + 1.0;
    }
    
    void prepare() const override {
        coffee->prepare();
        std::cout << "🍦 Topping with fluffy whipped cream..." << std::endl;
    }
};

// ======================= TEXT PROCESSING DECORATOR EXAMPLE =======================
class TextProcessor {
public:
    virtual ~TextProcessor() = default;
    virtual std::string process(const std::string& text) = 0;
    virtual std::string getProcessingInfo() const = 0;
};

class PlainTextProcessor : public TextProcessor {
public:
    std::string process(const std::string& text) override {
        return text;
    }
    
    std::string getProcessingInfo() const override {
        return "Plain Text";
    }
};

class TextProcessorDecorator : public TextProcessor {
protected:
    std::unique_ptr<TextProcessor> processor;
    
public:
    TextProcessorDecorator(std::unique_ptr<TextProcessor> p) : processor(std::move(p)) {}
    
    std::string process(const std::string& text) override {
        return processor->process(text);
    }
    
    std::string getProcessingInfo() const override {
        return processor->getProcessingInfo();
    }
};

class UpperCaseDecorator : public TextProcessorDecorator {
public:
    UpperCaseDecorator(std::unique_ptr<TextProcessor> p) : TextProcessorDecorator(std::move(p)) {}
    
    std::string process(const std::string& text) override {
        std::string processed = processor->process(text);
        std::transform(processed.begin(), processed.end(), processed.begin(), ::toupper);
        return processed;
    }
    
    std::string getProcessingInfo() const override {
        return processor->getProcessingInfo() + " -> UpperCase";
    }
};

class EncryptionDecorator : public TextProcessorDecorator {
private:
    int shift;
    
public:
    EncryptionDecorator(std::unique_ptr<TextProcessor> p, int s = 3) 
        : TextProcessorDecorator(std::move(p)), shift(s) {}
    
    std::string process(const std::string& text) override {
        std::string processed = processor->process(text);
        std::string encrypted;
        
        for (char c : processed) {
            if (std::isalpha(c)) {
                char base = std::isupper(c) ? 'A' : 'a';
                encrypted += static_cast<char>((c - base + shift) % 26 + base);
            } else {
                encrypted += c;
            }
        }
        return encrypted;
    }
    
    std::string getProcessingInfo() const override {
        return processor->getProcessingInfo() + " -> Encrypted(shift=" + std::to_string(shift) + ")";
    }
};

class CompressionDecorator : public TextProcessorDecorator {
public:
    CompressionDecorator(std::unique_ptr<TextProcessor> p) : TextProcessorDecorator(std::move(p)) {}
    
    std::string process(const std::string& text) override {
        std::string processed = processor->process(text);
        // Simulate compression by removing duplicate spaces
        std::string compressed;
        bool prevSpace = false;
        
        for (char c : processed) {
            if (c == ' ') {
                if (!prevSpace) {
                    compressed += c;
                    prevSpace = true;
                }
            } else {
                compressed += c;
                prevSpace = false;
            }
        }
        return compressed;
    }
    
    std::string getProcessingInfo() const override {
        return processor->getProcessingInfo() + " -> Compressed";
    }
};

// ======================= DEMONSTRATION FUNCTIONS =======================
inline void demonstrateAdapterDecorator() {
    std::cout << "\n===== ADAPTER & DECORATOR PATTERNS DEMO =====\n" << std::endl;
    
    // Adapter Pattern Demo
    std::cout << "1. ADAPTER PATTERN - Payment System Integration:" << std::endl;
    PaymentProcessor processor;
    
    // Use modern payment gateway
    std::cout << "\n--- Using Modern Payment Gateway ---" << std::endl;
    processor.setGateway(std::make_unique<ModernPaymentGateway>());
    processor.processTransaction(100.50, "Credit Card", "TXN-001");
    
    // Integrate legacy system using adapter
    std::cout << "\n--- Integrating Legacy System with Adapter ---" << std::endl;
    auto legacyGateway = std::make_unique<LegacyPaymentGateway>();
    auto adapter = std::make_unique<PaymentAdapter>(std::move(legacyGateway), "USD");
    processor.setGateway(std::move(adapter));
    processor.processTransaction(250.75, "Debit Card", "TXN-002");
    
    // Decorator Pattern Demo
    std::cout << "\n2. DECORATOR PATTERN - Coffee Shop:" << std::endl;
    
    // Simple coffee
    std::cout << "\n--- Simple Coffee ---" << std::endl;
    auto coffee1 = std::make_unique<SimpleCoffee>();
    std::cout << "Order: " << coffee1->getDescription() << std::endl;
    std::cout << "Cost: $" << coffee1->getCost() << std::endl;
    coffee1->prepare();
    
    // Decorated coffee with multiple additions
    std::cout << "\n--- Decorated Coffee (Espresso + Milk + Sugar + Vanilla) ---" << std::endl;
    auto coffee2 = std::make_unique<Espresso>();
    coffee2 = std::make_unique<MilkDecorator>(std::move(coffee2));
    coffee2 = std::make_unique<SugarDecorator>(std::move(coffee2));
    coffee2 = std::make_unique<VanillaDecorator>(std::move(coffee2));
    
    std::cout << "Order: " << coffee2->getDescription() << std::endl;
    std::cout << "Cost: $" << coffee2->getCost() << std::endl;
    coffee2->prepare();
    
    // Luxury coffee with all decorations
    std::cout << "\n--- Luxury Coffee (All Decorations) ---" << std::endl;
    auto coffee3 = std::make_unique<SimpleCoffee>();
    coffee3 = std::make_unique<MilkDecorator>(std::move(coffee3));
    coffee3 = std::make_unique<SugarDecorator>(std::move(coffee3));
    coffee3 = std::make_unique<VanillaDecorator>(std::move(coffee3));
    coffee3 = std::make_unique<WhippedCreamDecorator>(std::move(coffee3));
    
    std::cout << "Order: " << coffee3->getDescription() << std::endl;
    std::cout << "Cost: $" << coffee3->getCost() << std::endl;
    coffee3->prepare();
    
    // Text Processing Decorator Demo
    std::cout << "\n3. DECORATOR PATTERN - Text Processing Pipeline:" << std::endl;
    std::string originalText = "Hello World! This is a test message.";
    std::cout << "Original text: \"" << originalText << "\"" << std::endl;
    
    // Plain processing
    std::cout << "\n--- Plain Text Processing ---" << std::endl;
    auto processor1 = std::make_unique<PlainTextProcessor>();
    std::string result1 = processor1->process(originalText);
    std::cout << "Processing: " << processor1->getProcessingInfo() << std::endl;
    std::cout << "Result: \"" << result1 << "\"" << std::endl;
    
    // Multiple decorators
    std::cout << "\n--- Multiple Text Decorators ---" << std::endl;
    auto processor2 = std::make_unique<PlainTextProcessor>();
    processor2 = std::make_unique<UpperCaseDecorator>(std::move(processor2));
    processor2 = std::make_unique<CompressionDecorator>(std::move(processor2));
    processor2 = std::make_unique<EncryptionDecorator>(std::move(processor2), 5);
    
    std::string result2 = processor2->process(originalText);
    std::cout << "Processing: " << processor2->getProcessingInfo() << std::endl;
    std::cout << "Result: \"" << result2 << "\"" << std::endl;
    
    // Different decorator order
    std::cout << "\n--- Different Decorator Order ---" << std::endl;
    auto processor3 = std::make_unique<PlainTextProcessor>();
    processor3 = std::make_unique<EncryptionDecorator>(std::move(processor3), 2);
    processor3 = std::make_unique<UpperCaseDecorator>(std::move(processor3));
    processor3 = std::make_unique<CompressionDecorator>(std::move(processor3));
    
    std::string result3 = processor3->process(originalText);
    std::cout << "Processing: " << processor3->getProcessingInfo() << std::endl;
    std::cout << "Result: \"" << result3 << "\"" << std::endl;
}

#endif // ADAPTER_DECORATOR_HPP
