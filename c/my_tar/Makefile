CC=gcc
CFLAGS=-Wall

mytar: mytar.o main.c
	$(CC) $(CFLAGS) $^ -o $@

mytar.o: mytar.c mytar.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f mytar.o mytar

.PHONY: clean