#ifndef STRATEGY_HPP
#define STRATEGY_HPP

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>

/**
 * STRATEGY DESIGN PATTERN
 * - Defines family of algorithms, encapsulates each one, makes them interchangeable
 * - Algorithm varies independently from clients that use it
 * - Common in interviews: Payment systems, sorting algorithms, compression
 */

// ======================= PAYMENT STRATEGY EXAMPLE =======================
class PaymentStrategy {
public:
    virtual ~PaymentStrategy() = default;
    virtual bool pay(double amount) = 0;
    virtual std::string getPaymentMethod() const = 0;
    virtual void displayPaymentDetails() const = 0;
};

class CreditCardPayment : public PaymentStrategy {
private:
    std::string cardNumber;
    std::string holderName;
    std::string expiryDate;
    
public:
    CreditCardPayment(const std::string& cardNum, const std::string& name, const std::string& expiry)
        : cardNumber(cardNum), holderName(name), expiryDate(expiry) {}
    
    bool pay(double amount) override {
        std::cout << "💳 Processing credit card payment of $" << amount << std::endl;
        std::cout << "   Card: ****" << cardNumber.substr(cardNumber.length() - 4) << std::endl;
        std::cout << "   Holder: " << holderName << std::endl;
        std::cout << "   Validating card details..." << std::endl;
        std::cout << "   Payment successful!" << std::endl;
        return true;
    }
    
    std::string getPaymentMethod() const override {
        return "Credit Card";
    }
    
    void displayPaymentDetails() const override {
        std::cout << "Credit Card ending in " << cardNumber.substr(cardNumber.length() - 4)
                  << " (Expires: " << expiryDate << ")" << std::endl;
    }
};

class PayPalPayment : public PaymentStrategy {
private:
    std::string email;
    std::string password;
    
public:
    PayPalPayment(const std::string& userEmail, const std::string& userPassword)
        : email(userEmail), password(userPassword) {}
    
    bool pay(double amount) override {
        std::cout << "🟦 Processing PayPal payment of $" << amount << std::endl;
        std::cout << "   Email: " << email << std::endl;
        std::cout << "   Authenticating with PayPal..." << std::endl;
        std::cout << "   Payment authorized and completed!" << std::endl;
        return true;
    }
    
    std::string getPaymentMethod() const override {
        return "PayPal";
    }
    
    void displayPaymentDetails() const override {
        std::cout << "PayPal account: " << email << std::endl;
    }
};

class BankTransferPayment : public PaymentStrategy {
private:
    std::string accountNumber;
    std::string routingNumber;
    std::string bankName;
    
public:
    BankTransferPayment(const std::string& account, const std::string& routing, const std::string& bank)
        : accountNumber(account), routingNumber(routing), bankName(bank) {}
    
    bool pay(double amount) override {
        std::cout << "🏦 Processing bank transfer of $" << amount << std::endl;
        std::cout << "   Bank: " << bankName << std::endl;
        std::cout << "   Account: ****" << accountNumber.substr(accountNumber.length() - 4) << std::endl;
        std::cout << "   Initiating transfer..." << std::endl;
        std::cout << "   Transfer scheduled successfully!" << std::endl;
        return true;
    }
    
    std::string getPaymentMethod() const override {
        return "Bank Transfer";
    }
    
    void displayPaymentDetails() const override {
        std::cout << "Bank Transfer from " << bankName 
                  << " (Account: ****" << accountNumber.substr(accountNumber.length() - 4) << ")" << std::endl;
    }
};

class ShoppingCart {
private:
    std::vector<std::pair<std::string, double>> items;
    std::unique_ptr<PaymentStrategy> paymentStrategy;
    
public:
    void addItem(const std::string& item, double price) {
        items.emplace_back(item, price);
        std::cout << "Added " << item << " ($" << price << ") to cart" << std::endl;
    }
    
    void setPaymentStrategy(std::unique_ptr<PaymentStrategy> strategy) {
        paymentStrategy = std::move(strategy);
        std::cout << "Payment method set to: " << paymentStrategy->getPaymentMethod() << std::endl;
    }
    
    double calculateTotal() const {
        double total = 0;
        for (const auto& item : items) {
            total += item.second;
        }
        return total;
    }
    
    void displayCart() const {
        std::cout << "\n🛒 Shopping Cart:" << std::endl;
        for (const auto& item : items) {
            std::cout << "   " << item.first << " - $" << item.second << std::endl;
        }
        std::cout << "   Total: $" << calculateTotal() << std::endl;
    }
    
    bool checkout() {
        if (!paymentStrategy) {
            std::cout << "❌ No payment method selected!" << std::endl;
            return false;
        }
        
        displayCart();
        std::cout << "\nProcessing checkout..." << std::endl;
        paymentStrategy->displayPaymentDetails();
        
        double total = calculateTotal();
        return paymentStrategy->pay(total);
    }
};

