CC=gcc
CFLAGS=-Wall -Iinclude

SRC=src
INPUT=input

SRCS=$(wildcard $(SRC)/*.c)
INPUTS=$(wildcard $(INPUT)/*.in)
BIN=main

all: $(BIN)

$(BIN): $(SRCS) $(INPUTS)
	$(CC) $(CFLAGS) $(SRCS) -o $@

run: $(BIN)
	./$(BIN)

clean:
	rm -f $(BIN)

.PHONY: all run clean