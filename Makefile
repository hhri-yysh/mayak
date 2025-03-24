CC = gcc
CFLAGS = -O3 -Wall -Wextra -std=c11 -D_POSIX_C_SOURCE=199309L -D_GNU_SOURCE

TARGET = mayak
SRC_DIR = src
LIB_DIR = lib
BUILD_DIR = build

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

BUILD_DIR:
	mkdir -p $(BUILD_DIR)

clean:
	rm -f $(BUILD_DIR)/*.o $(BUILD_DIR)/$(TARGET)