// ======================= SORTING STRATEGY EXAMPLE =======================
template<typename T>
class SortStrategy {
public:
    virtual ~SortStrategy() = default;
    virtual void sort(std::vector<T>& data) = 0;
    virtual std::string getAlgorithmName() const = 0;
};

template<typename T>
class BubbleSort : public SortStrategy<T> {
public:
    void sort(std::vector<T>& data) override {
        std::cout << "Performing Bubble Sort..." << std::endl;
        size_t n = data.size();
        for (size_t i = 0; i < n - 1; i++) {
            for (size_t j = 0; j < n - i - 1; j++) {
                if (data[j] > data[j + 1]) {
                    std::swap(data[j], data[j + 1]);
                }
            }
        }
    }
    
    std::string getAlgorithmName() const override {
        return "Bubble Sort";
    }
};

template<typename T>
class QuickSort : public SortStrategy<T> {
private:
    void quickSortHelper(std::vector<T>& data, int low, int high) {
        if (low < high) {
            int pi = partition(data, low, high);
            quickSortHelper(data, low, pi - 1);
            quickSortHelper(data, pi + 1, high);
        }
    }
    
    int partition(std::vector<T>& data, int low, int high) {
        T pivot = data[high];
        int i = (low - 1);
        
        for (int j = low; j <= high - 1; j++) {
            if (data[j] < pivot) {
                i++;
                std::swap(data[i], data[j]);
            }
        }
        std::swap(data[i + 1], data[high]);
        return (i + 1);
    }
    
public:
    void sort(std::vector<T>& data) override {
        std::cout << "Performing Quick Sort..." << std::endl;
        quickSortHelper(data, 0, static_cast<int>(data.size()) - 1);
    }
    
    std::string getAlgorithmName() const override {
        return "Quick Sort";
    }
};

template<typename T>
class STLSort : public SortStrategy<T> {
public:
    void sort(std::vector<T>& data) override {
        std::cout << "Performing STL Sort (typically IntroSort)..." << std::endl;
        std::sort(data.begin(), data.end());
    }
    
    std::string getAlgorithmName() const override {
        return "STL Sort";
    }
};

template<typename T>
class SortContext {
private:
    std::unique_ptr<SortStrategy<T>> strategy;
    
public:
    void setStrategy(std::unique_ptr<SortStrategy<T>> newStrategy) {
        strategy = std::move(newStrategy);
    }
    
    void performSort(std::vector<T>& data) {
        if (!strategy) {
            std::cout << "No sorting strategy set!" << std::endl;
            return;
        }
        
        std::cout << "Using " << strategy->getAlgorithmName() << std::endl;
        auto start = std::chrono::high_resolution_clock::now();
        strategy->sort(data);
        auto end = std::chrono::high_resolution_clock::now();
        
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "Sort completed in " << duration.count() << " microseconds" << std::endl;
    }
};

// ======================= COMPRESSION STRATEGY EXAMPLE =======================
class CompressionStrategy {
public:
    virtual ~CompressionStrategy() = default;
    virtual std::string compress(const std::string& data) = 0;
    virtual std::string decompress(const std::string& compressedData) = 0;
    virtual std::string getCompressionType() const = 0;
};

class ZipCompression : public CompressionStrategy {
public:
    std::string compress(const std::string& data) override {
        std::cout << "🗜️  Compressing with ZIP algorithm..." << std::endl;
        // Simulate compression
        std::string compressed = "[ZIP]" + data + "[/ZIP]";
        std::cout << "   Original size: " << data.length() << " bytes" << std::endl;
        std::cout << "   Compressed size: " << compressed.length() << " bytes" << std::endl;
        return compressed;
    }
    
    std::string decompress(const std::string& compressedData) override {
        std::cout << "📂 Decompressing ZIP data..." << std::endl;
        // Simulate decompression
        if (compressedData.substr(0, 5) == "[ZIP]" && 
            compressedData.substr(compressedData.length() - 6) == "[/ZIP]") {
            return compressedData.substr(5, compressedData.length() - 11);
        }
        return compressedData;
    }
    
    std::string getCompressionType() const override {
        return "ZIP";
    }
};

class RARCompression : public CompressionStrategy {
public:
    std::string compress(const std::string& data) override {
        std::cout << "🗜️  Compressing with RAR algorithm..." << std::endl;
        std::string compressed = "[RAR]" + data + "[/RAR]";
        std::cout << "   Original size: " << data.length() << " bytes" << std::endl;
        std::cout << "   Compressed size: " << compressed.length() << " bytes" << std::endl;
        return compressed;
    }
    
