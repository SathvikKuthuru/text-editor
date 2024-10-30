# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++17

# Libraries
LIBS = -lSDL2 -lSDL2_ttf

# Directories
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

# Executable name
TARGET = $(BIN_DIR)/text_editor

# Source files
SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/Application.cpp $(SRC_DIR)/Window.cpp \
       $(SRC_DIR)/Renderer.cpp $(SRC_DIR)/TextEditor.cpp

# Object files
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Default target
all: $(TARGET)

# Build target
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

# Build object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all clean
