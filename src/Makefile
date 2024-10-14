SRC_DIRS := Router Server Message ReactorV2 Crypt Utils Queue
OBJ_DIR := obj
BIN_DIR := bin

CC := gcc
CFLAGS := -Wall -lssl -lcrypto

SRC := $(shell find $(SRC_DIRS) -name '*.c' ! -path '*/tests/*')
OBJ := $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

TARGET := $(BIN_DIR)/my_program

all: $(TARGET)

$(TARGET): $(OBJ) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean

