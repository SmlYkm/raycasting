# Compiler
CXX := g++

# Directories
SRC_DIR := src
BIN_DIR := bin
INCLUDE_DIR := include

# Output
TARGET := $(BIN_DIR)/raycasting

# Source files
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp) \
             $(wildcard $(SRC_DIR)/Math/*.cpp) \
             $(wildcard $(SRC_DIR)/Rendering/*.cpp) \
             $(wildcard $(SRC_DIR)/Game/*.cpp)

# Compiler flags
CXXFLAGS := -fdiagnostics-color=always -g -I$(INCLUDE_DIR)

# Libraries
LIBS := -lsfml-graphics -lsfml-window -lsfml-system

# Build target
$(TARGET): $(SRC_FILES)
	$(CXX) $(CXXFLAGS) $(SRC_FILES) -o $(TARGET) $(LIBS)

# Clean target
.PHONY: clean
clean:
	rm -f $(TARGET)
