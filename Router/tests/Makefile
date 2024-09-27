CC = gcc

CFLAGS = -Wall -Wextra -g

SRC_DIR = ..
UTILS_DIR = ../../Utils

SRC = $(SRC_DIR)/*.c
UTILS = $(UTILS_DIR)/utils.c $(UTILS_DIR)/error.c
GLOBALS = ../../globals.c


TEST_SRC = test_router.c

OUTPUT = test_router

all: $(OUTPUT)

$(OUTPUT): $(TEST_SRC) $(SRC) $(UTILS)
	$(CC) $(CFLAGS) $(TEST_SRC) $(SRC) $(GLOBALS) $(UTILS) -o $(OUTPUT)

clean:
	rm -f $(OUTPUT)

