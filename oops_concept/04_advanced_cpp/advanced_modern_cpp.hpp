#ifndef ADVANCED_MODERN_CPP_HPP
#define ADVANCED_MODERN_CPP_HPP

#include <iostream>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>

#include "../03_modern_cpp/smart_pointers.hpp"

/**
 * ===============================================
 * ADVANCED MODERN C++ EXTRAS
 * ===============================================
 *
 * Moved here from 03_modern_cpp/: unique_ptr for arrays, unique_ptr with a
 * custom deleter (lambda + decltype), and a conditional noexcept template
 * with perfect forwarding. In LLD code use std::vector instead of arrays and
 * the default deleter.
 */

namespace AdvancedCpp {

inline void demonstrateUniquePtrExtras() {
    std::cout << "\n--- UNIQUE_PTR EXTRAS ---" << std::endl;
    
    // Array version
    std::cout << "1. unique_ptr with arrays:" << std::endl;
    std::unique_ptr<int[]> numbers = std::make_unique<int[]>(5);
    for (int i = 0; i < 5; i++) {
        numbers[i] = i * 10;
        std::cout << "numbers[" << i << "] = " << numbers[i] << std::endl;
    }
    
    // Custom deleter
    std::cout << "\n2. unique_ptr with custom deleter:" << std::endl;
    auto customDeleter = [](Resource* r) {
        std::cout << "🔥 Custom deleter called for: " << r->getName() << std::endl;
        delete r;
    };
    
    std::unique_ptr<Resource, decltype(customDeleter)> resource3(
        new Resource("FileHandle", 3), customDeleter);
    resource3->use();
}

// Function with conditional noexcept (moved from exception_handling.hpp)
template<typename T>
auto conditionalNoexcept(T&& value) noexcept(std::is_nothrow_move_constructible_v<T>) {
    return std::forward<T>(value);
}

} // namespace AdvancedCpp

// ======================= DEMONSTRATION FUNCTION =======================
inline void demonstrateAdvancedModernCpp() {
    std::cout << "\n===== ADVANCED MODERN C++ DEMO =====\n" << std::endl;
    
    AdvancedCpp::demonstrateUniquePtrExtras();
    
    std::cout << "\n--- CONDITIONAL NOEXCEPT + PERFECT FORWARDING ---" << std::endl;
    std::string text = "forwarded string";
    std::string result = AdvancedCpp::conditionalNoexcept(std::move(text));
    std::cout << "conditionalNoexcept returned: " << result << std::endl;
}

#endif // ADVANCED_MODERN_CPP_HPP
