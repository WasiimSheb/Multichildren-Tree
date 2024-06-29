#ifndef NODE_HPP
#define NODE_HPP

#include <vector>

template <typename T>
class Node {
public:
    T value;
    std::vector<Node<T>*> children;

    Node(T val);

    T get_value() const;

    void add_child(Node<T>* child);
};

#endif // NODE_HPP
