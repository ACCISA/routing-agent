
CC = gcc
CFLAGS = -Wall -g  # Compiler flags: enable all warnings and include debugging info
SRC = ../queue.c ../../Utils/error.c ../../Utils/utils.c test_queue.c  # Source files
OBJ = queue.o error.o utils.o test_queue.o  # Object files
TARGET = test_queue  # Output binary

all: $(TARGET)

$(TARGET): $(OBJ)
		$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

queue.o: ../queue.c
		$(CC) $(CFLAGS) -c ../queue.c

error.o: ../../Utils/error.c
		$(CC) $(CFLAGS) -c ../../Utils/error.c

utils.o: ../../Utils/utils.c
		$(CC) $(CFLAGS) -c ../../Utils/utils.c

test_queue.o: test_queue.c
		$(CC) $(CFLAGS) -c test_queue.c

clean:
		rm -f $(OBJ) $(TARGET)

