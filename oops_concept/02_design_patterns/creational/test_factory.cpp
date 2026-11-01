#include "factory.hpp"

int main() {
    std::cout << "🧪 TESTING DESIGN PATTERNS - Factory Pattern\n" << std::endl;

    demonstrateFactory();

    // The simple factory returns nullptr for a type it does not know
    std::shared_ptr<Shape> unknown = ShapeFactory::createShape("hexagon", 3.0);
    if (!unknown) {
        std::cout << "\nFactory correctly rejected unknown shape type: hexagon" << std::endl;
    }

    std::cout << "\n✅ Factory pattern test completed successfully!" << std::endl;
    return 0;
}

// Compile: g++ -std=c++17 test_factory.cpp -o test_factory
// Run: ./test_factory
