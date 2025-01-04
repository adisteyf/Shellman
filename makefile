CC = gcc
CFLAGS = -Wall
BUILD_DIR = bin
TARGET = ${BUILD_DIR}/pacage
SRC = main.cpp

# Default target to build the program
all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(TARGET): $(SRC)
	@echo "BUILDING"
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

install: $(TARGET)
	@echo "Installing to /usr/local/bin"
	mv $(TARGET) /usr/local/bin

# Clean up build artifacts
clean:
	rm -rf $(BUILD_DIR)

# Phony targets
.PHONY: all clean install
