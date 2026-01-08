#ifndef ABSTRACTION_HPP
#define ABSTRACTION_HPP

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>

/**
 * ===============================================
 * ABSTRACTION - HIDING COMPLEXITY, SHOWING ESSENTIALS
 * ===============================================
 * 
 * Abstraction is the process of hiding implementation details while showing
 * only essential features to the user. It's achieved through abstract classes
 * and interfaces.
 * 
 * INTERVIEW QUESTIONS COVERED:
 * 1. What is abstraction and how is it different from encapsulation?
 * 2. What are abstract classes and pure virtual functions?
 * 3. What is the difference between abstract class and interface?
 * 4. Can we instantiate abstract classes?
 * 5. What is the purpose of abstract base classes?
 * 6. Can abstract classes have constructors?
 */

namespace AdvancedConcepts {

/**
 * ===============================================
 * ABSTRACT BASE CLASS EXAMPLE
 * ===============================================
 */

/**
 * Abstract Database Connection Interface
 * Demonstrates: Pure virtual functions, abstract class design
 */
class DatabaseConnection {
protected:
    std::string connectionString;
    bool isConnected;
    std::string databaseType;

public:
    // Constructor for abstract class
    DatabaseConnection(const std::string& connStr, const std::string& dbType)
        : connectionString(connStr), isConnected(false), databaseType(dbType) {
        std::cout << "DatabaseConnection constructor called for " << dbType << std::endl;
    }
    
    // Virtual destructor
    virtual ~DatabaseConnection() {
        // Don't call pure virtual function in destructor
        std::cout << "DatabaseConnection destructor called" << std::endl;
    }
    
    // Pure virtual functions - must be implemented by derived classes
    virtual bool connect() = 0;
    virtual void disconnect() = 0;
    virtual bool executeQuery(const std::string& query) = 0;
    virtual std::vector<std::string> getResults() = 0;
    virtual bool beginTransaction() = 0;
    virtual bool commitTransaction() = 0;
    virtual bool rollbackTransaction() = 0;
    
    // Concrete methods - provide common functionality
    bool isConnectionActive() const {
        return isConnected;
    }
    
    const std::string& getConnectionString() const {
        return connectionString;
    }
    
    const std::string& getDatabaseType() const {
        return databaseType;
    }
    
    // Template method pattern - defines algorithm skeleton
    bool executeTransactionalQuery(const std::string& query) {
        if (!isConnected) {
            std::cout << "Error: Not connected to database" << std::endl;
            return false;
        }
        
        std::cout << "Starting transactional query..." << std::endl;
        
        if (!beginTransaction()) {
            std::cout << "Failed to begin transaction" << std::endl;
            return false;
        }
        
        bool success = executeQuery(query);
        
        if (success) {
            if (commitTransaction()) {
                std::cout << "Transaction committed successfully" << std::endl;
                return true;
            } else {
                std::cout << "Failed to commit transaction" << std::endl;
                rollbackTransaction();
                return false;
            }
        } else {
            std::cout << "Query failed, rolling back transaction" << std::endl;
            rollbackTransaction();
            return false;
        }
    }
};

/**
 * Concrete implementation - MySQL Database
 */
class MySQLConnection : public DatabaseConnection {
private:
    std::vector<std::string> queryResults;
    bool inTransaction;

public:
    MySQLConnection(const std::string& host, const std::string& database,
                   const std::string& username, const std::string& password)
        : DatabaseConnection("mysql://" + username + "@" + host + "/" + database, "MySQL"),
          inTransaction(false) {
        std::cout << "MySQLConnection created" << std::endl;
    }
    
    ~MySQLConnection() override {
        std::cout << "MySQLConnection destructor" << std::endl;
    }
    
    bool connect() override {
        std::cout << "Connecting to MySQL database..." << std::endl;
        std::cout << "Connection string: " << connectionString << std::endl;
        
        // Simulate connection logic
        isConnected = true;
        std::cout << "MySQL connection established" << std::endl;
        return true;
    }
    
    void disconnect() override {
        if (isConnected) {
            if (inTransaction) {
                rollbackTransaction();
            }
            std::cout << "Disconnecting from MySQL database..." << std::endl;
            isConnected = false;
            std::cout << "MySQL connection closed" << std::endl;
        }
    }
    
