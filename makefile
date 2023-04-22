CC=gcc
CFLAGS=-g
CFDEBUG=-Wall -g -DDebug -pedantic
LDFLAGS=-lncurses -l:libpcg_random.a
TARGET=cursejack

OBJ_DIR=./obj
BIN_DIR=./bin
INCLUDE=-I src/include
SRC=$(wildcard src/*.c)
OBJECTS=$(SRC:%.c=$(OBJ_DIR)/%.o)

all: build $(BIN_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(BIN_DIR)/$(TARGET): $(OBJECTS)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$(TARGET) $^ $(LDFLAGS)

.PHONY: all build debug clean info

build:
	mkdir -p $(BIN_DIR)
	mkdir -p $(OBJ_DIR)

debug: $(CFLAGS) += $(CFDEBUG)
debug: all

clean:
	rm -rvf $(OBJ_DIR)/*
	rm -rvf $(BIN_DIR)/*

info:
	echo "[*] Application dir: ${APP_DIR}     "
	echo "[*] Object dir:      ${OBJ_DIR}     "
	echo "[*] Sources:         ${SRC}         "
	echo "[*] Objects:         ${OBJECTS}     "