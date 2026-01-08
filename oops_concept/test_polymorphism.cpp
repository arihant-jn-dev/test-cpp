#include "basic/polymorphism.hpp"
#include <iostream>
#include <memory>
#include <vector>

int main() {
    std::cout << "🧪 TESTING BASIC OOP CONCEPTS - Polymorphism\n" << std::endl;
    
    try {
        std::cout << "===== POLYMORPHISM DEMO =====\n" << std::endl;
        
        // Test basic polymorphism with correct constructors
        std::cout << "1. Basic Polymorphism (Shape hierarchy):" << std::endl;
        BasicConcepts::Circle circle("Red", 5.0);  // Color, radius
        BasicConcepts::Rectangle rectangle("Blue", 4.0, 6.0);  // Color, width, height
        BasicConcepts::Triangle triangle("Green", 3.0, 4.0, 5.0);  // Color, side1, side2, side3
        
        std::cout << "Circle area: " << circle.calculateArea() << std::endl;
        std::cout << "Rectangle area: " << rectangle.calculateArea() << std::endl;
        std::cout << "Triangle area: " << triangle.calculateArea() << std::endl;
        
        std::cout << "\n2. Polymorphic behavior via base pointers:" << std::endl;
        std::vector<std::unique_ptr<BasicConcepts::Shape>> shapes;
        shapes.push_back(std::make_unique<BasicConcepts::Circle>("Yellow", 3.0));
        shapes.push_back(std::make_unique<BasicConcepts::Rectangle>("Purple", 5.0, 2.0));
        shapes.push_back(std::make_unique<BasicConcepts::Triangle>("Orange", 6.0, 8.0, 10.0));
        
        for (const auto& shape : shapes) {
            shape->draw();
            std::cout << "Area: " << shape->calculateArea() << std::endl;
        }
        
        std::cout << "\n✅ Polymorphism tests completed successfully!\n" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "❌ Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