    bool executeQuery(const std::string& query) override {
        if (!isConnected) {
            std::cout << "Error: Not connected to MySQL database" << std::endl;
            return false;
        }
        
        std::cout << "Executing MySQL query: " << query << std::endl;
        
        // Simulate query execution
        queryResults.clear();
        queryResults.push_back("Result row 1");
        queryResults.push_back("Result row 2");
        queryResults.push_back("Result row 3");
        
        std::cout << "MySQL query executed successfully" << std::endl;
        return true;
    }
    
    std::vector<std::string> getResults() override {
        return queryResults;
    }
    
    bool beginTransaction() override {
        if (!isConnected) return false;
        
        std::cout << "BEGIN TRANSACTION (MySQL)" << std::endl;
        inTransaction = true;
        return true;
    }
    
    bool commitTransaction() override {
        if (!inTransaction) return false;
        
        std::cout << "COMMIT (MySQL)" << std::endl;
        inTransaction = false;
        return true;
    }
    
    bool rollbackTransaction() override {
        if (!inTransaction) return false;
        
        std::cout << "ROLLBACK (MySQL)" << std::endl;
        inTransaction = false;
        return true;
    }
    
    // MySQL-specific methods
    void showTables() {
        if (executeQuery("SHOW TABLES")) {
            std::cout << "MySQL Tables:" << std::endl;
            for (const auto& result : queryResults) {
                std::cout << "  " << result << std::endl;
            }
        }
    }
};

/**
 * Concrete implementation - PostgreSQL Database
 */
class PostgreSQLConnection : public DatabaseConnection {
private:
    std::vector<std::string> queryResults;
    std::string transactionId;

public:
    PostgreSQLConnection(const std::string& host, const std::string& database,
                        const std::string& username, const std::string& password)
        : DatabaseConnection("postgresql://" + username + "@" + host + "/" + database, "PostgreSQL") {
        std::cout << "PostgreSQLConnection created" << std::endl;
    }
    
    ~PostgreSQLConnection() override {
        std::cout << "PostgreSQLConnection destructor" << std::endl;
    }
    
    bool connect() override {
        std::cout << "Connecting to PostgreSQL database..." << std::endl;
        std::cout << "Connection string: " << connectionString << std::endl;
        
        isConnected = true;
        std::cout << "PostgreSQL connection established" << std::endl;
        return true;
    }
    
    void disconnect() override {
        if (isConnected) {
            if (!transactionId.empty()) {
                rollbackTransaction();
            }
            std::cout << "Disconnecting from PostgreSQL database..." << std::endl;
            isConnected = false;
            std::cout << "PostgreSQL connection closed" << std::endl;
        }
    }
    
    bool executeQuery(const std::string& query) override {
        if (!isConnected) {
            std::cout << "Error: Not connected to PostgreSQL database" << std::endl;
            return false;
        }
        
        std::cout << "Executing PostgreSQL query: " << query << std::endl;
        
        queryResults.clear();
        queryResults.push_back("PG Result 1");
        queryResults.push_back("PG Result 2");
        
        std::cout << "PostgreSQL query executed successfully" << std::endl;
        return true;
    }
    
    std::vector<std::string> getResults() override {
        return queryResults;
    }
    
    bool beginTransaction() override {
        if (!isConnected) return false;
        
        transactionId = "TXN_" + std::to_string(rand() % 10000);
        std::cout << "BEGIN TRANSACTION " << transactionId << " (PostgreSQL)" << std::endl;
        return true;
    }
    
    bool commitTransaction() override {
        if (transactionId.empty()) return false;
        
        std::cout << "COMMIT " << transactionId << " (PostgreSQL)" << std::endl;
        transactionId.clear();
        return true;
    }
    
    bool rollbackTransaction() override {
        if (transactionId.empty()) return false;
        
        std::cout << "ROLLBACK " << transactionId << " (PostgreSQL)" << std::endl;
        transactionId.clear();
        return true;
    }
    
