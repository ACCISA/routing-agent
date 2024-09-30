CC = gcc
CFLAGS = -Wall -g

TARGET = test_message

SRC_DIR = ..
UTILS_DIR = ../../Utils
ROUTER_DIR = ../../Router
GLOBALS_DIR = ../../

SRCS = test_message.c $(SRC_DIR)/message.c $(GLOBALS_DIR)/globals.c \
       $(UTILS_DIR)/utils.c $(UTILS_DIR)/error.c \
       $(ROUTER_DIR)/router.c $(ROUTER_DIR)/peer.c

all: $(TARGET)

$(TARGET):
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)

