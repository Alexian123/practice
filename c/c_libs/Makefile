CC=gcc
CFLAGS=-Wall -g -Iinclude
LIBS=-lm -pthread

RM=/bin/rm
RMFLAGS=-rf

SRC=src
OBJ=obj
TEST=test
EXPORT=export

SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
TEST_BIN=$(TEST)/main
TEST_SRC=$(TEST)/main.c

all: $(TEST_BIN)

$(TEST_BIN): $(TEST_SRC) $(OBJS) $(OBJ)
	$(CC) $(CFLAGS) $(TEST_SRC) $(OBJS) -o $@ $(LIBS)

$(OBJ)/%.o: $(SRC)/%.c $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@ 

$(OBJ):
	mkdir -p $@

run: $(TEST_BIN)
	./$(TEST_BIN)

clean:
	find . -type f | xargs touch
	$(RM) $(RMFLAGS) $(OBJ) $(BIN) $(EXPORT)

.PHONY: all run clean