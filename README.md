# Tree Data Structure Implementation

## Overview

This project implements a generic k-ary tree data structure in C++. It includes several tree traversal methods and visualizes the tree using the SFML library. The project supports various data types such as integers, strings, doubles, and custom complex numbers.

## Features

- **Generic k-ary Tree**: Supports any type of data and any number of children per node.
- **Tree Traversals**: Includes BFS, DFS, In-Order, Post-Order, Pre-Order, and Min-Heap traversals.
- **SFML Visualization**: Visualizes the tree structure using the SFML library.
- **Complex Number Support**: Provides support for complex numbers with overloaded operators.
- **Unit Tests**: Includes comprehensive unit tests using the doctest framework.

## Files

### Source Files

- `main.cpp`: Contains the main function demonstrating tree operations and visualization.
- `node.hpp`: Defines the `Node` class for tree nodes.
- `tree.hpp`: Defines the `Tree` class and various tree traversal iterators.
- `complex.hpp`: Defines the `Complex` class with overloaded operators.
- `test_tree.cpp`: Contains unit tests for the tree and node operations.

### Build Files

- `Makefile`: Defines the build and test process.


