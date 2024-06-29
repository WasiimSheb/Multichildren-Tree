#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <iostream>

template <typename T>
class Node {
public:
    Node(T value) : value(value) {}

    T get_value() const { return value; }
    std::vector<Node*> children;

private:
    T value;
};

#endif
