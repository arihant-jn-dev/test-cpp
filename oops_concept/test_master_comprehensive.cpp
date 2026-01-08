#include <iostream>
#include <string>

// Function to run individual tests
int runTestCommand(const std::string& command, const std::string& testName) {
    std::cout << "🧪 Running " << testName << "..." << std::endl;
    int result = system(command.c_str());
    if (result == 0) {
        std::cout << "✅ " << testName << " - PASSED" << std::endl;
    } else {
        std::cout << "❌ " << testName << " - FAILED" << std::endl;
    }
    return result;
}

int main() {
    std::cout << "\n🎯 COMPREHENSIVE TEST OF ALL WORKING C++ OOP CONCEPTS" << std::endl;
    std::cout << "=======================================================" << std::endl;
    
    int totalTests = 0;
    int passedTests = 0;
    
    // List of working test files
    struct TestCase {
        std::string filename;
        std::string description;
    };
    
    TestCase tests[] = {
        {"test_encapsulation.cpp", "Encapsulation (Data Hiding & Access Control)"},
        {"test_singleton.cpp", "Singleton Pattern (Creational)"},
        {"test_strategy.cpp", "Strategy Pattern (Behavioral)"},
        {"test_smart_pointers.cpp", "Smart Pointers (Modern C++)"},
        {"test_exception_handling.cpp", "Exception Handling (Error Management)"}
    };
    
    // Run each test
    for (const auto& test : tests) {
        totalTests++;
        std::string compileCmd = "g++ -std=c++17 " + test.filename + " -o " + 
                                test.filename.substr(0, test.filename.find('.'));
        std::string runCmd = "./" + test.filename.substr(0, test.filename.find('.'));
        std::string fullCmd = compileCmd + " && " + runCmd + " > /dev/null 2>&1";
        
        if (runTestCommand(fullCmd, test.description) == 0) {
            passedTests++;
        }
        std::cout << std::endl;
    }
    
    // Print comprehensive results
    std::cout << "🏆 COMPREHENSIVE TEST RESULTS" << std::endl;
    std::cout << "==============================" << std::endl;
    std::cout << "Total Tests: " << totalTests << std::endl;
    std::cout << "Passed: " << passedTests << std::endl;
    std::cout << "Failed: " << (totalTests - passedTests) << std::endl;
    std::cout << "Success Rate: " << (totalTests > 0 ? (passedTests * 100 / totalTests) : 0) << "%" << std::endl;
    
    if (passedTests == totalTests) {
        std::cout << "\n🎉 ALL TESTS PASSED!" << std::endl;
        std::cout << "Your C++ OOP implementation covers:" << std::endl;
        std::cout << "📦 Core OOP Concepts (Encapsulation)" << std::endl;
        std::cout << "🏗️  Design Patterns (Singleton, Strategy)" << std::endl;
        std::cout << "🚀 Modern C++ Features (Smart Pointers, Exception Handling)" << std::endl;
        std::cout << "\nPerfect for C++ OOP interviews! 🚀" << std::endl;
    } else {
        std::cout << "\n⚠️  Some tests failed. Check individual test outputs for details." << std::endl;
    }
    
    std::cout << "\n📋 INTERVIEW PREPARATION SUMMARY:" << std::endl;
    std::cout << "=================================" << std::endl;
    std::cout << "✅ Encapsulation: Private data, public methods, access control" << std::endl;
    std::cout << "✅ Singleton Pattern: Single instance, global access" << std::endl;
    std::cout << "✅ Strategy Pattern: Runtime algorithm selection" << std::endl;
    std::cout << "✅ Smart Pointers: Memory management, RAII" << std::endl;
    std::cout << "✅ Exception Handling: Error safety, custom exceptions" << std::endl;
    
    return (passedTests == totalTests) ? 0 : 1;
}
