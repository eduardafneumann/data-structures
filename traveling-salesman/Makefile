CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -g

SRC_FOLDER = ./src
SRC_FILES = $(wildcard $(SRC_FOLDER)/*.c $(SRC_FOLDER)/**/*.c $(SRC_FOLDER)/**/**/*.c)

BUILD_FOLDER = ./build
TARGET_FILE = ./bin/traveling-salesman

OBJ_FOLDER = $(BUILD_FOLDER)/obj
OBJ_FILES = $(patsubst $(SRC_FOLDER)/%.c,$(OBJ_FOLDER)/%.o,$(SRC_FILES))

INC = -I$(SRC_FOLDER)
CFLAGS += $(INC)

all: $(OBJ_FILES)
	mkdir -p $(dir $(TARGET_FILE))
	$(CC) -o $(TARGET_FILE) $^ $(CFLAGS)

$(OBJ_FILES): $(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.c
	mkdir -p $(dir $@)
	$(CC) -o $@ $^ $(CFLAGS) -c

clean:
	rm -r $(BUILD_FOLDER)

run:
	./$(TARGET_FILE)

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET_FILE)
