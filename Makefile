CC = gcc
CFLAGS = -Wall -I./Double_Linked_List -I./Single_Linked_List
LDFLAGS = 
SRC_DIRS = Double_Linked_List Single_Linked_List
EXECUTABLE_NAME = linked_lists_program
EXECUTABLE = ./output/$(EXECUTABLE_NAME)

# Find all .c files in source directories and main.c
SOURCES = $(wildcard $(addsuffix /*.c, $(SRC_DIRS))) main.c

# Generate object file names in build directory
OBJECTS = $(addprefix build/, $(notdir $(SOURCES:.c=.o)))

all: $(EXECUTABLE)

# Link all object files into executable in output directory
$(EXECUTABLE): $(OBJECTS) | output
	$(CC) $(LDFLAGS) $^ -o $@

# Compile .c to .o in build directory
build/%.o: %.c | build
	$(CC) $(CFLAGS) -c $< -o $@

# Create directories if they don't exist
build:
	mkdir -p build

output:
	mkdir -p output

clean:
	rm -rf build output

.PHONY: all clean

# Help make find source files in multiple directories
vpath %.c $(SRC_DIRS) .
