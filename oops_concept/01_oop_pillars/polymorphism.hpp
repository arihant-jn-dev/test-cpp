#ifndef POLYMORPHISM_HPP
#define POLYMORPHISM_HPP

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cmath>

/**
 * ===============================================
 * POLYMORPHISM - ONE INTERFACE, MULTIPLE FORMS
 * ===============================================
 *
 * Polymorphism allows objects of different types to be treated as objects of
 * a common base type while maintaining their specific behavior.
 *
 * INTERVIEW QUESTIONS COVERED:
 * 1. What is polymorphism and its types?
 * 2. What is the difference between compile-time and runtime polymorphism?
 * 3. What are virtual functions and how do they work?
 * 4. What is a vtable (virtual table)?
 * 5. What is function overloading vs overriding?
 * 6. What are pure virtual functions and abstract classes?
 *
 * Operator overloading, templates, functors and dynamic_cast are in
 * 04_advanced_cpp/advanced_polymorphism.hpp.
 */

namespace BasicConcepts {

/**
 * ===============================================
 * COMPILE-TIME POLYMORPHISM
 * ===============================================
 */

/**
 * Function Overloading - Same name, different parameters
 */
class Calculator {
public:
    // Function overloading - compile-time polymorphism
    int add(int a, int b) {
        std::cout << "Adding two integers: " << a << " + " << b;
        return a + b;
    }
    
    double add(double a, double b) {
        std::cout << "Adding two doubles: " << a << " + " << b;
        return a + b;
    }
    
    int add(int a, int b, int c) {
        std::cout << "Adding three integers: " << a << " + " << b << " + " << c;
        return a + b + c;
    }
    
    std::string add(const std::string& a, const std::string& b) {
        std::cout << "Concatenating strings: " << a << " + " << b;
        return a + b;
    }
};

/**
 * ===============================================
 * RUNTIME POLYMORPHISM
 * ===============================================
 */

/**
 * Base class for demonstrating runtime polymorphism
 */
class Shape {
protected:
    std::string name;
    std::string color;

public:
    Shape(const std::string& n, const std::string& c) : name(n), color(c) {
        std::cout << "Shape constructor: " << name << std::endl;
    }
    
    // Virtual destructor - essential for proper cleanup
    virtual ~Shape() {
        std::cout << "Shape destructor: " << name << std::endl;
    }
    
    // Pure virtual functions - makes Shape abstract
    virtual double calculateArea() const = 0;
    virtual double calculatePerimeter() const = 0;
    virtual void draw() const = 0;
    
    // Virtual function with implementation
    virtual void displayInfo() const {
        std::cout << "Shape: " << name << ", Color: " << color << std::endl;
        std::cout << "Area: " << calculateArea() << std::endl;
        std::cout << "Perimeter: " << calculatePerimeter() << std::endl;
    }
    
    // Non-virtual function
    const std::string& getName() const { return name; }
    const std::string& getColor() const { return color; }
    
    // Virtual function to demonstrate vtable
    virtual std::string getType() const {
        return "Generic Shape";
    }
};

/**
 * Derived class - Circle
 */
class Circle : public Shape {
private:
    double radius;

public:
    Circle(const std::string& c, double r) 
        : Shape("Circle", c), radius(r) {
        std::cout << "Circle constructor" << std::endl;
    }
    
    ~Circle() override {
        std::cout << "Circle destructor" << std::endl;
    }
    
    // Override pure virtual functions
    double calculateArea() const override {
        return 3.14159 * radius * radius;
    }
    
    double calculatePerimeter() const override {
        return 2 * 3.14159 * radius;
    }
    
    void draw() const override {
        std::cout << "Drawing a " << color << " circle with radius " << radius << std::endl;
    }
    
    // Override virtual function
    void displayInfo() const override {
        Shape::displayInfo(); // Call base implementation
        std::cout << "Radius: " << radius << std::endl;
    }
    
    std::string getType() const override {
        return "Circle";
    }
    
    // Circle-specific method
    double getRadius() const { return radius; }
    void setRadius(double r) { radius = r; }
};

/**
 * Derived class - Rectangle
 */
class Rectangle : public Shape {
private:
    double width, height;

public:
    Rectangle(const std::string& c, double w, double h)
        : Shape("Rectangle", c), width(w), height(h) {
        std::cout << "Rectangle constructor" << std::endl;
    }
    
    ~Rectangle() override {
        std::cout << "Rectangle destructor" << std::endl;
    }
    
    double calculateArea() const override {
        return width * height;
    }
    
    double calculatePerimeter() const override {
        return 2 * (width + height);
    }
    
    void draw() const override {
        std::cout << "Drawing a " << color << " rectangle " 
                  << width << "x" << height << std::endl;
    }
    
    void displayInfo() const override {
        Shape::displayInfo();
        std::cout << "Width: " << width << ", Height: " << height << std::endl;
    }
    
