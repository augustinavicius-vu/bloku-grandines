# Define the compiler and compiler flags
CXX := g++
CXXFLAGS := -Wall -g

# Target executable
TARGET := main

# Source and object directories
SRC_DIR := src
OBJ_DIR := obj

# Source files (all .cpp files in the src folder)
SRCS := $(SRC_DIR)/main.cpp

# Object files (place them in the obj folder, replacing .cpp with .o)
OBJS := $(OBJ_DIR)/main.o

# Default rule to build the executable
all: $(TARGET)

# Rule to link object files and create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile .cpp files into .o object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Ensure the obj directory exists
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)
	rm -rf $(OBJ_DIR)

# Phony targets (targets not associated with files)
.PHONY: all clean
