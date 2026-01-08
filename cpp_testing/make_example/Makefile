# Makefile for Calculator Project (Make Example)
# This demonstrates traditional make build system

# Compiler settings
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -O2
INCLUDES = -Iinclude

# Directories
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build

# Source files
SOURCES = $(SRC_DIR)/main.cpp $(SRC_DIR)/calculator.cpp
OBJECTS = $(BUILD_DIR)/main.o $(BUILD_DIR)/calculator.o

# Target executable
TARGET = $(BUILD_DIR)/calculator

# Default target
all: $(TARGET)

# Rule to build the main executable
$(TARGET): $(OBJECTS) | $(BUILD_DIR)
	@echo "🔗 Linking executable..."
	$(CXX) $(OBJECTS) -o $(TARGET)
	@echo "✅ Make build complete! Executable: $(TARGET)"

# Rule to compile main.cpp
$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp $(INCLUDE_DIR)/calculator.hpp | $(BUILD_DIR)
	@echo "🔨 Compiling main.cpp..."
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/main.o

# Rule to compile calculator.cpp
$(BUILD_DIR)/calculator.o: $(SRC_DIR)/calculator.cpp $(INCLUDE_DIR)/calculator.hpp | $(BUILD_DIR)
	@echo "🔨 Compiling calculator.cpp..."
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $(SRC_DIR)/calculator.cpp -o $(BUILD_DIR)/calculator.o

# Create build directory if it doesn't exist
$(BUILD_DIR):
	@echo "📁 Creating build directory..."
	mkdir -p $(BUILD_DIR)

# Clean build artifacts
clean:
	@echo "🧹 Cleaning build directory..."
	rm -rf $(BUILD_DIR)
	@echo "✅ Clean complete!"

# Run the program
run: $(TARGET)
	@echo "🚀 Running the calculator program..."
	./$(TARGET)

# Build and run in one command
build-and-run: clean all run

# Debug build
debug: CXXFLAGS += -g -DDEBUG
debug: $(TARGET)
	@echo "🐛 Debug build completed with symbols!"

# Show build info
info:
	@echo "📋 Make Build System Information:"
	@echo "   Compiler: $(CXX)"
	@echo "   Flags: $(CXXFLAGS)"
	@echo "   Include dirs: $(INCLUDES)"
	@echo "   Source files: $(SOURCES)"
	@echo "   Target: $(TARGET)"

# Help target
help:
	@echo "🔧 Available Make targets:"
	@echo "  all          - Build the calculator program (default)"
	@echo "  clean        - Remove build artifacts"
	@echo "  run          - Build and run the program"
	@echo "  build-and-run - Clean, build, and run"
	@echo "  debug        - Build with debug symbols"
	@echo "  info         - Show build configuration"
	@echo "  help         - Show this help message"

# Declare phony targets
.PHONY: all clean run build-and-run debug info help

# Make will rebuild if header files change
$(OBJECTS): $(INCLUDE_DIR)/calculator.hpp