    std::string getType() const override {
        return "Rectangle";
    }
    
    // Rectangle-specific methods
    double getWidth() const { return width; }
    double getHeight() const { return height; }
    bool isSquare() const { return width == height; }
};

/**
 * Derived class - Triangle
 */
class Triangle : public Shape {
private:
    double side1, side2, side3;

public:
    Triangle(const std::string& c, double s1, double s2, double s3)
        : Shape("Triangle", c), side1(s1), side2(s2), side3(s3) {
        std::cout << "Triangle constructor" << std::endl;
    }
    
    ~Triangle() override {
        std::cout << "Triangle destructor" << std::endl;
    }
    
    double calculateArea() const override {
        // Using Heron's formula
        double s = (side1 + side2 + side3) / 2;
        return sqrt(s * (s - side1) * (s - side2) * (s - side3));
    }
    
    double calculatePerimeter() const override {
        return side1 + side2 + side3;
    }
    
    void draw() const override {
        std::cout << "Drawing a " << color << " triangle with sides " 
                  << side1 << ", " << side2 << ", " << side3 << std::endl;
    }
    
    void displayInfo() const override {
        Shape::displayInfo();
        std::cout << "Sides: " << side1 << ", " << side2 << ", " << side3 << std::endl;
        std::cout << "Type: " << getTriangleType() << std::endl;
    }
    
    std::string getType() const override {
        return "Triangle";
    }
    
    // Triangle-specific methods
    std::string getTriangleType() const {
        if (side1 == side2 && side2 == side3) {
            return "Equilateral";
        } else if (side1 == side2 || side2 == side3 || side1 == side3) {
            return "Isosceles";
        } else {
            return "Scalene";
        }
    }
};

/**
 * Function demonstrating runtime polymorphism
 */
inline void processShape(const Shape& shape) {
    std::cout << "\n--- Processing Shape ---" << std::endl;
    shape.displayInfo();
    shape.draw();
    std::cout << "Shape type: " << shape.getType() << std::endl;
}

/**
 * Polymorphic container and operations
 */
class ShapeManager {
private:
    std::vector<std::shared_ptr<Shape>> shapes;

public:
    void addShape(std::shared_ptr<Shape> shape) {
        shapes.push_back(shape);
    }
    
    void drawAllShapes() const {
        std::cout << "\n--- Drawing All Shapes ---" << std::endl;
        for (const auto& shape : shapes) {
            shape->draw();
        }
    }
    
    void displayAllInfo() const {
        std::cout << "\n--- All Shapes Information ---" << std::endl;
        for (const auto& shape : shapes) {
            shape->displayInfo();
            std::cout << "---" << std::endl;
        }
    }
    
    double getTotalArea() const {
        double total = 0.0;
        for (const auto& shape : shapes) {
            total += shape->calculateArea();
        }
        return total;
    }
    
    std::vector<std::shared_ptr<Shape>> getShapesByType(const std::string& type) const {
        std::vector<std::shared_ptr<Shape>> result;
        for (const auto& shape : shapes) {
            if (shape->getType() == type) {
                result.push_back(shape);
            }
        }
        return result;
    }

    void removeShapesByColor(const std::string& color) {
        std::vector<std::shared_ptr<Shape>> remaining;
        for (const auto& shape : shapes) {
            if (shape->getColor() != color) {
                remaining.push_back(shape);
            }
        }
        shapes = remaining;
    }
    
    size_t getShapeCount() const {
        return shapes.size();
    }
};

/**
 * Interface-based polymorphism
 */
class Drawable {
public:
    virtual ~Drawable() = default;
    virtual void draw() const = 0;
    virtual std::string getDescription() const = 0;
};

class Movable {
public:
    virtual ~Movable() = default;
    virtual void move(double dx, double dy) = 0;
    virtual std::pair<double, double> getPosition() const = 0;
};

// Multiple inheritance for interfaces
class GameSprite : public Drawable, public Movable {
private:
    std::string name;
    double x, y;
    std::string texture;

public:
    GameSprite(const std::string& n, double posX, double posY, const std::string& tex)
        : name(n), x(posX), y(posY), texture(tex) {}
    
    // Implement Drawable interface
    void draw() const override {
        std::cout << "Drawing " << name << " at (" << x << ", " << y 
                  << ") with texture: " << texture << std::endl;
    }
    
    std::string getDescription() const override {
        return name + " sprite";
    }
    
    // Implement Movable interface
    void move(double dx, double dy) override {
        x += dx;
        y += dy;
        std::cout << name << " moved to (" << x << ", " << y << ")" << std::endl;
    }
    
    std::pair<double, double> getPosition() const override {
        return {x, y};
    }
    
    const std::string& getName() const { return name; }
};

} // namespace BasicConcepts

