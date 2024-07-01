# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic

# Include directories
INCLUDES = -I/usr/include/SFML -I.

# Linker flags
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# Source files
SOURCES = Demo.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Executable
EXECUTABLE = complex_tree

# Default rule
all: $(EXECUTABLE)

# Rule to link the executable
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

# Rule to compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean rule
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

# Phony targets
.PHONY: all clean
