CC = clang
CFLAGS = -Wall -Wextra -std=c11

TARGET = mayak
SRC_DIR = src
LIB_DIR = lib
BUILD_DIR = build

SRC = ($(SRC_DIR)/*.c)
OBJ = ($(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET) 

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(BUILD_DIR) $(TARGET)

