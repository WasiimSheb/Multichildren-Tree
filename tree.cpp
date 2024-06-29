#include "tree.hpp"
#include "complex.hpp"

// Explicit instantiation of the Tree class for Complex type with k=2 (binary tree)
template class Tree<Complex, 2>;

// Explicit instantiation of the Tree class for Complex type with k=3 (ternary tree)
template class Tree<Complex, 3>;
