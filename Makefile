CC := gcc
CFLAGS := -std=c99 -Wall

OBJ := src/logger.o

all: $(OBJ)
	mv $(OBJ) suclog.o
	#$(CC) -c $(CFLAGS) $(OBJ) -o suclog.o

example: $(OBJ) example/example.o
	$(CC) $(CFLAGS) $^ -o test

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm *.o
	rm test


