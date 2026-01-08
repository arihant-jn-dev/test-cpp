# Basic C++ Example

This folder contains the original simple C++ files demonstrating basic compilation and execution without build systems.

## Files
- `main.cpp` - Main program file
- `math_utils.hpp` - Header file with function declarations
- `math_utils.cpp` - Implementation file with function definitions
- `test_exe` - Compiled executable (if present)

## Compilation
This example was compiled manually using:
```bash
g++ -o test_exe main.cpp math_utils.cpp
```

## What's Next?
Check out the `../make_cmake_example/` directory to see how the same type of project structure can be managed using Make and CMake build systems.

This basic example shows the fundamental concepts of:
- Header files (`.hpp`)
- Source files (`.cpp`)
- Manual compilation with g++
- Function declarations vs definitions
- Linking multiple source files

The make_cmake_example builds upon these concepts to show why build systems are essential for larger projects.
