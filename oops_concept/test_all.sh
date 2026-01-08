#!/bin/bash

# C++ OOP Concepts - Comprehensive Testing Script
# This script compiles and runs all individual concept demonstrations

echo "=================================================="
echo "🚀 C++ OOP CONCEPTS - COMPREHENSIVE TESTING"
echo "=================================================="
echo ""

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Function to run a test
run_test() {
    local file=$1
    local name=$2
    
    echo -e "${BLUE}📋 Testing: $name${NC}"
    echo "Command: g++ -std=c++17 $file -o test && ./test"
    echo "----------------------------------------"
    
    if g++ -std=c++17 "$file" -o test 2>/dev/null; then
        if ./test; then
            echo -e "${GREEN}✅ $name - PASSED${NC}"
            rm -f test
        else
            echo -e "${RED}❌ $name - RUNTIME ERROR${NC}"
            rm -f test
            return 1
        fi
    else
        echo -e "${RED}❌ $name - COMPILATION ERROR${NC}"
        echo "Compilation details:"
        g++ -std=c++17 "$file" -o test
        return 1
    fi
    echo ""
}

# Test individual concepts
echo -e "${YELLOW}🧪 BASIC OOP CONCEPTS${NC}"
echo ""

run_test "test_basic.cpp" "Classes and Objects"
run_test "test_encapsulation.cpp" "Encapsulation"
run_test "test_inheritance.cpp" "Inheritance"
run_test "test_polymorphism.cpp" "Polymorphism"

echo -e "${YELLOW}🎓 ADVANCED OOP CONCEPTS${NC}"
echo ""

run_test "test_abstraction.cpp" "Abstraction"

echo -e "${YELLOW}🏗️ DESIGN PATTERNS${NC}"
echo ""

run_test "test_singleton.cpp" "Singleton Pattern"
run_test "test_factory.cpp" "Factory Pattern"
run_test "test_strategy.cpp" "Strategy Pattern"
run_test "test_adapter_decorator.cpp" "Adapter & Decorator Patterns"
run_test "test_observer.cpp" "Observer Pattern"

echo -e "${YELLOW}🚀 MODERN C++ FEATURES${NC}"
echo ""

run_test "test_smart_pointers.cpp" "Smart Pointers"
run_test "test_move_semantics.cpp" "Move Semantics"
run_test "test_exception_handling.cpp" "Exception Handling"

# Test comprehensive demos
echo -e "${YELLOW}🎯 COMPREHENSIVE DEMOS${NC}"
echo ""

run_test "main_simple_demo.cpp" "Simple OOP Demo"
run_test "main_guaranteed_working.cpp" "Complete Working Demo"
run_test "master_demo.cpp" "Master Demo"
run_test "test_comprehensive.cpp" "Comprehensive Test Suite"

echo "=================================================="
echo -e "${GREEN}🎉 ALL TESTS COMPLETED!${NC}"
echo "=================================================="
echo ""
echo -e "${BLUE}📚 INDIVIDUAL COMMANDS TO RUN EACH FILE:${NC}"
echo ""
echo "# Basic OOP Concepts:"
echo "g++ -std=c++17 test_basic.cpp -o test_basic && ./test_basic"
echo "g++ -std=c++17 test_encapsulation.cpp -o test_encapsulation && ./test_encapsulation"
echo "g++ -std=c++17 test_inheritance.cpp -o test_inheritance && ./test_inheritance"
echo "g++ -std=c++17 test_polymorphism.cpp -o test_polymorphism && ./test_polymorphism"
echo ""
echo "# Advanced OOP Concepts:"
echo "g++ -std=c++17 test_abstraction.cpp -o test_abstraction && ./test_abstraction"
echo ""
echo "# Design Patterns:"
echo "g++ -std=c++17 test_singleton.cpp -o test_singleton && ./test_singleton"
echo "g++ -std=c++17 test_factory.cpp -o test_factory && ./test_factory"
echo "g++ -std=c++17 test_strategy.cpp -o test_strategy && ./test_strategy"
echo "g++ -std=c++17 test_adapter_decorator.cpp -o test_adapter_decorator && ./test_adapter_decorator"
echo "g++ -std=c++17 test_observer.cpp -o test_observer && ./test_observer"
echo ""
echo "# Modern C++ Features:"
echo "g++ -std=c++17 test_smart_pointers.cpp -o test_smart_pointers && ./test_smart_pointers"
echo "g++ -std=c++17 test_move_semantics.cpp -o test_move_semantics && ./test_move_semantics"
echo "g++ -std=c++17 test_exception_handling.cpp -o test_exception_handling && ./test_exception_handling"
echo ""
echo "# Comprehensive Demos:"
echo "g++ -std=c++17 main_simple_demo.cpp -o simple_demo && ./simple_demo"
echo "g++ -std=c++17 main_guaranteed_working.cpp -o complete_demo && ./complete_demo"
echo "g++ -std=c++17 master_demo.cpp -o master_demo && ./master_demo"
echo "g++ -std=c++17 test_comprehensive.cpp -o comprehensive_test && ./comprehensive_test"
echo ""
echo -e "${YELLOW}💡 To run this test script: chmod +x test_all.sh && ./test_all.sh${NC}"
