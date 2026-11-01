#include "observer.hpp"
#include <map>

int main() {
    std::cout << "🧪 TESTING DESIGN PATTERNS - Observer Pattern\n" << std::endl;
    
    demonstrateObserver();
    
    std::cout << "\n✅ Observer pattern test completed successfully!" << std::endl;
    return 0;
}

// Compile: g++ -std=c++17 test_observer.cpp -o test_observer
// Run: ./test_observer
