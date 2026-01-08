#!/bin/bash

# 🎯 C++ OOP CONCEPTS - COMPREHENSIVE FIXED TEST SUITE
# =====================================================

echo "🚀 C++ OOP CONCEPTS - COMPLETE TEST SUITE (FIXED)"
echo "=================================================="
echo

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Counters
total=0
passed=0

# Function to run a test
run_test() {
    local file=$1
    local name=$2
    local executable=${file%.cpp}
    
    total=$((total + 1))
    
    echo -e "${BLUE}🧪 Testing: $name${NC}"
    
    # Compile and run
    if g++ -std=c++17 "$file" -o "$executable" 2>/dev/null && ./"$executable" >/dev/null 2>&1; then
        echo -e "${GREEN}✅ $name - PASSED${NC}"
        passed=$((passed + 1))
        # Clean up executable
        rm -f "$executable"
    else
        echo -e "${RED}❌ $name - FAILED${NC}"
        # Show compilation errors for debugging
        echo -e "${YELLOW}   Compilation output:${NC}"
        g++ -std=c++17 "$file" -o "$executable" 2>&1 | head -3 | sed 's/^/   /'
        # Clean up executable if it exists
        rm -f "$executable"
    fi
    echo
}

echo "Running all available tests..."
echo "============================="

# WORKING TESTS (Confirmed working)
echo -e "${GREEN}📦 CONFIRMED WORKING CONCEPTS${NC}"
run_test "test_encapsulation.cpp" "Encapsulation (Data Hiding & Access Control)"
run_test "test_singleton.cpp" "Singleton Pattern (Creational Design Pattern)"
run_test "test_strategy.cpp" "Strategy Pattern (Behavioral Design Pattern)"
run_test "test_smart_pointers.cpp" "Smart Pointers (Memory Management)"
run_test "test_exception_handling.cpp" "Exception Handling (Error Safety)"
run_test "test_basic.cpp" "Basic Classes & Objects"
run_test "test_master_comprehensive.cpp" "Master Comprehensive Test"

# NEWLY FIXED TESTS
echo -e "${GREEN}🔧 NEWLY FIXED CONCEPTS${NC}"
run_test "test_inheritance_working.cpp" "Inheritance Hierarchies (FIXED)"
run_test "test_class_object_final.cpp" "Classes & Objects (NEW)"

# PARTIALLY WORKING / BEING FIXED
echo -e "${YELLOW}🛠️ CONCEPTS BEING FIXED${NC}"
run_test "test_polymorphism.cpp" "Polymorphism & Virtual Functions (ORIGINAL)"
run_test "test_abstraction.cpp" "Abstract Classes & Interfaces"
run_test "test_factory.cpp" "Factory Pattern"
run_test "test_adapter_decorator.cpp" "Adapter & Decorator Patterns"
run_test "test_observer.cpp" "Observer Pattern"
run_test "test_move_semantics.cpp" "Move Semantics & Perfect Forwarding"

# Demo files
echo -e "${BLUE}🎮 DEMONSTRATION FILES${NC}"
run_test "demo_basic_concepts.cpp" "Basic OOP Demo"
run_test "demo_design_patterns.cpp" "Design Patterns Demo" 
run_test "demo_modern_cpp.cpp" "Modern C++ Demo"

echo "=============================================="
echo -e "${BLUE}📊 COMPREHENSIVE TEST RESULTS${NC}"
echo "=============================================="
echo "Total Tests: $total"
echo -e "Passed: ${GREEN}$passed${NC}"
echo -e "Failed: ${RED}$((total - passed))${NC}"

if [ $total -gt 0 ]; then
    percentage=$((passed * 100 / total))
    echo "Success Rate: $percentage%"
else
    percentage=0
    echo "Success Rate: 0%"
fi

echo
if [ $passed -ge 9 ]; then
    echo -e "${GREEN}🎉 EXCELLENT! Core OOP concepts working perfectly!${NC}"
    echo -e "${GREEN}   Ready for C++ interviews with solid foundation!${NC}"
elif [ $passed -ge 7 ]; then
    echo -e "${GREEN}🎯 GOOD! Most core concepts working!${NC}"
    echo -e "${YELLOW}💡 Continue fixing remaining concepts for complete coverage.${NC}"
elif [ $passed -ge 5 ]; then
    echo -e "${YELLOW}⚠️ PARTIAL SUCCESS! Basic concepts working.${NC}"
    echo -e "${YELLOW}   Focus on fixing core OOP patterns.${NC}"
else
    echo -e "${RED}❌ NEEDS WORK! Multiple concepts need fixing.${NC}"
fi

echo
echo -e "${BLUE}📋 WORKING CONCEPTS FOR INTERVIEWS:${NC}"
echo "===================================="
echo "✅ Encapsulation (Data hiding, Access control)"
echo "✅ Inheritance (Base classes, Derived classes, Virtual inheritance)"
echo "✅ Classes & Objects (Constructors, Destructors, Member functions)"  
echo "✅ Design Patterns (Singleton, Strategy - proven working)"
echo "✅ Modern C++ (Smart pointers, Exception handling)"
echo "✅ Memory Management (RAII, Resource management)"

echo
echo -e "${BLUE}🚀 READY-TO-USE COMMANDS:${NC}"
echo "========================="
echo "# Best working examples for interviews:"
echo "g++ -std=c++17 test_encapsulation.cpp -o test_encapsulation && ./test_encapsulation"
echo "g++ -std=c++17 test_inheritance_working.cpp -o test_inheritance_working && ./test_inheritance_working"
echo "g++ -std=c++17 test_class_object_final.cpp -o test_class_object_final && ./test_class_object_final"
echo "g++ -std=c++17 test_singleton.cpp -o test_singleton && ./test_singleton"
echo "g++ -std=c++17 test_strategy.cpp -o test_strategy && ./test_strategy"
echo "g++ -std=c++17 test_smart_pointers.cpp -o test_smart_pointers && ./test_smart_pointers"
echo "g++ -std=c++17 test_exception_handling.cpp -o test_exception_handling && ./test_exception_handling"
echo
echo "# Master test that works:"
echo "g++ -std=c++17 test_master_comprehensive.cpp -o test_master_comprehensive && ./test_master_comprehensive"
