CC := gcc
CFLAGS := -Wall
SRC := main.c globals.c Router/*.c Instructor/*.c Server/*.c Message/*.c Reactor/*.c Crypt/*.c Utils/*.c Queue/*.c Config/*.c
TARGET := main

all:
	$(CC) $(CFLAGS) $(SRC) -lssl -lcrypto -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean

