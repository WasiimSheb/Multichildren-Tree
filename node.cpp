#include "node.hpp"

template <typename T>
Node<T>::Node(T val) : value(val) {}

template <typename T>
T Node<T>::get_value() const {
    return value;
}

template <typename T>
void Node<T>::add_child(Node<T>* child) {
    children.push_back(child);
}

// Explicit template instantiation
template class Node<double>;
