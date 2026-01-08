# CMakeLists.txt for Calculator Project
# This demonstrates modern cmake build system

# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(Calculator 
    VERSION 1.0
    DESCRIPTION "A calculator demonstrating cmake build system"
    LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler-specific options
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    # Add warning flags for GCC and Clang
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Set build type to Release if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Add different flags for different build types
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

# Include directories
include_directories(include)

# Source files
set(SOURCES
    src/main.cpp
    src/calculator.cpp
)

# Header files (for IDE support)
set(HEADERS
    include/calculator.hpp
)

# Create the executable
add_executable(calculator ${SOURCES} ${HEADERS})

# Set target properties
set_target_properties(calculator PROPERTIES
    OUTPUT_NAME "calculator"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Custom target to run the program
add_custom_target(run
    COMMAND calculator
    DEPENDS calculator
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    COMMENT "Running the calculator program..."
)

# Install rules
install(TARGETS calculator
    RUNTIME DESTINATION bin
)

# Add a custom target for formatting (if clang-format is available)
find_program(CLANG_FORMAT clang-format)
if(CLANG_FORMAT)
    add_custom_target(format
        COMMAND ${CLANG_FORMAT} -i ${SOURCES} ${HEADERS}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Formatting source code with clang-format"
    )
endif()

# Print build information
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "C++ flags: ${CMAKE_CXX_FLAGS}")

# Option to build with static linking
option(STATIC_LINKING "Enable static linking" OFF)
if(STATIC_LINKING)
    target_link_libraries(calculator -static)
    message(STATUS "Static linking enabled")
endif()

# Enable testing if requested
option(BUILD_TESTS "Build unit tests" OFF)
if(BUILD_TESTS)
    enable_testing()
    message(STATUS "Testing enabled")
    # Add test subdirectory here if you have tests
endif()
