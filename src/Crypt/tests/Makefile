CC = gcc

CFLAGS = 

LIBS = -lcrypto -lssl

SRC = test_crypt.c ../crypt.c ../../Utils/utils.c ../../Utils/error.c

TARGET = test_crypt

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LIBS)

clean:
	rm -f $(TARGET)

