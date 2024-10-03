CC := gcc

CFLAGS := -Iinclude -Wall -Wextra -Werror -c

TARGET := lab-04_intrusive-list
all: obj $(TARGET)

obj:
	mkdir obj

$(TARGET): obj/clist.o src/main.c
	$(CC) -Iinclude -Wall -Wextra -Werror obj/clist.o src/main.c -o $(TARGET)

obj/clist.o: src/clist.c include/clist.h 
	$(CC) $(CFLAGS) src/clist.c -o obj/clist.o

.PHONY: all clean

clean:
	rm -rf obj/ $(TARGET)
