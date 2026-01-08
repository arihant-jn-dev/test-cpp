#ifndef SMART_POINTERS_HPP
#define SMART_POINTERS_HPP

#include <iostream>
#include <memory>
#include <string>
#include <vector>

/**
 * SMART POINTERS IN C++
 * - Modern C++ memory management
 * - RAII (Resource Acquisition Is Initialization)
 * - Automatic memory cleanup
 * - Very common in interviews for modern C++ positions
 */

// ======================= RESOURCE CLASS FOR DEMONSTRATION =======================
class Resource {
private:
    std::string name;
    int id;
    
public:
    Resource(const std::string& n, int i) : name(n), id(i) {
        std::cout << "🔧 Resource created: " << name << " (ID: " << id << ")" << std::endl;
    }
    
    ~Resource() {
        std::cout << "🗑️  Resource destroyed: " << name << " (ID: " << id << ")" << std::endl;
    }
    
    void use() {
        std::cout << "⚡ Using resource: " << name << " (ID: " << id << ")" << std::endl;
    }
    
    std::string getName() const { return name; }
    int getId() const { return id; }
};

// ======================= UNIQUE_PTR EXAMPLES =======================
void demonstrateUniquePtr() {
    std::cout << "\n--- UNIQUE_PTR EXAMPLES ---" << std::endl;
    
    // Basic unique_ptr usage
    std::cout << "1. Basic unique_ptr creation:" << std::endl;
    std::unique_ptr<Resource> resource1 = std::make_unique<Resource>("Database", 1);
    resource1->use();
    
    // Transfer ownership
    std::cout << "\n2. Transfer ownership:" << std::endl;
    std::unique_ptr<Resource> resource2 = std::move(resource1);
    
    if (!resource1) {
        std::cout << "resource1 is now null after move" << std::endl;
    }
    
    if (resource2) {
        std::cout << "resource2 now owns the resource" << std::endl;
        resource2->use();
    }
    
    // Array version
    std::cout << "\n3. unique_ptr with arrays:" << std::endl;
    std::unique_ptr<int[]> numbers = std::make_unique<int[]>(5);
    for (int i = 0; i < 5; i++) {
        numbers[i] = i * 10;
        std::cout << "numbers[" << i << "] = " << numbers[i] << std::endl;
    }
    
    // Custom deleter
    std::cout << "\n4. unique_ptr with custom deleter:" << std::endl;
    auto customDeleter = [](Resource* r) {
        std::cout << "🔥 Custom deleter called for: " << r->getName() << std::endl;
        delete r;
    };
    
    std::unique_ptr<Resource, decltype(customDeleter)> resource3(
        new Resource("FileHandle", 3), customDeleter);
    resource3->use();
} // All resources automatically cleaned up here

// ======================= SHARED_PTR EXAMPLES =======================
void demonstrateSharedPtr() {
    std::cout << "\n--- SHARED_PTR EXAMPLES ---" << std::endl;
    
    // Basic shared_ptr usage
    std::cout << "1. Basic shared_ptr creation:" << std::endl;
    std::shared_ptr<Resource> resource1 = std::make_shared<Resource>("SharedResource", 10);
    std::cout << "Reference count: " << resource1.use_count() << std::endl;
    
    // Multiple owners
    std::cout << "\n2. Multiple owners:" << std::endl;
    {
        std::shared_ptr<Resource> resource2 = resource1; // Copy shared_ptr
        std::cout << "Reference count after copy: " << resource1.use_count() << std::endl;
        
        std::shared_ptr<Resource> resource3 = resource1; // Another copy
        std::cout << "Reference count with 3 owners: " << resource1.use_count() << std::endl;
        
        resource2->use();
        resource3->use();
    } // resource2 and resource3 go out of scope
    
    std::cout << "Reference count after scope exit: " << resource1.use_count() << std::endl;
    resource1->use();
    
    // Vector of shared_ptr
    std::cout << "\n3. Container of shared_ptr:" << std::endl;
    std::vector<std::shared_ptr<Resource>> resources;
    
    for (int i = 0; i < 3; i++) {
        resources.push_back(std::make_shared<Resource>("Resource" + std::to_string(i), 20 + i));
    }
    
    std::cout << "Resources in vector:" << std::endl;
    for (const auto& res : resources) {
        res->use();
        std::cout << "Reference count: " << res.use_count() << std::endl;
    }
} // All resources automatically cleaned up

// ======================= WEAK_PTR EXAMPLES =======================
class Node {
public:
    int data;
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> parent; // Weak reference to avoid cycles
    
    Node(int value) : data(value) {
        std::cout << "📊 Node created with value: " << data << std::endl;
    }
    
    ~Node() {
        std::cout << "🗑️  Node destroyed with value: " << data << std::endl;
    }
};

void demonstrateWeakPtr() {
    std::cout << "\n--- WEAK_PTR EXAMPLES ---" << std::endl;
    
    std::cout << "1. Breaking circular dependencies:" << std::endl;
    
    // Create a simple linked structure
    auto node1 = std::make_shared<Node>(1);
    auto node2 = std::make_shared<Node>(2);
    auto node3 = std::make_shared<Node>(3);
    
    // Set up forward links
    node1->next = node2;
    node2->next = node3;
    
    // Set up parent links (weak references)
    node2->parent = node1;
    node3->parent = node2;
    
    std::cout << "Reference count for node1: " << node1.use_count() << std::endl;
    std::cout << "Reference count for node2: " << node2.use_count() << std::endl;
    
    // Using weak_ptr
    std::cout << "\n2. Using weak_ptr:" << std::endl;
    std::weak_ptr<Node> weak_node = node2;
    
    if (auto locked_node = weak_node.lock()) {
        std::cout << "Accessed node through weak_ptr: " << locked_node->data << std::endl;
        std::cout << "Reference count during access: " << locked_node.use_count() << std::endl;
    }
    
    // Check if weak_ptr is expired
    std::cout << "\n3. Checking weak_ptr validity:" << std::endl;
    std::cout << "Is weak_ptr expired? " << (weak_node.expired() ? "Yes" : "No") << std::endl;
    
    // Reset the shared_ptr
    node2.reset();
    std::cout << "After resetting node2:" << std::endl;
    std::cout << "Is weak_ptr expired? " << (weak_node.expired() ? "Yes" : "No") << std::endl;
}

