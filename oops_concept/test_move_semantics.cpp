#include "other_concepts/move_semantics.hpp"
#include <cstring>

int main() {
    std::cout << "🧪 TESTING OTHER CONCEPTS - Move Semantics\n" << std::endl;
    
    demonstrateMoveSemantics();
    
    std::cout << "\n✅ Move semantics test completed successfully!" << std::endl;
    return 0;
}

// Compile: g++ -std=c++17 test_move_semantics.cpp -o test_move_semantics
// Run: ./test_move_semantics
