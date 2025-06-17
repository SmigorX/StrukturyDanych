CC = gcc
CFLAGS = -Wall -Wextra -O2 -g
TARGET = hash_table_test
SOURCES = main.c HashTable.c HashingFunctions.c
HEADERS = HashTable.h HashingFunctions.h
OBJS = $(SOURCES:.c=.o)

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files to object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean build artifacts
clean:
	rm -f $(OBJS) $(TARGET)

# Run tests
test: $(TARGET)
	./$(TARGET)

# Phony targets (not files)
.PHONY: all clean test

