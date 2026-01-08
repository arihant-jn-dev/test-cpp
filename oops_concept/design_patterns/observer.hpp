#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>
#include <functional>

/**
 * OBSERVER DESIGN PATTERN
 * - Defines one-to-many dependency between objects
 * - When subject changes state, all observers are notified
 * - Common in interviews: Event systems, MVC, notifications
 */

// ======================= CLASSIC OBSERVER PATTERN =======================
class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(const std::string& message) = 0;
    virtual std::string getName() const = 0;
};

class Subject {
private:
    std::vector<Observer*> observers;
    std::string state;
    
public:
    virtual ~Subject() = default;
    
    void attach(Observer* observer) {
        observers.push_back(observer);
        std::cout << "Observer " << observer->getName() << " attached" << std::endl;
    }
    
    void detach(Observer* observer) {
        auto it = std::find(observers.begin(), observers.end(), observer);
        if (it != observers.end()) {
            std::cout << "Observer " << observer->getName() << " detached" << std::endl;
            observers.erase(it);
        }
    }
    
    void notify() {
        std::cout << "Notifying " << observers.size() << " observers..." << std::endl;
        for (auto* observer : observers) {
            observer->update(state);
        }
    }
    
    void setState(const std::string& newState) {
        std::cout << "Subject state changed to: " << newState << std::endl;
        state = newState;
        notify();
    }
    
    std::string getState() const {
        return state;
    }
};

// Concrete Observers
class EmailNotifier : public Observer {
private:
    std::string email;
    
public:
    EmailNotifier(const std::string& emailAddr) : email(emailAddr) {}
    
    void update(const std::string& message) override {
        std::cout << "📧 Email sent to " << email << ": " << message << std::endl;
    }
    
    std::string getName() const override {
        return "EmailNotifier(" + email + ")";
    }
};

class SMSNotifier : public Observer {
private:
    std::string phoneNumber;
    
public:
    SMSNotifier(const std::string& phone) : phoneNumber(phone) {}
    
    void update(const std::string& message) override {
        std::cout << "📱 SMS sent to " << phoneNumber << ": " << message << std::endl;
    }
    
    std::string getName() const override {
        return "SMSNotifier(" + phoneNumber + ")";
    }
};

class PushNotifier : public Observer {
private:
    std::string deviceId;
    
public:
    PushNotifier(const std::string& device) : deviceId(device) {}
    
    void update(const std::string& message) override {
        std::cout << "🔔 Push notification to " << deviceId << ": " << message << std::endl;
    }
    
    std::string getName() const override {
        return "PushNotifier(" + deviceId + ")";
    }
};

// ======================= NEWS AGENCY EXAMPLE =======================
class NewsAgency : public Subject {
private:
    std::string latestNews;
    
public:
    void publishNews(const std::string& news) {
        latestNews = news;
        setState("Breaking News: " + news);
    }
    
    std::string getLatestNews() const {
        return latestNews;
    }
};

class NewsChannel : public Observer {
private:
    std::string channelName;
    
public:
    NewsChannel(const std::string& name) : channelName(name) {}
    
    void update(const std::string& message) override {
        std::cout << "📺 " << channelName << " broadcasting: " << message << std::endl;
    }
    
    std::string getName() const override {
        return channelName;
    }
};

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

// ======================= STOCK PRICE OBSERVER =======================
struct StockPrice {
    std::string symbol;
    double price;
    double change;
    
    StockPrice(const std::string& sym = "", double p = 0.0, double c = 0.0)
        : symbol(sym), price(p), change(c) {}
};

class StockDisplay : public Observer {
private:
    std::string displayName;
    
public:
    StockDisplay(const std::string& name) : displayName(name) {}
    
    void update(const std::string& message) override {
        std::cout << "📊 " << displayName << " updated: " << message << std::endl;
    }
    
    std::string getName() const override {
        return displayName;
    }
};

class StockMarket : public Subject {
private:
    std::vector<StockPrice> stocks;
    
public:
    void updateStock(const std::string& symbol, double newPrice) {
        bool found = false;
        for (auto& stock : stocks) {
            if (stock.symbol == symbol) {
                double oldPrice = stock.price;
                stock.change = newPrice - oldPrice;
                stock.price = newPrice;
                found = true;
                break;
            }
        }
        
        if (!found) {
            stocks.emplace_back(symbol, newPrice, 0.0);
        }
        
        setState(symbol + " price updated to $" + std::to_string(newPrice));
    }
    
