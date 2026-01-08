#include "design_patterns/strategy.hpp"
#include <chrono>

int main() {
    std::cout << "🧪 TESTING DESIGN PATTERNS - Strategy Pattern\n" << std::endl;
    
    demonstrateStrategy();
    
    std::cout << "\n✅ Strategy pattern test completed successfully!" << std::endl;
    return 0;
}

// Compile: g++ -std=c++17 test_strategy.cpp -o test_strategy
// Run: ./test_strategy
