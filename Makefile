CC = gcc

CFLAGS = -std=c11 -Iinclude

SRC = $(shell find src -type f -name "*.c")

OBJ = $(SRC:.c=.o)

TARGET = PromoManage

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean run