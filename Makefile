TARGET = main
BUILD = build
BIN = bin
INCLUDE = include
SRC = src
CC = gcc
CFLAGS = -I$(INCLUDE)


# List all source files
SRCS := $(wildcard $(SRC)/*.c)

# Derive object file names from source file names
OBJS := $(patsubst $(SRC)/%.c, $(BUILD)/%.o, $(SRCS))

# Default target
all: $(BIN)/$(TARGET)

# Rule to make the executable
$(BIN)/$(TARGET): $(OBJS)
	$(CC) $^ -o $@ `sdl2-config --cflags --libs`

# Rule to make object files
$(BUILD)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Create necessary directories
$(shell mkdir -p $(BUILD) $(BIN))

# Clean rule
clean:
	rm -rf $(BUILD) $(BIN)

.PHONY: all clean