    // PostgreSQL-specific methods
    void vacuum() {
        std::cout << "Running VACUUM on PostgreSQL database" << std::endl;
    }
};

/**
 * ===============================================
 * INTERFACE-LIKE ABSTRACT CLASSES
 * ===============================================
 */

/**
 * Pure interface - only pure virtual functions
 */
class Printable {
public:
    virtual ~Printable() = default;
    virtual void print() const = 0;
    virtual std::string toString() const = 0;
};

class Serializable {
public:
    virtual ~Serializable() = default;
    virtual std::string serialize() const = 0;
    virtual bool deserialize(const std::string& data) = 0;
};

class Comparable {
public:
    virtual ~Comparable() = default;
    virtual int compareTo(const Comparable& other) const = 0;
    virtual bool equals(const Comparable& other) const = 0;
};

/**
 * Document class implementing multiple interfaces
 */
class Document : public Printable, public Serializable, public Comparable {
private:
    std::string title;
    std::string content;
    std::string author;
    int pageCount;

public:
    Document(const std::string& t, const std::string& c, const std::string& a, int pages)
        : title(t), content(c), author(a), pageCount(pages) {}
    
    // Implement Printable interface
    void print() const override {
        std::cout << "Printing document: " << title << std::endl;
        std::cout << "Author: " << author << std::endl;
        std::cout << "Pages: " << pageCount << std::endl;
        std::cout << "Content: " << content.substr(0, 100) << "..." << std::endl;
    }
    
    std::string toString() const override {
        return "Document{title='" + title + "', author='" + author + 
               "', pages=" + std::to_string(pageCount) + "}";
    }
    
    // Implement Serializable interface
    std::string serialize() const override {
        return title + "|" + content + "|" + author + "|" + std::to_string(pageCount);
    }
    
    bool deserialize(const std::string& data) override {
        size_t pos1 = data.find('|');
        size_t pos2 = data.find('|', pos1 + 1);
        size_t pos3 = data.find('|', pos2 + 1);
        
        if (pos1 != std::string::npos && pos2 != std::string::npos && pos3 != std::string::npos) {
            title = data.substr(0, pos1);
            content = data.substr(pos1 + 1, pos2 - pos1 - 1);
            author = data.substr(pos2 + 1, pos3 - pos2 - 1);
            pageCount = std::stoi(data.substr(pos3 + 1));
            return true;
        }
        return false;
    }
    
    // Implement Comparable interface
    int compareTo(const Comparable& other) const override {
        const Document* otherDoc = dynamic_cast<const Document*>(&other);
        if (!otherDoc) {
            throw std::invalid_argument("Cannot compare Document with non-Document");
        }
        
        if (pageCount < otherDoc->pageCount) return -1;
        if (pageCount > otherDoc->pageCount) return 1;
        return title.compare(otherDoc->title);
    }
    
    bool equals(const Comparable& other) const override {
        return compareTo(other) == 0;
    }
    
    // Getters
    const std::string& getTitle() const { return title; }
    const std::string& getContent() const { return content; }
    const std::string& getAuthor() const { return author; }
    int getPageCount() const { return pageCount; }
};

/**
 * ===============================================
 * ABSTRACT FACTORY PATTERN
 * ===============================================
 */

/**
 * Abstract UI Component
 */
class UIComponent {
protected:
    std::string name;
    bool visible;

public:
    UIComponent(const std::string& n) : name(n), visible(true) {}
    virtual ~UIComponent() = default;
    
    virtual void render() = 0;
    virtual void handleClick() = 0;
    virtual void setVisible(bool v) { visible = v; }
    virtual bool isVisible() const { return visible; }
    const std::string& getName() const { return name; }
};

class Button : public UIComponent {
private:
    std::string text;
    std::string style;

public:
    Button(const std::string& n, const std::string& t, const std::string& s)
        : UIComponent(n), text(t), style(s) {}
    
    virtual void render() override = 0;
    virtual void handleClick() override = 0;
    
    const std::string& getText() const { return text; }
    const std::string& getStyle() const { return style; }
};

class TextField : public UIComponent {
private:
    std::string placeholder;
    std::string value;

public:
    TextField(const std::string& n, const std::string& p)
        : UIComponent(n), placeholder(p) {}
    
    virtual void render() override = 0;
    virtual void handleClick() override = 0;
    
    const std::string& getPlaceholder() const { return placeholder; }
    const std::string& getValue() const { return value; }
    void setValue(const std::string& v) { value = v; }
};

/**
 * Concrete implementations for different platforms
 */
class WindowsButton : public Button {
public:
    WindowsButton(const std::string& n, const std::string& t)
        : Button(n, t, "Windows") {}
    
    void render() override {
        std::cout << "Rendering Windows-style button: " << getText() << std::endl;
        std::cout << "  [" << getText() << "]" << std::endl;
    }
    
