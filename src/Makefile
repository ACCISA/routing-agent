# Directories
SRC_DIRS := Router Server Message ReactorV2 Crypt Utils Queue
OBJ_DIR := obj
BIN_DIR := bin

# Compiler and Flags
CC := gcc
CFLAGS := -Wall -lssl -lcrypto

# Find all source files, excluding those in any 'tests' subdirectory
SRC := $(shell find $(SRC_DIRS) -name '*.c' ! -path '*/tests/*')
OBJ := $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

# Target binary name
TARGET := $(BIN_DIR)/my_program

# Default target
all: $(TARGET)

# Link the object files into the final binary
$(TARGET): $(OBJ) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# Pattern rule for compiling .c files into .o files
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Create output directories
$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

# Clean up object and binary directories
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean

