# Compiler
CXX := g++

# Directories
SRC_DIR := src
BIN_DIR := bin
OBJ_DIR := obj
INCLUDE_DIR := include

# Output
TARGET := $(BIN_DIR)/raycasting

# Source files
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp) \
             $(wildcard $(SRC_DIR)/Math/*.cpp) \
             $(wildcard $(SRC_DIR)/Draw/*.cpp) \
             $(wildcard $(SRC_DIR)/Game/*.cpp)

# Object files (corresponding to source files)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Compiler flags
CXXFLAGS := -O3 -march=native -fomit-frame-pointer -pipe -fdiagnostics-color=always -I$(INCLUDE_DIR)
LDFLAGS := -lSDL2 -lSDL2_image

# Build target
$(TARGET): $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJ_FILES) -o $(TARGET) $(LDFLAGS)

# Rule to build object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target
.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) $(TARGET)