    void handleClick() override {
        std::cout << "Windows button '" << getText() << "' clicked!" << std::endl;
    }
};

class MacButton : public Button {
public:
    MacButton(const std::string& n, const std::string& t)
        : Button(n, t, "Mac") {}
    
    void render() override {
        std::cout << "Rendering Mac-style button: " << getText() << std::endl;
        std::cout << "  (" << getText() << ")" << std::endl;
    }
    
    void handleClick() override {
        std::cout << "Mac button '" << getText() << "' clicked!" << std::endl;
    }
};

class WindowsTextField : public TextField {
public:
    WindowsTextField(const std::string& n, const std::string& p)
        : TextField(n, p) {}
    
    void render() override {
        std::cout << "Rendering Windows-style text field" << std::endl;
        std::cout << "  |" << getPlaceholder() << "               |" << std::endl;
    }
    
    void handleClick() override {
        std::cout << "Windows text field focused" << std::endl;
    }
};

class MacTextField : public TextField {
public:
    MacTextField(const std::string& n, const std::string& p)
        : TextField(n, p) {}
    
    void render() override {
        std::cout << "Rendering Mac-style text field" << std::endl;
        std::cout << "  ⌐" << getPlaceholder() << "               ¬" << std::endl;
    }
    
    void handleClick() override {
        std::cout << "Mac text field focused" << std::endl;
    }
};

/**
 * Abstract Factory
 */
class UIFactory {
public:
    virtual ~UIFactory() = default;
    virtual std::unique_ptr<Button> createButton(const std::string& name, 
                                                const std::string& text) = 0;
    virtual std::unique_ptr<TextField> createTextField(const std::string& name,
                                                      const std::string& placeholder) = 0;
    virtual std::string getPlatformName() const = 0;
};

class WindowsUIFactory : public UIFactory {
public:
    std::unique_ptr<Button> createButton(const std::string& name, 
                                       const std::string& text) override {
        return std::make_unique<WindowsButton>(name, text);
    }
    
    std::unique_ptr<TextField> createTextField(const std::string& name,
                                             const std::string& placeholder) override {
        return std::make_unique<WindowsTextField>(name, placeholder);
    }
    
    std::string getPlatformName() const override {
        return "Windows";
    }
};

class MacUIFactory : public UIFactory {
public:
    std::unique_ptr<Button> createButton(const std::string& name, 
                                       const std::string& text) override {
        return std::make_unique<MacButton>(name, text);
    }
    
    std::unique_ptr<TextField> createTextField(const std::string& name,
                                             const std::string& placeholder) override {
        return std::make_unique<MacTextField>(name, placeholder);
    }
    
    std::string getPlatformName() const override {
        return "Mac";
    }
};

/**
 * Client code using abstraction
 */
class Application {
private:
    std::unique_ptr<UIFactory> factory;
    std::vector<std::unique_ptr<UIComponent>> components;

public:
    Application(std::unique_ptr<UIFactory> f) : factory(std::move(f)) {}
    
    void createUI() {
        std::cout << "Creating UI for " << factory->getPlatformName() << " platform" << std::endl;
        
        auto button = factory->createButton("submitBtn", "Submit");
        auto textField = factory->createTextField("nameField", "Enter your name");
        
        components.push_back(std::move(button));
        components.push_back(std::move(textField));
    }
    
    void renderUI() {
        std::cout << "\nRendering UI components:" << std::endl;
        for (const auto& component : components) {
            if (component->isVisible()) {
                component->render();
            }
        }
    }
    
    void simulateUserInteraction() {
        std::cout << "\nSimulating user interaction:" << std::endl;
        for (const auto& component : components) {
            component->handleClick();
        }
    }
};

} // namespace AdvancedConcepts

