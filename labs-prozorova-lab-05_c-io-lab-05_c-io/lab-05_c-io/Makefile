CC := gcc

CFLAGS := -Iinclude -Wall -Wextra -Werror -c

TARGET := lab-05_c-io
all: obj $(TARGET)

obj:
	mkdir obj

$(TARGET): obj/clist.o obj/point_list.o src/main.c
	$(CC) -Iinclude -Wall -Wextra -Werror obj/clist.o obj/point_list.o src/main.c -o $(TARGET)

obj/clist.o: src/clist.c include/clist.h 
	$(CC) $(CFLAGS) src/clist.c -o obj/clist.o
	
obj/point_list.o: src/point_list.c include/point_list.h 
	$(CC) $(CFLAGS) src/point_list.c -o obj/point_list.o

.PHONY: all clean

clean:
	rm -rf obj/ $(TARGET)
