#ifndef POLYMORPHISM_HPP
#define POLYMORPHISM_HPP

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <typeinfo>

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
 * 3. What are virtual fun    intContainer.add(10);
    intContainer.add(20);
    intContainer.add(30);
    intContainer.display();
    
    BasicConcepts::Container<std::string> stringContainer;
    stringContainer.add("Hello");
    stringContainer.add("Template");
    stringContainer.add("World");
    stringContainer.display();
    
    // Operator Overloading
    std::cout << "\n4. Operator Overloading:" << std::endl;
    BasicConcepts::Point p1(3, 4);
    BasicConcepts::Point p2(1, 2);
    
    BasicConcepts::Point p3 = p1 + p2;
    std::cout << "p1: (" << p1.x << ", " << p1.y << ")" << std::endl;
    std::cout << "p2: (" << p2.x << ", " << p2.y << ")" << std::endl;
    std::cout << "p1 + p2 = (" << p3.x << ", " << p3.y << ")" << std::endl;ey work?
 * 4. What is a vtable (virtual table)?
 * 5. What is function overloading vs overriding?
 * 6. What are pure virtual functions and abstract classes?
 * 7. What is dynamic_cast and when to use it?
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
    
    // Template function - compile-time polymorphism
    template<typename T>
    T multiply(T a, T b) {
        std::cout << "Template multiply: " << a << " * " << b;
        return a * b;
    }
};

/**
 * Operator Overloading - Compile-time polymorphism
 */
class Complex {
private:
    double real, imaginary;

public:
    Complex(double r = 0, double i = 0) : real(r), imaginary(i) {}
    
    // Operator overloading
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imaginary + other.imaginary);
    }
    
    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imaginary - other.imaginary);
    }
    
    Complex operator*(const Complex& other) const {
        return Complex(real * other.real - imaginary * other.imaginary,
                      real * other.imaginary + imaginary * other.real);
    }
    
    bool operator==(const Complex& other) const {
        return real == other.real && imaginary == other.imaginary;
    }
    
    // Assignment operator
    Complex& operator=(const Complex& other) {
        if (this != &other) {
            real = other.real;
            imaginary = other.imaginary;
        }
        return *this;
    }
    
    // Stream operators
    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << c.real;
        if (c.imaginary >= 0) os << "+";
        os << c.imaginary << "i";
        return os;
    }
    
    friend std::istream& operator>>(std::istream& is, Complex& c) {
        is >> c.real >> c.imaginary;
        return is;
    }
    
    // Getters
    double getReal() const { return real; }
    double getImaginary() const { return imaginary; }
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
void processShape(const Shape& shape) {
    std::cout << "\n--- Processing Shape ---" << std::endl;
    shape.displayInfo();
    shape.draw();
    std::cout << "Shape type: " << shape.getType() << std::endl;
}

void processShapePointer(const Shape* shape) {
    if (shape) {
        std::cout << "\n--- Processing Shape Pointer ---" << std::endl;
        shape->displayInfo();
        shape->draw();
        
        // Demonstrate dynamic_cast
        if (const Circle* circle = dynamic_cast<const Circle*>(shape)) {
            std::cout << "This is a circle with radius: " << circle->getRadius() << std::endl;
        } else if (const Rectangle* rect = dynamic_cast<const Rectangle*>(shape)) {
            std::cout << "This is a rectangle " << rect->getWidth() 
                      << "x" << rect->getHeight() << std::endl;
            if (rect->isSquare()) {
                std::cout << "It's actually a square!" << std::endl;
            }
        } else if (const Triangle* tri = dynamic_cast<const Triangle*>(shape)) {
            std::cout << "This is a " << tri->getTriangleType() << " triangle" << std::endl;
        }
    }
}

/**
 * Advanced Polymorphism - Function Objects (Functors)
 */
class Functor {
private:
    int multiplier;

public:
    Functor(int m) : multiplier(m) {}
    
    // Overload function call operator
    int operator()(int x) const {
        return x * multiplier;
    }
    
    // Overload for different types
    double operator()(double x) const {
        return x * multiplier;
    }
};

/**
 * Template-based polymorphism
 */
template<typename T>
class Container {
private:
    std::vector<T> data;

public:
    void add(const T& item) {
        data.push_back(item);
    }
    
    T get(size_t index) const {
        if (index < data.size()) {
            return data[index];
        }
        throw std::out_of_range("Index out of range");
    }
    
    size_t size() const {
        return data.size();
    }
    
    // Template method
    template<typename U>
    void addConverted(const U& item) {
        data.push_back(static_cast<T>(item));
    }
    
    // Function template for operations
    template<typename Func>
    void applyFunction(Func f) {
        for (auto& item : data) {
            item = f(item);
        }
    }
};

/**
 * Virtual Function Table Demonstration
 */
class VTableDemo {
public:
    virtual void func1() { std::cout << "VTableDemo::func1" << std::endl; }
    virtual void func2() { std::cout << "VTableDemo::func2" << std::endl; }
    virtual void func3() { std::cout << "VTableDemo::func3" << std::endl; }
    
