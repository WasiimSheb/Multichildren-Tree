# Define the compiler to use
CXX = g++

# Define the flags to pass to the compiler
CXXFLAGS = -std=c++11 -Wall -Wextra

# Define the libraries to link
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# Define the target executable
TARGET = tree_example

# Define the source files
SRCS = Demo.cpp node.cpp tree.cpp

# Define the object files
OBJS = $(SRCS:.cpp=.o)

# Default target to build the executable
all: $(TARGET)

# Rule to build the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Rule to build object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up the generated files
clean:
	rm -f $(TARGET) $(OBJS)

# Declare the 'clean' target as a phony target
.PHONY: all clean
