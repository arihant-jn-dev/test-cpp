#ifndef FACTORY_HPP
#define FACTORY_HPP

#include <iostream>
#include <memory>
#include <string>
#include <map>
#include <functional>

/**
 * FACTORY DESIGN PATTERNS
 * - Simple Factory: Static method to create objects
 * - Factory Method: Virtual method in base class
 * - Abstract Factory: Family of related objects
 * - Very common in interviews for object creation scenarios
 */

// ======================= SIMPLE FACTORY PATTERN =======================
class Shape {
public:
    virtual ~Shape() = default;
    virtual void draw() const = 0;
    virtual double getArea() const = 0;
    virtual std::string getType() const = 0;
};

class Circle : public Shape {
private:
    double radius;
    
public:
    Circle(double r) : radius(r) {}
    
    void draw() const override {
        std::cout << "Drawing Circle with radius: " << radius << std::endl;
    }
    
    double getArea() const override {
        return 3.14159 * radius * radius;
    }
    
    std::string getType() const override {
        return "Circle";
    }
};

class Rectangle : public Shape {
private:
    double width, height;
    
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    
    void draw() const override {
        std::cout << "Drawing Rectangle " << width << "x" << height << std::endl;
    }
    
    double getArea() const override {
        return width * height;
    }
    
    std::string getType() const override {
        return "Rectangle";
    }
};

class Triangle : public Shape {
private:
    double base, height;
    
public:
    Triangle(double b, double h) : base(b), height(h) {}
    
    void draw() const override {
        std::cout << "Drawing Triangle with base: " << base << ", height: " << height << std::endl;
    }
    
    double getArea() const override {
        return 0.5 * base * height;
    }
    
    std::string getType() const override {
        return "Triangle";
    }
};

// Simple Factory
class ShapeFactory {
public:
    enum class ShapeType {
        CIRCLE,
        RECTANGLE,
        TRIANGLE
    };
    
    static std::unique_ptr<Shape> createShape(ShapeType type, double param1, double param2 = 0) {
        switch(type) {
            case ShapeType::CIRCLE:
                return std::make_unique<Circle>(param1);
            case ShapeType::RECTANGLE:
                return std::make_unique<Rectangle>(param1, param2);
            case ShapeType::TRIANGLE:
                return std::make_unique<Triangle>(param1, param2);
            default:
                return nullptr;
        }
    }
    
    // String-based factory (more flexible)
    static std::unique_ptr<Shape> createShape(const std::string& type, double param1, double param2 = 0) {
        if (type == "circle") {
            return std::make_unique<Circle>(param1);
        } else if (type == "rectangle") {
            return std::make_unique<Rectangle>(param1, param2);
        } else if (type == "triangle") {
            return std::make_unique<Triangle>(param1, param2);
        }
        return nullptr;
    }
};

// ======================= FACTORY METHOD PATTERN =======================
class Document {
public:
    virtual ~Document() = default;
    virtual void open() = 0;
    virtual void save() = 0;
    virtual std::string getType() = 0;
};

class WordDocument : public Document {
public:
    void open() override {
        std::cout << "Opening Word document (.docx)" << std::endl;
    }
    
    void save() override {
        std::cout << "Saving Word document with formatting" << std::endl;
    }
    
    std::string getType() override {
        return "Word Document";
    }
};

class PDFDocument : public Document {
public:
    void open() override {
        std::cout << "Opening PDF document (.pdf)" << std::endl;
    }
    
    void save() override {
        std::cout << "Saving PDF document with layout preservation" << std::endl;
    }
    
    std::string getType() override {
        return "PDF Document";
    }
};

class TextDocument : public Document {
public:
    void open() override {
        std::cout << "Opening Text document (.txt)" << std::endl;
    }
    
    void save() override {
        std::cout << "Saving plain text document" << std::endl;
    }
    
    std::string getType() override {
        return "Text Document";
    }
};

// Abstract Creator
class DocumentFactory {
public:
    virtual ~DocumentFactory() = default;
    virtual std::unique_ptr<Document> createDocument() = 0;
    
    // Template method using factory method
    void processDocument() {
        auto doc = createDocument();
        doc->open();
        std::cout << "Processing " << doc->getType() << "..." << std::endl;
        doc->save();
    }
};

// Concrete Creators
class WordDocumentFactory : public DocumentFactory {
public:
    std::unique_ptr<Document> createDocument() override {
        return std::make_unique<WordDocument>();
    }
};

class PDFDocumentFactory : public DocumentFactory {
public:
    std::unique_ptr<Document> createDocument() override {
        return std::make_unique<PDFDocument>();
    }
};

class TextDocumentFactory : public DocumentFactory {
public:
    std::unique_ptr<Document> createDocument() override {
        return std::make_unique<TextDocument>();
    }
};

