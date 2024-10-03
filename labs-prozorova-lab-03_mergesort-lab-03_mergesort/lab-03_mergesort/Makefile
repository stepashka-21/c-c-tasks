CC := gcc

CFLAGS := -Iinclude -Wall -Wextra -Werror -c

TARGET := lab-03_mergesort
all: obj $(TARGET)

obj:
	mkdir obj

$(TARGET): obj/mergesort.o src/main.c
	$(CC) -Iinclude -Wall -Wextra -Werror obj/mergesort.o src/main.c -o $(TARGET)

obj/mergesort.o: src/mergesort.c include/mergesort.h 
	$(CC) $(CFLAGS) src/mergesort.c -o obj/mergesort.o

.PHONY: all clean

clean:
	rm -rf obj/ $(TARGET)