    std::string decompress(const std::string& compressedData) override {
        std::cout << "📂 Decompressing RAR data..." << std::endl;
        if (compressedData.substr(0, 5) == "[RAR]" && 
            compressedData.substr(compressedData.length() - 6) == "[/RAR]") {
            return compressedData.substr(5, compressedData.length() - 11);
        }
        return compressedData;
    }
    
    std::string getCompressionType() const override {
        return "RAR";
    }
};

class CompressionContext {
private:
    std::unique_ptr<CompressionStrategy> strategy;
    
public:
    void setCompressionStrategy(std::unique_ptr<CompressionStrategy> newStrategy) {
        strategy = std::move(newStrategy);
        std::cout << "Compression method set to: " << strategy->getCompressionType() << std::endl;
    }
    
    std::string compressFile(const std::string& data) {
        if (!strategy) {
            std::cout << "No compression strategy set!" << std::endl;
            return data;
        }
        return strategy->compress(data);
    }
    
    std::string decompressFile(const std::string& compressedData) {
        if (!strategy) {
            std::cout << "No compression strategy set!" << std::endl;
            return compressedData;
        }
        return strategy->decompress(compressedData);
    }
};

// ======================= DEMONSTRATION FUNCTIONS =======================
inline void demonstrateStrategy() {
    std::cout << "\n===== STRATEGY PATTERN DEMO =====\n" << std::endl;
    
    // Payment Strategy Example
    std::cout << "1. Payment Strategy Example:" << std::endl;
    ShoppingCart cart;
    
    cart.addItem("Laptop", 999.99);
    cart.addItem("Mouse", 29.99);
    cart.addItem("Keyboard", 79.99);
    
    // Try different payment methods
    std::cout << "\n--- Paying with Credit Card ---" << std::endl;
    cart.setPaymentStrategy(std::make_unique<CreditCardPayment>("1234567890123456", "John Doe", "12/25"));
    cart.checkout();
    
    std::cout << "\n--- Changing to PayPal ---" << std::endl;
    cart.setPaymentStrategy(std::make_unique<PayPalPayment>("john.doe@email.com", "password123"));
    cart.checkout();
    
    // Sorting Strategy Example
    std::cout << "\n2. Sorting Strategy Example:" << std::endl;
    std::vector<int> data1 = {64, 34, 25, 12, 22, 11, 90};
    std::vector<int> data2 = data1;
    std::vector<int> data3 = data1;
    
    SortContext<int> sortContext;
    
    std::cout << "Original data: ";
    for (int num : data1) std::cout << num << " ";
    std::cout << std::endl;
    
    // Bubble Sort
    std::cout << "\n--- Using Bubble Sort ---" << std::endl;
    sortContext.setStrategy(std::make_unique<BubbleSort<int>>());
    sortContext.performSort(data1);
    std::cout << "Sorted: ";
    for (int num : data1) std::cout << num << " ";
    std::cout << std::endl;
    
    // Quick Sort
    std::cout << "\n--- Using Quick Sort ---" << std::endl;
    sortContext.setStrategy(std::make_unique<QuickSort<int>>());
    sortContext.performSort(data2);
    std::cout << "Sorted: ";
    for (int num : data2) std::cout << num << " ";
    std::cout << std::endl;
    
    // STL Sort
    std::cout << "\n--- Using STL Sort ---" << std::endl;
    sortContext.setStrategy(std::make_unique<STLSort<int>>());
    sortContext.performSort(data3);
    std::cout << "Sorted: ";
    for (int num : data3) std::cout << num << " ";
    std::cout << std::endl;
    
    // Compression Strategy Example
    std::cout << "\n3. Compression Strategy Example:" << std::endl;
    CompressionContext compressor;
    std::string originalData = "This is a sample text file that needs to be compressed for storage efficiency.";
    
    std::cout << "Original data: " << originalData << std::endl;
    
    // ZIP Compression
    std::cout << "\n--- Using ZIP Compression ---" << std::endl;
    compressor.setCompressionStrategy(std::make_unique<ZipCompression>());
    std::string zipCompressed = compressor.compressFile(originalData);
    std::cout << "Compressed: " << zipCompressed << std::endl;
    std::string zipDecompressed = compressor.decompressFile(zipCompressed);
    std::cout << "Decompressed: " << zipDecompressed << std::endl;
    
    // RAR Compression
    std::cout << "\n--- Using RAR Compression ---" << std::endl;
    compressor.setCompressionStrategy(std::make_unique<RARCompression>());
    std::string rarCompressed = compressor.compressFile(originalData);
    std::cout << "Compressed: " << rarCompressed << std::endl;
    std::string rarDecompressed = compressor.decompressFile(rarCompressed);
    std::cout << "Decompressed: " << rarDecompressed << std::endl;
}

#endif // STRATEGY_HPP