// ======================= ABSTRACT FACTORY PATTERN =======================
// Abstract Products
class Button {
public:
    virtual ~Button() = default;
    virtual void render() = 0;
    virtual void onClick() = 0;
};

class Checkbox {
public:
    virtual ~Checkbox() = default;
    virtual void render() = 0;
    virtual void toggle() = 0;
};

// Windows Family
class WindowsButton : public Button {
public:
    void render() override {
        std::cout << "Rendering Windows-style button with blue theme" << std::endl;
    }
    
    void onClick() override {
        std::cout << "Windows button clicked with system sound" << std::endl;
    }
};

class WindowsCheckbox : public Checkbox {
public:
    void render() override {
        std::cout << "Rendering Windows-style checkbox with square design" << std::endl;
    }
    
    void toggle() override {
        std::cout << "Windows checkbox toggled with animation" << std::endl;
    }
};

// Mac Family
class MacButton : public Button {
public:
    void render() override {
        std::cout << "Rendering Mac-style button with rounded corners" << std::endl;
    }
    
    void onClick() override {
        std::cout << "Mac button clicked with haptic feedback" << std::endl;
    }
};

class MacCheckbox : public Checkbox {
public:
    void render() override {
        std::cout << "Rendering Mac-style checkbox with circular design" << std::endl;
    }
    
    void toggle() override {
        std::cout << "Mac checkbox toggled with smooth transition" << std::endl;
    }
};

// Abstract Factory
class GUIFactory {
public:
    virtual ~GUIFactory() = default;
    virtual std::unique_ptr<Button> createButton() = 0;
    virtual std::unique_ptr<Checkbox> createCheckbox() = 0;
};

// Concrete Factories
class WindowsFactory : public GUIFactory {
public:
    std::unique_ptr<Button> createButton() override {
        return std::make_unique<WindowsButton>();
    }
    
    std::unique_ptr<Checkbox> createCheckbox() override {
        return std::make_unique<WindowsCheckbox>();
    }
};

class MacFactory : public GUIFactory {
public:
    std::unique_ptr<Button> createButton() override {
        return std::make_unique<MacButton>();
    }
    
    std::unique_ptr<Checkbox> createCheckbox() override {
        return std::make_unique<MacCheckbox>();
    }
};

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

// ======================= DEMONSTRATION FUNCTIONS =======================
inline void demonstrateFactory() {
    std::cout << "\n===== FACTORY PATTERNS DEMO =====\n" << std::endl;
    
    // Simple Factory
    std::cout << "1. Simple Factory Pattern:" << std::endl;
    auto circle = ShapeFactory::createShape(ShapeFactory::ShapeType::CIRCLE, 5.0);
    auto rect = ShapeFactory::createShape("rectangle", 4.0, 6.0);
    
    if (circle) {
        circle->draw();
        std::cout << "Area: " << circle->getArea() << std::endl;
    }
    if (rect) {
        rect->draw();
        std::cout << "Area: " << rect->getArea() << std::endl;
    }
    
    // Factory Method
    std::cout << "\n2. Factory Method Pattern:" << std::endl;
    auto wordFactory = std::make_unique<WordDocumentFactory>();
    auto pdfFactory = std::make_unique<PDFDocumentFactory>();
    
    wordFactory->processDocument();
    std::cout << std::endl;
    pdfFactory->processDocument();
    
    // Abstract Factory
    std::cout << "\n3. Abstract Factory Pattern:" << std::endl;
    auto windowsFactory = std::make_unique<WindowsFactory>();
    auto macFactory = std::make_unique<MacFactory>();
    
    // Create Windows UI
    std::cout << "Creating Windows UI:" << std::endl;
    auto winButton = windowsFactory->createButton();
    auto winCheckbox = windowsFactory->createCheckbox();
    winButton->render();
    winCheckbox->render();
    
    std::cout << "\nCreating Mac UI:" << std::endl;
    auto macButton = macFactory->createButton();
    auto macCheckbox = macFactory->createCheckbox();
    macButton->render();
    macCheckbox->render();
    
    // Registration-based Factory
    std::cout << "\n4. Registration-based Factory:" << std::endl;
    AdvancedShapeFactory::registerShape<Circle>("circle");
    AdvancedShapeFactory::registerShape<Rectangle>("rectangle");
    AdvancedShapeFactory::registerShape<Triangle>("triangle");
    
    AdvancedShapeFactory::listAvailableShapes();
    
    auto advCircle = AdvancedShapeFactory::create("circle", 3.0);
    if (advCircle) {
        advCircle->draw();
        std::cout << "Area: " << advCircle->getArea() << std::endl;
    }
}

#endif // FACTORY_HPP
