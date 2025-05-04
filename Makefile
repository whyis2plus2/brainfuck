# on windows, use git bash

CC := gcc
LD := gcc

CFLAGS += -std=c99 -pedantic-errors
CFLAGS += -Wall -Wextra -Wunused -Wformat=2

LDFLAGS +=

SRC_DIR := ./src
OBJ_DIR := ./build
OUT_DIR := ./build/out

SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

TARGET := $(OUT_DIR)/brainfuck

build: $(TARGET)

run: build
	$(TARGET) $(ARGS)
	
clean:
	rm -rf $(OBJ_DIR) $(OUT_DIR)

$(TARGET): $(OBJ)
	@mkdir -p $(OUT_DIR)
	$(LD) $^ $(LDFLAGS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $< $(CFLAGS) -c -o $@