// ======================= COMPARISON WITH RAW POINTERS =======================
void demonstrateRawVsSmart() {
    std::cout << "\n--- RAW vs SMART POINTERS COMPARISON ---" << std::endl;
    
    std::cout << "1. Raw pointer problems:" << std::endl;
    {
        Resource* rawPtr = new Resource("RawResource", 100);
        rawPtr->use();
        // Oops! Forgot to delete - memory leak!
        // delete rawPtr; // This line is commented to show the problem
    }
    std::cout << "Memory leak occurred with raw pointer!" << std::endl;
    
    std::cout << "\n2. Smart pointer solution:" << std::endl;
    {
        auto smartPtr = std::make_unique<Resource>("SmartResource", 200);
        smartPtr->use();
        // Automatic cleanup when going out of scope
    }
    std::cout << "No memory leak with smart pointer!" << std::endl;
    
    std::cout << "\n3. Exception safety:" << std::endl;
    try {
        auto safePtr = std::make_unique<Resource>("ExceptionSafe", 300);
        safePtr->use();
        throw std::runtime_error("Simulated exception");
        // Resource is still cleaned up even with exception
    } catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
        std::cout << "Resource was still properly cleaned up!" << std::endl;
    }
}

// ======================= FACTORY WITH SMART POINTERS =======================
class Shape {
public:
    virtual ~Shape() = default;
    virtual void draw() const = 0;
    virtual std::string getType() const = 0;
};

class Circle : public Shape {
private:
    double radius;
    
public:
    Circle(double r) : radius(r) {
        std::cout << "🔵 Circle created with radius: " << radius << std::endl;
    }
    
    ~Circle() {
        std::cout << "🗑️  Circle destroyed" << std::endl;
    }
    
    void draw() const override {
        std::cout << "Drawing circle with radius: " << radius << std::endl;
    }
    
    std::string getType() const override {
        return "Circle";
    }
};

class Rectangle : public Shape {
private:
    double width, height;
    
public:
    Rectangle(double w, double h) : width(w), height(h) {
        std::cout << "🔲 Rectangle created: " << width << "x" << height << std::endl;
    }
    
    ~Rectangle() {
        std::cout << "🗑️  Rectangle destroyed" << std::endl;
    }
    
    void draw() const override {
        std::cout << "Drawing rectangle: " << width << "x" << height << std::endl;
    }
    
    std::string getType() const override {
        return "Rectangle";
    }
};

class ShapeFactory {
public:
    static std::unique_ptr<Shape> createCircle(double radius) {
        return std::make_unique<Circle>(radius);
    }
    
    static std::unique_ptr<Shape> createRectangle(double width, double height) {
        return std::make_unique<Rectangle>(width, height);
    }
    
    static std::shared_ptr<Shape> createSharedCircle(double radius) {
        return std::make_shared<Circle>(radius);
    }
};

void demonstrateSmartPointerFactory() {
    std::cout << "\n--- SMART POINTER FACTORY PATTERN ---" << std::endl;
    
    // unique_ptr factory
    std::cout << "1. unique_ptr factory:" << std::endl;
    auto circle = ShapeFactory::createCircle(5.0);
    auto rectangle = ShapeFactory::createRectangle(10.0, 20.0);
    
    circle->draw();
    rectangle->draw();
    
    // shared_ptr factory
    std::cout << "\n2. shared_ptr factory:" << std::endl;
    auto sharedCircle = ShapeFactory::createSharedCircle(7.5);
    
    std::vector<std::shared_ptr<Shape>> shapes;
    shapes.push_back(sharedCircle);
    shapes.push_back(sharedCircle); // Same object, shared ownership
    
    std::cout << "Reference count: " << sharedCircle.use_count() << std::endl;
    
    for (const auto& shape : shapes) {
        shape->draw();
    }
}

// ======================= DEMONSTRATION FUNCTION =======================
inline void demonstrateSmartPointers() {
    std::cout << "\n===== SMART POINTERS DEMO =====\n" << std::endl;
    
    demonstrateUniquePtr();
    demonstrateSharedPtr();
    demonstrateWeakPtr();
    demonstrateRawVsSmart();
    demonstrateSmartPointerFactory();
    
    std::cout << "\n===== SMART POINTERS BEST PRACTICES =====\n" << std::endl;
    std::cout << "✅ Use unique_ptr by default for single ownership" << std::endl;
    std::cout << "✅ Use shared_ptr when you need shared ownership" << std::endl;
    std::cout << "✅ Use weak_ptr to break circular dependencies" << std::endl;
    std::cout << "✅ Prefer make_unique and make_shared over new" << std::endl;
    std::cout << "✅ Use smart pointers for exception safety" << std::endl;
    std::cout << "❌ Don't mix raw pointers with smart pointers" << std::endl;
    std::cout << "❌ Don't create shared_ptr from raw pointers multiple times" << std::endl;
}

#endif // SMART_POINTERS_HPP
