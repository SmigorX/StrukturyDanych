CC = gcc
CFLAGS = -Wall -I./Double_Linked_List -I./Single_Linked_List -I./Dynamic_Array
LDFLAGS = 
SRC_DIRS = Double_Linked_List Single_Linked_List Dynamic_Array
EXECUTABLE = ./output/linked_lists_program

# Recursively find all .c files in SRC_DIRS and include main.c
SOURCES = $(shell find $(SRC_DIRS) -name '*.c') main.c

# Preserve subdirectory structure in build dir (e.g., Double_Linked_List/file.c -> build/Double_Linked_List/file.o)
OBJECTS = $(patsubst %.c,build/%.o,$(SOURCES))

all: $(EXECUTABLE)

# Link all objects into executable
$(EXECUTABLE): $(OBJECTS) | output
	$(CC) $(LDFLAGS) $^ -o $@

# Compile .c to .o, preserving subdirectories
build/%.o: %.c | build
	@mkdir -p $(@D)  # Ensure output subdirectory exists
	$(CC) $(CFLAGS) -c $< -o $@

# Create directories
build:
	mkdir -p build

output:
	mkdir -p output

clean:
	rm -rf build output

.PHONY: all clean
