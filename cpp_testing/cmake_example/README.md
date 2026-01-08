# CMake Build System Example

This project demonstrates the **modern CMake build system** for C++ projects.

## 📁 Project Structure

```
cmake_example/
├── include/
│   └── calculator.hpp    # Header file with class declarations
├── src/
│   ├── main.cpp         # Main application
│   └── calculator.cpp   # Calculator implementation
├── build/               # Build directory (created during build)
├── CMakeLists.txt       # CMake build configuration
└── README.md           # This file
```

## 🔧 What is CMake?

**CMake** is a modern cross-platform build system generator that:
- Uses `CMakeLists.txt` with higher-level, readable syntax
- Generates native build files (Makefiles, Visual Studio projects, etc.)
- Works on Windows, Linux, macOS with the same configuration
- Automatically handles dependencies and modern C++ features

## 🚀 How to Build and Run

### Basic Commands

```bash
# Create build directory and configure
mkdir build && cd build
cmake ..

# Build the project
cmake --build .

# Run the program
./bin/calculator
```

### Using CMake Targets

```bash
# Configure and build in one step
cmake --build build

# Run using CMake target (from project root)
cd build && cmake --build . --target run

# Clean build
cmake --build . --target clean

# Show help
cmake --build . --target help
```

### Advanced Options

```bash
# Configure with specific build type
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake -DCMAKE_BUILD_TYPE=Release ..

# Configure with options
cmake -DSTATIC_LINKING=ON ..
cmake -DBUILD_TESTS=ON ..

# Parallel build (use 4 cores)
cmake --build . -j 4

# Install the program
cmake --build . --target install
```

## 📋 Step-by-Step Instructions

### Method 1: Standard CMake Workflow

1. **Navigate to this directory:**
   ```bash
   cd cmake_example
   ```

2. **Create and enter build directory:**
   ```bash
   mkdir build
   cd build
   ```

3. **Configure the project:**
   ```bash
   cmake ..
   ```
   You'll see output like:
   ```
   -- The CXX compiler identification is AppleClang 17.0.0
   -- Detecting CXX compiler ABI info
   -- Detecting CXX compiler ABI info - done
   🔧 CMake Build Configuration:
      Build type: Release
      C++ compiler: /usr/bin/c++
      C++ standard: 17
   -- Configuring done
   -- Generating done
   -- Build files have been written to: .../build
   ```

4. **Build the project:**
   ```bash
   cmake --build .
   ```

5. **Run the program:**
   ```bash
   ./bin/calculator
   ```

### Method 2: One-Command Build

```bash
# From the cmake_example directory
cmake -B build && cmake --build build && ./build/bin/calculator
```

## 🎯 How CMake Works

### 1. **Configuration Phase**
- Reads `CMakeLists.txt`
- Detects compiler and system
- Generates native build files (like Makefiles)

### 2. **Build Phase**
- Uses generated build files
- Compiles source code
- Links executables

### 3. **CMakeLists.txt Structure**
```cmake
# Project setup
cmake_minimum_required(VERSION 3.10)
project(MyProject)

# Configuration
set(CMAKE_CXX_STANDARD 17)
include_directories(include)

# Targets
add_executable(myapp src/main.cpp src/utils.cpp)
```

## 🔍 Key CMake Concepts

### **Targets**
```cmake
# Executable target
add_executable(calculator src/main.cpp src/calculator.cpp)

# Library target
add_library(mylib src/library.cpp)

# Custom target
add_custom_target(run COMMAND calculator)
```

### **Properties**
```cmake
# Set target properties
set_target_properties(calculator PROPERTIES
    OUTPUT_NAME "calc"
    RUNTIME_OUTPUT_DIRECTORY "bin"
)
```

### **Variables**
```cmake
set(SOURCES src/main.cpp src/utils.cpp)  # Custom variable
set(CMAKE_CXX_STANDARD 17)               # Built-in variable
```

### **Options**
```cmake
option(BUILD_TESTS "Build unit tests" OFF)
if(BUILD_TESTS)
    enable_testing()
endif()
```

## 💡 Advantages of CMake

✅ **Cross-platform** - Same config works everywhere  
✅ **IDE Integration** - Generates Visual Studio, Xcode projects  
✅ **Modern C++** - Built-in support for C++11/14/17/20  
✅ **Package Management** - Easy integration with libraries  
✅ **Scalable** - Handles large, complex projects well  
✅ **Active Development** - Constantly improving  

## ⚠️ CMake Considerations

❌ **Learning curve** - More concepts to understand initially  
❌ **Abstraction** - Less direct control over compiler commands  
❌ **Dependency** - Need CMake installed on build machines  

## 🆚 CMake vs Make

| Feature | Make | CMake |
|---------|------|--------|
| **Config file** | Makefile | CMakeLists.txt |
| **Cross-platform** | No | Yes |
| **Syntax** | Low-level, complex | High-level, readable |
| **IDE support** | Limited | Excellent |
| **Dependency detection** | Manual | Automatic |
| **Modern C++** | Manual setup | Built-in |

## 🔧 CMake Build Types

### **Debug Build**
```bash
cmake -DCMAKE_BUILD_TYPE=Debug ..
# Adds: -g -O0 -DDEBUG
```

### **Release Build**
```bash
cmake -DCMAKE_BUILD_TYPE=Release ..
# Adds: -O3 -DNDEBUG
```

### **Custom Configuration**
```bash
cmake -DCMAKE_CXX_FLAGS="-Wall -Wextra" ..
```

## 🎓 Learning Exercises

1. **Try different build types** - Debug vs Release, see the difference
2. **Modify CMakeLists.txt** - Change compiler flags, add options
3. **Generate different build systems**:
   ```bash
   cmake -G "Unix Makefiles" ..
   cmake -G "Ninja" ..        # If Ninja is installed
   ```
4. **Use CMake GUI** (if installed) for visual configuration

## 🔍 Useful CMake Commands

```bash
# Show available generators
cmake --help

# Show cache variables
cmake -L

# Show advanced cache variables
cmake -LA

# Clean configure (remove cache)
rm -rf build && mkdir build && cd build && cmake ..

# Verbose build output
cmake --build . --verbose
```

## 🔗 Next Steps

- Learn about `find_package()` for external libraries
- Explore CMake testing with CTest
- Try advanced features like custom commands and generators
- Compare with the `make_example` to understand differences

---

**CMake is perfect for:**
- Cross-platform development
- Modern C++ projects
- IDE integration
- Large, complex projects
- Team development with mixed environments
