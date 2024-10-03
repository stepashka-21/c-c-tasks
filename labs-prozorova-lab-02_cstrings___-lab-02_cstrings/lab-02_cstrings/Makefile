CC := gcc

CFLAGS := -Iinclude -Wall -Wextra -Werror -c

TARGET := lab-02_cstrings
all: obj $(TARGET)

obj:
	mkdir obj

$(TARGET): obj/str.o obj/test_str.o src/test.c
	$(CC) -Iinclude -Wall -Wextra -Werror obj/str.o obj/test_str.o src/test.c -o $(TARGET)

obj/str.o: src/str.c include/str.h 
	$(CC) $(CFLAGS) src/str.c -o obj/str.o

obj/test_str.o: src/test_str.c include/test_str.h
	$(CC) $(CFLAGS) src/test_str.c -o obj/test_str.o

.PHONY: all clean

clean:
	rm -rf obj/ $(TARGET)
