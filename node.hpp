/**
 * @file node.hpp
 * @brief Declaration of the Node class for representing nodes in a tree.
 * @date 2024-06-30
 * @version 1.0
 * @details
 * This file contains the declaration of the Node class, which is used to represent 
 * nodes in a tree structure. Each node stores a key of type T and has a list of child nodes.
 * 
 * Contact: wasimshebalny@gmail.com
 */

#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <sstream>

/**
 * @class Node
 * @brief A class to represent a node in a tree.
 * 
 * This class provides methods for creating nodes, adding child nodes, and 
 * converting the node's key to a string representation.
 * 
 * @tparam T The type of the key stored in the node.
 */
template <typename T>
class Node {
public:
    T key; ///< The key stored in the node.
    std::vector<Node<T>*> children; ///< The list of child nodes.

    /**
     * @brief Construct a new Node object.
     * 
     * @param key The key to be stored in the node.
     */
    Node(T key) : key(key) {}

    /**
     * @brief Get the key stored in the node.
     * 
     * @return T The key stored in the node.
     */
    T get_key() const { return key; }

    /**
     * @brief Add a child node to the current node.
     * 
     * @param child Pointer to the child node to be added.
     */
    void add_child(Node<T>* child) { children.push_back(child); }

    /**
     * @brief Convert the node's key to a string representation.
     * 
     * @return std::string The string representation of the node's key.
     */
    std::string toString() const {
        std::stringstream ss;
        ss << key;
        return ss.str();
    }
};

#endif // NODE_HPP