    void displayAllStocks() const {
        std::cout << "\n📈 Current Stock Prices:" << std::endl;
        for (const auto& stock : stocks) {
            std::cout << stock.symbol << ": $" << stock.price 
                      << " (change: " << (stock.change >= 0 ? "+" : "") 
                      << stock.change << ")" << std::endl;
        }
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

// ======================= DEMONSTRATION FUNCTIONS =======================
inline void demonstrateObserver() {
    std::cout << "\n===== OBSERVER PATTERN DEMO =====\n" << std::endl;
    
    // Classic Observer Pattern
    std::cout << "1. Classic Observer Pattern (Notification System):" << std::endl;
    Subject notificationSystem;
    
    EmailNotifier emailNotifier("user@example.com");
    SMSNotifier smsNotifier("+1234567890");
    PushNotifier pushNotifier("device123");
    
    notificationSystem.attach(&emailNotifier);
    notificationSystem.attach(&smsNotifier);
    notificationSystem.setState("Your order has been shipped!");
    
    notificationSystem.attach(&pushNotifier);
    notificationSystem.setState("Payment successful!");
    
    notificationSystem.detach(&smsNotifier);
    notificationSystem.setState("Order delivered!");
    
    // News Agency Example
    std::cout << "\n2. News Agency Observer:" << std::endl;
    NewsAgency agency;
    NewsChannel cnn("CNN");
    NewsChannel bbc("BBC");
    NewsChannel fox("Fox News");
    
    agency.attach(&cnn);
    agency.attach(&bbc);
    agency.publishNews("Major earthquake hits Japan");
    
    agency.attach(&fox);
    agency.publishNews("Elections results announced");
    
    // Stock Market Example
    std::cout << "\n3. Stock Market Observer:" << std::endl;
    StockMarket market;
    StockDisplay display1("Trading Dashboard");
    StockDisplay display2("Mobile App");
    
    market.attach(&display1);
    market.attach(&display2);
    
    market.updateStock("AAPL", 150.25);
    market.updateStock("GOOGL", 2800.50);
    market.updateStock("AAPL", 152.30); // Price change
    market.displayAllStocks();
    
    // Modern C++ Observer with Lambda
    std::cout << "\n4. Modern C++ Observer with Lambdas:" << std::endl;
    ModernSubject<std::string> modernSubject;
    
    modernSubject.subscribe([](const std::string& data) {
        std::cout << "Lambda Observer 1: Received " << data << std::endl;
    });
    
    modernSubject.subscribe([](const std::string& data) {
        std::cout << "Lambda Observer 2: Processing " << data << std::endl;
    });
    
    modernSubject.setData("Hello World");
    modernSubject.setData("Design Patterns");
    
    // Event System
    std::cout << "\n5. Event System Example:" << std::endl;
    EventSystem eventSystem;
    
    // Register event listeners
    eventSystem.addEventListener(EventSystem::EventType::USER_LOGIN, [](const std::string& data) {
        std::cout << "   Analytics: User logged in - " << data << std::endl;
    });
    
    eventSystem.addEventListener(EventSystem::EventType::USER_LOGIN, [](const std::string& data) {
        std::cout << "   Security: Login recorded for - " << data << std::endl;
    });
    
    eventSystem.addEventListener(EventSystem::EventType::ORDER_PLACED, [](const std::string& data) {
        std::cout << "   Email: Sending confirmation for order - " << data << std::endl;
    });
    
    eventSystem.addEventListener(EventSystem::EventType::ORDER_PLACED, [](const std::string& data) {
        std::cout << "   Inventory: Updating stock for order - " << data << std::endl;
    });
    
    // Trigger events
    eventSystem.triggerEvent(EventSystem::EventType::USER_LOGIN, "john.doe@email.com");
    eventSystem.triggerEvent(EventSystem::EventType::ORDER_PLACED, "ORD-12345");
    eventSystem.triggerEvent(EventSystem::EventType::PAYMENT_SUCCESS, "PAY-67890");
}

#endif // OBSERVER_HPP
