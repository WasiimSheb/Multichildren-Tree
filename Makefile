//wasimshebalny@gmail.com
# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -pedantic

# Include directories
INCLUDES = -I/usr/include/SFML -I.

# Linker flags
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# Source files
SOURCES = Demo.cpp
TEST_SOURCES = test.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)

# Executable
EXECUTABLE = complex_tree
TEST_EXECUTABLE = test_tree

# Default rule
all: $(EXECUTABLE) $(TEST_EXECUTABLE)

# Rule to link the executable
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

# Rule to link the test executable
$(TEST_EXECUTABLE): $(TEST_OBJECTS)
	$(CXX) $(TEST_OBJECTS) -o $@ $(LDFLAGS)

# Rule to compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Run tests
test: $(TEST_EXECUTABLE)
	./$(TEST_EXECUTABLE)

# Clean rule
clean:
	rm -f $(OBJECTS) $(TEST_OBJECTS) $(EXECUTABLE) $(TEST_EXECUTABLE)

# Phony targets
.PHONY: all test clean