/**
 * ===============================================
 * INTERVIEW QUESTIONS AND ANSWERS
 * ===============================================
 * 
 * Q1: What is abstraction and how is it different from encapsulation?
 * A1: Abstraction: Hiding complexity, showing only essential features
 *     Encapsulation: Hiding implementation details, bundling data with methods
 *     Abstraction is WHAT (interface), Encapsulation is HOW (implementation)
 * 
 * Q2: What are abstract classes and pure virtual functions?
 * A2: Abstract class: Class with at least one pure virtual function
 *     Pure virtual function: virtual function = 0, must be implemented by derived classes
 *     Cannot instantiate abstract classes directly
 * 
 * Q3: What is the difference between abstract class and interface?
 * A3: Abstract class: Can have data members, constructors, concrete methods
 *     Interface: Only pure virtual functions (in C++, achieved through abstract classes)
 *     Abstract class represents IS-A, Interface represents CAN-DO
 * 
 * Q4: Can we instantiate abstract classes?
 * A4: No, cannot create objects of abstract classes
 *     Can have pointers/references to abstract classes
 *     Can have constructors (called by derived class constructors)
 * 
 * Q5: What is the purpose of abstract base classes?
 * A5: - Define common interface for derived classes
 *     - Enforce implementation of certain methods
 *     - Enable polymorphism
 *     - Code reusability through common base functionality
 * 
 * Q6: Can abstract classes have constructors?
 * A6: Yes, abstract classes can have constructors
 *     Called when derived class objects are created
 *     Used to initialize base class members
 *     Cannot be used to create objects directly
 * 
 * Q7: What is the Template Method pattern?
 * A7: Defines skeleton of algorithm in base class, lets derived classes
 *     override specific steps without changing algorithm structure
 * 
 * Q8: When to use abstract classes vs interfaces?
 * A8: Abstract classes: When you have common implementation to share
 *     Interfaces: When you want to define a contract/capability
 *     Use interfaces for multiple inheritance-like behavior
 * 
 * Q9: Can we have virtual functions in abstract classes?
 * A9: Yes, abstract classes can have:
 *     - Pure virtual functions (must implement)
 *     - Virtual functions with implementation (can override)
 *     - Non-virtual functions (cannot override)
 * 
 * Q10: What is the Abstract Factory pattern?
 * A10: Creational pattern that provides interface for creating families
 *      of related objects without specifying their concrete classes
 *      Useful for platform-specific or theme-specific object creation
 */

// ======================= DEMONSTRATION FUNCTION =======================
inline void demonstrateAbstraction() {
    std::cout << "\n===== ABSTRACTION DEMO =====\n" << std::endl;
    
    // Database Connection Abstraction
    std::cout << "1. Database Connection Abstraction:" << std::endl;
    AdvancedConcepts::MySQLConnection mysql("localhost", 3306, "mydb");
    mysql.executeQuery("SELECT * FROM users");
    mysql.disconnect();
    
    std::cout << std::endl;
    AdvancedConcepts::PostgreSQLConnection postgres("localhost", 5432, "mydb");
    postgres.executeQuery("SELECT COUNT(*) FROM orders");
    postgres.disconnect();
    
    // Document Interface Example
    std::cout << "\n2. Interface Implementation:" << std::endl;
    AdvancedConcepts::Document doc("Sample Document", "This is a sample document content.");
    doc.print();
    std::string serialized = doc.serialize();
    std::cout << "Serialized: " << serialized << std::endl;
    
    // File System Abstraction
    std::cout << "\n3. File System Abstraction:" << std::endl;
    FileSystemManager manager;
    
    manager.setFileSystem(std::make_unique<LocalFileSystem>());
    manager.storeFile("document.pdf", "Local PDF content");
    manager.retrieveFile("document.pdf");
    
    manager.setFileSystem(std::make_unique<CloudFileSystem>());
    manager.storeFile("image.jpg", "Cloud image content");
    manager.retrieveFile("image.jpg");
    
    // Notification System Abstraction
    std::cout << "\n4. Notification System Abstraction:" << std::endl;
    NotificationManager notificationManager;
    
    notificationManager.addChannel(std::make_unique<EmailNotification>());
    notificationManager.addChannel(std::make_unique<SMSNotification>());
    notificationManager.addChannel(std::make_unique<PushNotification>());
    
    notificationManager.sendNotification("Your order has been shipped!");
    
    // Pure Virtual Function Demo
    std::cout << "\n5. Pure Virtual Functions:" << std::endl;
    std::vector<std::unique_ptr<GeometricShape>> shapes;
    shapes.push_back(std::make_unique<Circle2D>(7.5));
    shapes.push_back(std::make_unique<Rectangle2D>(10.0, 5.0));
    
    for (const auto& shape : shapes) {
        shape->draw();
        std::cout << "Area: " << shape->calculateArea() << std::endl;
        std::cout << "Perimeter: " << shape->calculatePerimeter() << std::endl;
        std::cout << std::endl;
    }
}

#endif // ABSTRACTION_HPP
