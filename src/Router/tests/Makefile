CC = gcc

CFLAGS = -Wall -Wextra -g

SRC_DIR = ..
UTILS_DIR = ../../Utils
MESSAGE_DIR = ../../Message

SRC = $(SRC_DIR)/*.c
UTILS = $(UTILS_DIR)/utils.c $(UTILS_DIR)/error.c
GLOBALS = ../../globals.c
MESSAGE = $(MESSAGE_DIR)/message.c

TEST_SRC = test_router.c
TEST2_SRC = test_router_sequence.c

OUTPUT = test_router
OUTPUT2 = test_router_sequence

all: $(OUTPUT)

$(OUTPUT): $(TEST_SRC) $(SRC) $(UTILS)
	$(CC) $(CFLAGS) $(TEST_SRC) $(SRC) $(GLOBALS) $(UTILS) -o $(OUTPUT)

test2: $(TEST2_SRC) $(SRC) $(UTILS) $(MESSAGE)
	$(CC) $(CFLAGS) $(TEST2_SRC) $(SRC) $(GLOBALS) $(UTILS) $(MESSAGE) -o $(OUTPUT2)

clean:
	rm -f $(OUTPUT) $(OUTPUT2)

