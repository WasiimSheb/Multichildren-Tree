#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <memory>
#include <sstream>

template <typename T>
class Node {
public:
    T key;
    std::vector<std::shared_ptr<Node<T>>> children;

    Node(T key) : key(key) {}
    T get_key() const { return key; }
    void add_child(std::shared_ptr<Node<T>> child) { children.push_back(child); }

    std::string toString() const {
        std::stringstream ss;
        ss << key;
        return ss.str();
    }
};

#endif // NODE_HPP
