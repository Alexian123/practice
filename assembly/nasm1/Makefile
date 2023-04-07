ASM=/usr/bin/nasm
ASM_FLAGS=-f elf

LD=/usr/bin/ld
LD_FLAGS=-m elf_i386

RM=/bin/rm
RMFLAGS=-rf

SRC=src
OBJ=obj
BIN=bin

SRCS=$(wildcard $(SRC)/*.asm)
OBJS=$(patsubst $(SRC)/%.asm, $(OBJ)/%.o, $(SRCS))
BINS=$(patsubst $(OBJ)/%.o, $(BIN)/%, $(OBJS))

all: $(BINS)

$(BINS): $(SRCS) $(OBJS)

$(BIN)/%: $(OBJ)/%.o $(BIN)
	$(LD) $(LD_FLAGS) $< -o $@

$(BIN):
	mkdir -p $@

$(OBJ)/%.o: $(SRC)/%.asm $(OBJ)
	$(ASM) $(ASM_FLAGS) $< -o $@

$(OBJ):
	mkdir -p $@

clean:
	find . -type f | xargs touch
	$(RM) $(RMFLAGS) $(OBJ) $(BIN)

.PHONY: all clean
