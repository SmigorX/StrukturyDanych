CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = 
SOURCES = $(wildcard *.c)  # Get all .c files in current directory
OBJECTS = $(patsubst %.c,build/%.o,$(SOURCES))
EXECUTABLE = ./output/linked_lists_program

all: $(EXECUTABLE)

# Link all objects into executable
$(EXECUTABLE): $(OBJECTS) | output
	$(CC) $(LDFLAGS) $^ -o $@

# Compile .c to .o
build/%.o: %.c | build
	@mkdir -p $(@D)  # Ensure output directory exists
	$(CC) $(CFLAGS) -c $< -o $@

# Create directories
build:
	mkdir -p build

output:
	mkdir -p output

clean:
	rm -rf build output

.PHONY: all clean