/**
 * ===============================================
 * INTERVIEW QUESTIONS AND ANSWERS
 * ===============================================
 * 
 * Q1: What is polymorphism and its types?
 * A1: Polymorphism means "many forms" - same interface, different implementations
 *     Types:
 *     - Compile-time: Function/operator overloading, templates
 *     - Runtime: Virtual functions, inheritance-based
 * 
 * Q2: What is the difference between compile-time and runtime polymorphism?
 * A2: - Compile-time: Resolved at compile time, faster, static binding
 *     - Runtime: Resolved at runtime, flexible, dynamic binding via vtable
 * 
 * Q3: What are virtual functions and how do they work?
 * A3: Virtual functions enable runtime polymorphism through:
 *     - vtable (virtual table) - array of function pointers
 *     - vptr (virtual pointer) - points to object's vtable
 *     - Late binding - function call resolved at runtime
 * 
 * Q4: What is a vtable?
 * A4: Virtual table is an array of function pointers created for each class
 *     with virtual functions. Each object has a vptr pointing to its class vtable.
 * 
 * Q5: What is function overloading vs overriding?
 * A5: - Overloading: Same name, different parameters (compile-time)
 *     - Overriding: Redefining virtual function in derived class (runtime)
 * 
 * Q6: What are pure virtual functions?
 * A6: Functions declared with "= 0", making the class abstract.
 *     Must be implemented by derived classes.
 * 
 * Q7: What is the cost of virtual functions?
 * A7: - Extra memory for vtable and vptr
 *     - Indirect function call overhead
 *     - Prevents some compiler optimizations
 *     - Usually negligible in most applications
 *
 * Q8: Can we have virtual constructors?
 * A8: No, constructors cannot be virtual because:
 *     - vtable is set up during construction
 *     - Object type is known at construction time
 *     - Use factory pattern for "virtual construction"
 *
 * Q9: What is object slicing?
 * A9: When derived object is assigned to base object, derived-specific
 *     data is "sliced off". Avoid by using pointers/references.
 */

// ======================= DEMONSTRATION FUNCTION =======================
inline void demonstratePolymorphism() {
    std::cout << "\n===== POLYMORPHISM DEMO =====\n" << std::endl;
    
    // Runtime Polymorphism
    std::cout << "1. Runtime Polymorphism (Virtual Functions):" << std::endl;
    std::vector<std::shared_ptr<BasicConcepts::Shape>> shapes;
    shapes.push_back(std::make_shared<BasicConcepts::Circle>("Red", 5.0));
    shapes.push_back(std::make_shared<BasicConcepts::Rectangle>("Blue", 4.0, 6.0));
    shapes.push_back(std::make_shared<BasicConcepts::Triangle>("Green", 3.0, 4.0, 5.0));

    for (const auto& shape : shapes) {
        shape->draw();
        std::cout << "Area: " << shape->calculateArea() << std::endl;
        std::cout << "Type: " << shape->getType() << std::endl;
        std::cout << std::endl;
    }
    
    // Compile-time Polymorphism - Function Overloading
    std::cout << "2. Compile-time Polymorphism (Function Overloading):" << std::endl;
    BasicConcepts::Calculator calc;
    std::cout << "add(5, 3) = " << calc.add(5, 3) << std::endl;
    std::cout << "add(2.5, 3.7) = " << calc.add(2.5, 3.7) << std::endl;
    std::cout << "add(1, 2, 3) = " << calc.add(1, 2, 3) << std::endl;
    std::cout << "add(\"Hello\", \"World\") = " << calc.add(std::string("Hello"), std::string("World")) << std::endl;
    
    // Polymorphic container
    std::cout << "\n3. Polymorphic Container (ShapeManager):" << std::endl;
    BasicConcepts::ShapeManager manager;
    manager.addShape(std::make_shared<BasicConcepts::Circle>("Red", 1.0));
    manager.addShape(std::make_shared<BasicConcepts::Rectangle>("Red", 2.0, 3.0));
    manager.addShape(std::make_shared<BasicConcepts::Rectangle>("Blue", 2.0, 2.0));
    manager.drawAllShapes();
    std::cout << "Total area: " << manager.getTotalArea() << std::endl;
    manager.removeShapesByColor("Red");
    std::cout << "Shapes left after removing red ones: " << manager.getShapeCount() << std::endl;

    // Interface-based polymorphism
    std::cout << "\n4. Interfaces (GameSprite is Drawable and Movable):" << std::endl;
    BasicConcepts::GameSprite hero("Hero", 0.0, 0.0, "hero.png");
    hero.draw();
    hero.move(5.0, 2.0);

    // Virtual Destructor Demo
    std::cout << "\n5. Virtual Destructor Importance:" << std::endl;
    {
        std::shared_ptr<BasicConcepts::Shape> shape = std::make_shared<BasicConcepts::Circle>("Blue", 3.0);
        shape->draw();
        // Proper cleanup with virtual destructor
    }
    std::cout << "Shape destroyed properly with virtual destructor" << std::endl;
}

#endif // POLYMORPHISM_HPP
