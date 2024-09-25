SRC_DIRS := Routing Utils Queue
OBJ_DIR := obj
BIN_DIR := bin

CC := gcc
CFLAGS := -Wall

SRC := $(shell find $(SRC_DIRS) -name '*.c')
OBJ := $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

TARGET := $(BIN_DIR)/test_prog

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
