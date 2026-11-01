#ifndef ADVANCED_PATTERNS_HPP
#define ADVANCED_PATTERNS_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <mutex>
#include <functional>
#include <type_traits>

#include "../02_design_patterns/creational/factory.hpp"

/**
 * ===============================================
 * ADVANCED PATTERN VARIANTS
 * ===============================================
 *
 * Moved here from 02_design_patterns/. These variants use mutexes, templates,
 * std::function and lambdas. The plain versions left in 02_design_patterns/
 * are what you should write in an LLD round.
 *
 * - Singleton with a raw pointer and a mutex (note: the instance is never
 *   deleted; the static-local Logger in singleton.hpp avoids that)
 * - Registration-based factory (std::function + template + if constexpr)
 * - Observer built on std::function and lambdas
 * - Event system: map from event type to a list of lambda listeners
 */

namespace AdvancedCpp {

// ======================= CLASSIC SINGLETON =======================
class DatabaseConnection {
private:
    static DatabaseConnection* instance;
    static std::mutex mutex_;
    std::string connection_string;
    
    // Private constructor prevents external instantiation
    DatabaseConnection(const std::string& conn_str = "localhost:3306") 
        : connection_string(conn_str) {
        std::cout << "Database connection created to: " << conn_str << std::endl;
    }
    
    // Delete copy constructor and assignment operator
    DatabaseConnection(const DatabaseConnection&) = delete;
    DatabaseConnection& operator=(const DatabaseConnection&) = delete;
    
public:
    // Thread-safe singleton instance
    static DatabaseConnection* getInstance(const std::string& conn_str = "localhost:3306") {
        std::lock_guard<std::mutex> lock(mutex_);
        if (instance == nullptr) {
            instance = new DatabaseConnection(conn_str);
        }
        return instance;
    }
    
    void query(const std::string& sql) {
        std::cout << "Executing query on " << connection_string << ": " << sql << std::endl;
    }
    
    void close() {
        std::cout << "Closing connection to " << connection_string << std::endl;
    }
    
    ~DatabaseConnection() {
        std::cout << "Database connection destroyed" << std::endl;
    }
};

// Static member definitions
DatabaseConnection* DatabaseConnection::instance = nullptr;
std::mutex DatabaseConnection::mutex_;

// ======================= REGISTRATION-BASED FACTORY (ADVANCED) =======================
class AdvancedShapeFactory {
private:
    using Creator = std::function<std::unique_ptr<Shape>(double, double)>;
    static std::map<std::string, Creator> creators;
    
public:
    template<typename T>
    static void registerShape(const std::string& name) {
        creators[name] = [](double p1, double p2) -> std::unique_ptr<Shape> {
            if constexpr (std::is_same_v<T, Circle>) {
                return std::make_unique<T>(p1);
            } else {
                return std::make_unique<T>(p1, p2);
            }
        };
    }
    
    static std::unique_ptr<Shape> create(const std::string& type, double param1, double param2 = 0) {
        auto it = creators.find(type);
        if (it != creators.end()) {
            return it->second(param1, param2);
        }
        return nullptr;
    }
    
    static void listAvailableShapes() {
        std::cout << "Available shapes: ";
        for (const auto& pair : creators) {
            std::cout << pair.first << " ";
        }
        std::cout << std::endl;
    }
};

// Static member definition
std::map<std::string, AdvancedShapeFactory::Creator> AdvancedShapeFactory::creators;

// ======================= MODERN C++ OBSERVER (FUNCTION-BASED) =======================
template<typename T>
class ModernSubject {
private:
    std::vector<std::function<void(const T&)>> observers;
    T data;
    
public:
    void subscribe(std::function<void(const T&)> observer) {
        observers.push_back(observer);
    }
    
    void unsubscribe(size_t index) {
        if (index < observers.size()) {
            observers.erase(observers.begin() + index);
        }
    }
    
    void notify() {
        for (const auto& observer : observers) {
            observer(data);
        }
    }
    
    void setData(const T& newData) {
        data = newData;
        notify();
    }
    
    const T& getData() const {
        return data;
    }
};

// ======================= EVENT SYSTEM EXAMPLE =======================
class EventSystem {
public:
    enum class EventType {
        USER_LOGIN,
        USER_LOGOUT,
        ORDER_PLACED,
        PAYMENT_SUCCESS
    };
    
private:
    std::map<EventType, std::vector<std::function<void(const std::string&)>>> listeners;
    
public:
    void addEventListener(EventType type, std::function<void(const std::string&)> listener) {
        listeners[type].push_back(listener);
    }
    
    void triggerEvent(EventType type, const std::string& data) {
        std::string eventName;
        switch(type) {
            case EventType::USER_LOGIN: eventName = "USER_LOGIN"; break;
            case EventType::USER_LOGOUT: eventName = "USER_LOGOUT"; break;
            case EventType::ORDER_PLACED: eventName = "ORDER_PLACED"; break;
            case EventType::PAYMENT_SUCCESS: eventName = "PAYMENT_SUCCESS"; break;
        }
        
        std::cout << "🎯 Event triggered: " << eventName << " with data: " << data << std::endl;
        
        auto it = listeners.find(type);
        if (it != listeners.end()) {
            for (const auto& listener : it->second) {
                listener(data);
            }
        }
    }
};

} // namespace AdvancedCpp

// ======================= DEMONSTRATION FUNCTION =======================
inline void demonstrateAdvancedPatterns() {
    std::cout << "\n===== ADVANCED PATTERN VARIANTS DEMO =====\n" << std::endl;

    std::cout << "1. Singleton with pointer + mutex (DatabaseConnection):" << std::endl;
    auto* db1 = AdvancedCpp::DatabaseConnection::getInstance("mysql://localhost:3306");
    auto* db2 = AdvancedCpp::DatabaseConnection::getInstance("postgres://localhost:5432"); // Same instance!
    std::cout << "db1 == db2: " << (db1 == db2 ? "true" : "false") << std::endl;
    db1->query("SELECT * FROM users");

    std::cout << "\n2. Registration-based Factory:" << std::endl;
    AdvancedCpp::AdvancedShapeFactory::registerShape<Circle>("circle");
    AdvancedCpp::AdvancedShapeFactory::registerShape<Rectangle>("rectangle");
    AdvancedCpp::AdvancedShapeFactory::registerShape<Triangle>("triangle");
    AdvancedCpp::AdvancedShapeFactory::listAvailableShapes();
    auto advCircle = AdvancedCpp::AdvancedShapeFactory::create("circle", 3.0);
    if (advCircle) {
        advCircle->draw();
        std::cout << "Area: " << advCircle->getArea() << std::endl;
    }

    std::cout << "\n3. Observer with Lambdas:" << std::endl;
    AdvancedCpp::ModernSubject<std::string> modernSubject;
    modernSubject.subscribe([](const std::string& data) {
        std::cout << "Lambda Observer 1: Received " << data << std::endl;
    });
    modernSubject.subscribe([](const std::string& data) {
        std::cout << "Lambda Observer 2: Processing " << data << std::endl;
    });
    modernSubject.setData("Hello World");

    std::cout << "\n4. Event System:" << std::endl;
    AdvancedCpp::EventSystem eventSystem;
    eventSystem.addEventListener(AdvancedCpp::EventSystem::EventType::USER_LOGIN, [](const std::string& data) {
        std::cout << "   Analytics: User logged in - " << data << std::endl;
    });
    eventSystem.addEventListener(AdvancedCpp::EventSystem::EventType::ORDER_PLACED, [](const std::string& data) {
        std::cout << "   Email: Sending confirmation for order - " << data << std::endl;
    });
    eventSystem.triggerEvent(AdvancedCpp::EventSystem::EventType::USER_LOGIN, "john.doe@email.com");
    eventSystem.triggerEvent(AdvancedCpp::EventSystem::EventType::ORDER_PLACED, "ORD-12345");
}

#endif // ADVANCED_PATTERNS_HPP
