CC = gcc

CFLAGS = -std=c11  -Iinclude

SRC = src/main.c src/class.c src/course.c src/csv_parser.c src/data_saver.c src/list.c src/student.c

OBJ = $(SRC:.c=.o)

TARGET = PromoManage

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(TARGET)