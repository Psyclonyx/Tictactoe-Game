# Makefile for Tic-Tac-Toe Game

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
TARGET = main
SOURCE = tictactoe2.c

# Default target
all: $(TARGET)

# Compile the game
$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)

# Clean build artifacts
clean:
	rm -f $(TARGET)

# Rebuild everything
rebuild: clean all

# Run the game
run: $(TARGET)
	./$(TARGET)

# Phony targets
.PHONY: all clean rebuild run
