# on windows, use git bash

CC := gcc
LD := gcc

CFLAGS += -std=c99 -pedantic-errors
CFLAGS += -Wall -Wextra -Wunused -Wformat=2

LDFLAGS +=

SRC_DIR := ./src
OUT_DIR := ./build

SRC := $(wildcard $(SRC_DIR)/*.c)
SRC += $(wildcard $(SRC_DIR)/**/*.c)

OBJ := $(SRC:%.c=%.o)

TARGET := $(OUT_DIR)/brainfuck

build: $(TARGET)

run: build
	$(TARGET) $(ARGS)
	
clean:
	rm -rf $(OBJ) $(OUT_DIR)

$(TARGET): $(OBJ)
	@mkdir -p $(OUT_DIR)
	$(LD) $^ $(LDFLAGS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $< $(CFLAGS) -c -o $@