    void nonVirtualFunc() { std::cout << "VTableDemo::nonVirtualFunc" << std::endl; }
    
    virtual ~VTableDemo() = default;
};

class DerivedVTable : public VTableDemo {
public:
    void func1() override { std::cout << "DerivedVTable::func1" << std::endl; }
    // func2 not overridden - uses base version
    void func3() override { std::cout << "DerivedVTable::func3" << std::endl; }
    
    void derivedSpecific() { std::cout << "DerivedVTable::derivedSpecific" << std::endl; }
};

/**
 * Polymorphic container and operations
 */
class ShapeManager {
private:
    std::vector<std::unique_ptr<Shape>> shapes;

public:
    void addShape(std::unique_ptr<Shape> shape) {
        shapes.push_back(std::move(shape));
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
    
    std::vector<Shape*> getShapesByType(const std::string& type) const {
        std::vector<Shape*> result;
        for (const auto& shape : shapes) {
            if (shape->getType() == type) {
                result.push_back(shape.get());
            }
        }
        return result;
    }
    
    void removeShapesByColor(const std::string& color) {
        shapes.erase(
            std::remove_if(shapes.begin(), shapes.end(),
                [&color](const std::unique_ptr<Shape>& shape) {
                    return shape->getColor() == color;
                }),
            shapes.end()
        );
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
 * Q7: When to use dynamic_cast?
 * A7: - Safe downcasting in inheritance hierarchy
 *     - Returns nullptr if cast fails (for pointers)
 *     - Throws std::bad_cast if cast fails (for references)
 *     - Requires polymorphic classes (with virtual functions)
 * 
 * Q8: What is the cost of virtual functions?
 * A8: - Extra memory for vtable and vptr
 *     - Indirect function call overhead
 *     - Prevents some compiler optimizations
 *     - Usually negligible in most applications
 * 
 * Q9: Can we have virtual constructors?
 * A9: No, constructors cannot be virtual because:
 *     - vtable is set up during construction
 *     - Object type is known at construction time
 *     - Use factory pattern for "virtual construction"
 * 
 * Q10: What is object slicing?
 * A10: When derived object is assigned to base object, derived-specific
 *      data is "sliced off". Avoid by using pointers/references.
 */

// ======================= DEMONSTRATION FUNCTION =======================
inline void demonstratePolymorphism() {
    std::cout << "\n===== POLYMORPHISM DEMO =====\n" << std::endl;
    
    // Runtime Polymorphism
    std::cout << "1. Runtime Polymorphism (Virtual Functions):" << std::endl;
    std::vector<std::unique_ptr<BasicConcepts::Shape>> shapes;
    shapes.push_back(std::make_unique<BasicConcepts::Circle>("Red", 5.0));
    shapes.push_back(std::make_unique<BasicConcepts::Rectangle>("Blue", 4.0, 6.0));
    shapes.push_back(std::make_unique<BasicConcepts::Triangle>("Green", 3.0, 4.0, 5.0));
    
    for (const auto& shape : shapes) {
        shape->draw();
        std::cout << "Area: " << shape->calculateArea() << std::endl;
        std::cout << "Type: " << typeid(*shape).name() << std::endl;
        std::cout << std::endl;
    }
    
    // Compile-time Polymorphism - Function Overloading
    std::cout << "2. Compile-time Polymorphism (Function Overloading):" << std::endl;
    BasicConcepts::Calculator calc;
    std::cout << "add(5, 3) = " << calc.add(5, 3) << std::endl;
    std::cout << "add(2.5, 3.7) = " << calc.add(2.5, 3.7) << std::endl;
    std::cout << "add(1, 2, 3) = " << calc.add(1, 2, 3) << std::endl;
    std::cout << "add(\"Hello\", \"World\") = " << calc.add(std::string("Hello"), std::string("World")) << std::endl;
    
    // Template Polymorphism
    std::cout << "\n3. Template Polymorphism:" << std::endl;
    BasicConcepts::Container<int> intContainer;
    intContainer.add(10);
    intContainer.add(20);
    intContainer.add(30);
    std::cout << "Integer container size: " << intContainer.size() << std::endl;
    
    BasicConcepts::Container<std::string> stringContainer;
    stringContainer.add("Hello");
    stringContainer.add("Template");
    stringContainer.add("World");
    std::cout << "String container size: " << stringContainer.size() << std::endl;
    
    // Operator Overloading
    std::cout << "\n4. Basic Template Features:" << std::endl;
    std::cout << "Demonstrated template polymorphism with different container types" << std::endl;
    
    // Virtual Destructor Demo
    std::cout << "\n5. Virtual Destructor Importance:" << std::endl;
    {
        std::unique_ptr<BasicConcepts::Shape> shape = std::make_unique<BasicConcepts::Circle>("Blue", 3.0);
        shape->draw();
        // Proper cleanup with virtual destructor
    }
    std::cout << "Shape destroyed properly with virtual destructor" << std::endl;
}

#endif // POLYMORPHISM_HPP
