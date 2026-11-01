#include "singleton.hpp"

int main() {
    std::cout << "🧪 TESTING DESIGN PATTERNS - Singleton Pattern\n" << std::endl;
    
    demonstrateSingleton();
    
    std::cout << "\n✅ Singleton pattern test completed successfully!" << std::endl;
    return 0;
}

// Compile: g++ -std=c++17 test_singleton.cpp -o test_singleton
// Run: ./test_singleton
