# CMakeLists.txt for Calculator Project (CMake Example)
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
    message(STATUS "Build type not specified, defaulting to Release")
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
    COMMENT "🚀 Running the calculator program..."
)

# Custom target for clean build and run
add_custom_target(build-and-run
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target clean
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}
    COMMAND calculator
    DEPENDS calculator
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    COMMENT "🔄 Clean, build, and run..."
)

# Install rules
install(TARGETS calculator
    RUNTIME DESTINATION bin
)

# Print build information
message(STATUS "🔧 CMake Build Configuration:")
message(STATUS "   Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "   C++ compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "   C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "   Install prefix: ${CMAKE_INSTALL_PREFIX}")

# Option to build with static linking
option(STATIC_LINKING "Enable static linking" OFF)
if(STATIC_LINKING)
    target_link_libraries(calculator -static)
    message(STATUS "   Static linking: ENABLED")
else()
    message(STATUS "   Static linking: DISABLED")
endif()

# Enable testing if requested
option(BUILD_TESTS "Build unit tests" OFF)
if(BUILD_TESTS)
    enable_testing()
    message(STATUS "   Testing: ENABLED")
else()
    message(STATUS "   Testing: DISABLED")
endif()

# Add a custom target for showing help
add_custom_target(show-help
    COMMAND ${CMAKE_COMMAND} -E echo "🔧 Available CMake targets:"
    COMMAND ${CMAKE_COMMAND} -E echo "  all          - Build the calculator program (default)"
    COMMAND ${CMAKE_COMMAND} -E echo "  clean        - Remove build artifacts"
    COMMAND ${CMAKE_COMMAND} -E echo "  run          - Build and run the program"
    COMMAND ${CMAKE_COMMAND} -E echo "  build-and-run - Clean, build, and run"
    COMMAND ${CMAKE_COMMAND} -E echo "  install      - Install the program"
    COMMAND ${CMAKE_COMMAND} -E echo "  show-help    - Show this help message"
    COMMENT "Showing available targets..."
)
