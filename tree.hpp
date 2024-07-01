/**
 * @file tree.hpp
 * @brief Declaration of the Tree class for representing k-ary trees and various traversal iterators.
 * @date 2024-06-30
 * @version 1.0
 * @details
 * This file contains the declaration of the Tree class, which represents a k-ary tree. It provides 
 * methods for adding nodes and various iterators for traversing the tree (BFS, DFS, In-Order, 
 * Post-Order, Pre-Order, and Min-Heap).
 * 
 * Contact: wasimshebalny@gmail.com
 */

#ifndef TREE_HPP
#define TREE_HPP

#include "node.hpp"
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>
#include <iostream>

/**
 * @class Tree
 * @brief A class to represent a k-ary tree.
 * 
 * This class provides methods for creating a tree, adding nodes, and traversing the tree 
 * using various iterators.
 * 
 * @tparam T The type of the key stored in the nodes.
 * @tparam k The maximum number of children per node. Default is 2 (binary tree).
 */
template <typename T, int k = 2>
class Tree {
private:
    Node<T>* root; ///< Pointer to the root node of the tree.

public:
    /**
     * @brief Construct a new Tree object.
     * 
     * Initializes the tree with no root.
     */
    Tree() : root(nullptr) {}

    /**
     * @brief Add a root node to the tree.
     * 
     * @param root_node The node to be added as the root.
     */
    void add_root(Node<T>& root_node) {
        root = &root_node;
    }

    /**
     * @brief Add a child node to a specified parent node.
     * 
     * @param parent_node The parent node.
     * @param sub_node The child node to be added.
     */
    void add_sub_node(Node<T>& parent_node, Node<T>& sub_node) {
        Node<T>* parent = find_node(root, parent_node);
        if (parent && parent->children.size() < k) {
            parent->add_child(&sub_node);
        }
    }

    /**
     * @brief Find a node in the tree.
     * 
     * @param current The current node in the search.
     * @param target The target node to find.
     * @return Node<T>* Pointer to the found node or nullptr if not found.
     */
    Node<T>* find_node(Node<T>* current, Node<T>& target) {
        if (!current) return nullptr;
        if (current->get_key() == target.get_key()) return current;

        for (auto& child : current->children) {
            auto found = find_node(child, target);
            if (found) return found;
        }

        return nullptr;
    }

    /**
     * @class BFSIterator
     * @brief An iterator for traversing the tree in breadth-first order.
     */
    class BFSIterator {
    public:
        /**
         * @brief Construct a new BFSIterator object.
         * 
         * @param root The root node of the tree.
         */
        BFSIterator(Node<T>* root) {
            if (root) queue.push(root);
        }

        /**
         * @brief Inequality operator to compare two iterators.
         * 
         * @param other The other iterator to compare to.
         * @return true If the iterators are not equal.
         * @return false If the iterators are equal.
         */
        bool operator!=(const BFSIterator& other) const {
            return !queue.empty();
        }

        /**
         * @brief Increment the iterator.
         * 
         * @return BFSIterator& Reference to the incremented iterator.
         */
        BFSIterator& operator++() {
            auto node = queue.front();
            queue.pop();
            for (auto& child : node->children) {
                queue.push(child);
            }
            return *this;
        }

        /**
         * @brief Dereference operator to access the current node.
         * 
         * @return Node<T>& Reference to the current node.
         */
        Node<T>& operator*() const {
            return *queue.front();
        }

        /**
         * @brief Arrow operator to access the current node.
         * 
         * @return Node<T>* Pointer to the current node.
         */
        Node<T>* operator->() const {
            return queue.front();
        }

    private:
        std::queue<Node<T>*> queue; ///< Queue for BFS traversal.
    };

    /**
     * @brief Get an iterator to the beginning of the BFS traversal.
     * 
     * @return BFSIterator An iterator to the beginning of the BFS traversal.
     */
    BFSIterator begin_bfs() const {
        return BFSIterator(root);
    }

    /**
     * @brief Get an iterator to the end of the BFS traversal.
     * 
     * @return BFSIterator An iterator to the end of the BFS traversal.
     */
    BFSIterator end_bfs() const {
        return BFSIterator(nullptr);
    }

    /**
     * @class DFSIterator
     * @brief An iterator for traversing the tree in depth-first order.
     */
    class DFSIterator {
    public:
        /**
         * @brief Construct a new DFSIterator object.
         * 
         * @param root The root node of the tree.
         */
        DFSIterator(Node<T>* root) {
            if (root) stack.push(root);
        }

        /**
         * @brief Inequality operator to compare two iterators.
         * 
         * @param other The other iterator to compare to.
         * @return true If the iterators are not equal.
         * @return false If the iterators are equal.
         */
        bool operator!=(const DFSIterator& other) const {
            return !stack.empty();
        }

        /**
         * @brief Increment the iterator.
         * 
         * @return DFSIterator& Reference to the incremented iterator.
         */
        DFSIterator& operator++() {
            auto node = stack.top();
            stack.pop();
            for (auto it = node->children.rbegin(); it != node->children.rend(); ++it) {
                stack.push(*it);
            }
            return *this;
        }

        /**
         * @brief Dereference operator to access the current node.
         * 
         * @return Node<T>& Reference to the current node.
         */
        Node<T>& operator*() const {
            return *stack.top();
        }

        /**
         * @brief Arrow operator to access the current node.
         * 
         * @return Node<T>* Pointer to the current node.
         */
        Node<T>* operator->() const {
            return stack.top();
        }

    private:
        std::stack<Node<T>*> stack; ///< Stack for DFS traversal.
    };

    /**
     * @brief Get an iterator to the beginning of the DFS traversal.
     * 
     * @return DFSIterator An iterator to the beginning of the DFS traversal.
     */
    DFSIterator begin_dfs() const {
        return DFSIterator(root);
    }

    /**
     * @brief Get an iterator to the end of the DFS traversal.
     * 
     * @return DFSIterator An iterator to the end of the DFS traversal.
     */
    DFSIterator end_dfs() const {
        return DFSIterator(nullptr);
    }

    /**
     * @class InOrderIterator
     * @brief An iterator for traversing the tree in in-order.
     */
    class InOrderIterator {
    public:
        /**
         * @brief Construct a new InOrderIterator object.
         * 
         * @param root The root node of the tree.
         */
        InOrderIterator(Node<T>* root) {
            push_left(root);
        }

        /**
         * @brief Inequality operator to compare two iterators.
         * 
         * @param other The other iterator to compare to.
         * @return true If the iterators are not equal.
         * @return false If the iterators are equal.
         */
        bool operator!=(const InOrderIterator& other) const {
            return !stack.empty();
        }

        /**
         * @brief Increment the iterator.
         * 
         * @return InOrderIterator& Reference to the incremented iterator.
         */
        InOrderIterator& operator++() {
            Node<T>* node = stack.top();
            stack.pop();
            if (node->children.size() > 1) {
                push_left(node->children[1]);
            }
            return *this;
        }

        /**
         * @brief Dereference operator to access the current node.
         * 
         * @return Node<T>& Reference to the current node.
         */
        Node<T>& operator*() const {
            return *stack.top();
        }

        /**
         * @brief Arrow operator to access the current node.
         * 
         * @return Node<T>* Pointer to the current node.
         */
        Node<T>* operator->() const {
            return stack.top();
        }

    private:
        std::stack<Node<T>*> stack; ///< Stack for in-order traversal.

        /**
         * @brief Push all left children of the node onto the stack.
         * 
         * @param node The starting node.
         */
        void push_left(Node<T>* node) {
            while (node) {
                stack.push(node);
                if (!node->children.empty()) {
                    node = node->children[0];
                } else {
                    node = nullptr;
                }
            }
        }
    };

    /**
     * @brief Get an iterator to the beginning of the in-order traversal.
     * 
     * @return InOrderIterator An iterator to the beginning of the in-order traversal.
     */
    InOrderIterator begin_in_order() const {
        return InOrderIterator(root);
    }

    /**
     * @brief Get an iterator to the end of the in-order traversal.
     * 
     * @return InOrderIterator An iterator to the end of the in-order traversal.
     */
    InOrderIterator end_in_order() const {
        return InOrderIterator(nullptr);
    }

    /**
     * @class PostOrderIterator
     * @brief An iterator for traversing the tree in post-order.
     */
    class PostOrderIterator {
    public:
        /**
         * @brief Construct a new PostOrderIterator object.
         * 
         * @param root The root node of the tree.
         */
        PostOrderIterator(Node<T>* root) {
            if (root) {
                stack.push(root);
                while (!stack.empty()) {
                    Node<T>* node = stack.top();
                    stack.pop();
                    output.push(node);
                    for (auto& child : node->children) {
                        stack.push(child);
                    }
                }
            }
        }

        /**
         * @brief Inequality operator to compare two iterators.
         * 
         * @param other The other iterator to compare to.
         * @return true If the iterators are not equal.
         * @return false If the iterators are equal.
         */
        bool operator!=(const PostOrderIterator& other) const {
            return !output.empty();
        }

        /**
         * @brief Increment the iterator.
         * 
         * @return PostOrderIterator& Reference to the incremented iterator.
         */
        PostOrderIterator& operator++() {
            output.pop();
            return *this;
        }

        /**
         * @brief Dereference operator to access the current node.
         * 
         * @return Node<T>& Reference to the current node.
         */
        Node<T>& operator*() const {
            return *output.top();
        }

        /**
         * @brief Arrow operator to access the current node.
         * 
         * @return Node<T>* Pointer to the current node.
         */
        Node<T>* operator->() const {
            return output.top();
        }

    private:
        std::stack<Node<T>*> stack; ///< Stack for post-order traversal.
        std::stack<Node<T>*> output; ///< Stack for storing the post-order output.
    };

    /**
     * @brief Get an iterator to the beginning of the post-order traversal.
     * 
     * @return PostOrderIterator An iterator to the beginning of the post-order traversal.
     */
    PostOrderIterator begin_post_order() const {
        return PostOrderIterator(root);
    }

    /**
     * @brief Get an iterator to the end of the post-order traversal.
     * 
     * @return PostOrderIterator An iterator to the end of the post-order traversal.
     */
    PostOrderIterator end_post_order() const {
        return PostOrderIterator(nullptr);
    }

    /**
     * @class PreOrderIterator
     * @brief An iterator for traversing the tree in pre-order.
     */
    class PreOrderIterator {
    public:
        /**
         * @brief Construct a new PreOrderIterator object.
         * 
         * @param root The root node of the tree.
         */
        PreOrderIterator(Node<T>* root) {
            if (root) stack.push(root);
        }

        /**
         * @brief Inequality operator to compare two iterators.
         * 
         * @param other The other iterator to compare to.
         * @return true If the iterators are not equal.
         * @return false If the iterators are equal.
         */
        bool operator!=(const PreOrderIterator& other) const {
            return !stack.empty();
        }

        /**
         * @brief Increment the iterator.
         * 
         * @return PreOrderIterator& Reference to the incremented iterator.
         */
        PreOrderIterator& operator++() {
            auto node = stack.top();
            stack.pop();
            for (auto it = node->children.rbegin(); it != node->children.rend(); ++it) {
                stack.push(*it);
            }
            return *this;
        }

        /**
         * @brief Dereference operator to access the current node.
         * 
         * @return Node<T>& Reference to the current node.
         */
        Node<T>& operator*() const {
            return *stack.top();
        }

        /**
         * @brief Arrow operator to access the current node.
         * 
         * @return Node<T>* Pointer to the current node.
         */
        Node<T>* operator->() const {
            return stack.top();
        }

    private:
        std::stack<Node<T>*> stack; ///< Stack for pre-order traversal.
    };

    /**
     * @brief Get an iterator to the beginning of the pre-order traversal.
     * 
     * @return PreOrderIterator An iterator to the beginning of the pre-order traversal.
     */
    PreOrderIterator begin_pre_order() const {
        return PreOrderIterator(root);
    }

    /**
     * @brief Get an iterator to the end of the pre-order traversal.
     * 
     * @return PreOrderIterator An iterator to the end of the pre-order traversal.
     */
    PreOrderIterator end_pre_order() const {
        return PreOrderIterator(nullptr);
    }

    /**
     * @class MinHeapIterator
     * @brief An iterator for traversing the tree in min-heap order.
     */
    class MinHeapIterator {
    public:
        /**
         * @brief Construct a new MinHeapIterator object.
         * 
         * @param root The root node of the tree.
         */
        MinHeapIterator(Node<T>* root) {
            if (root) {
                populate_heap(root);
                std::make_heap(heap.begin(), heap.end(), compare_nodes);
            }
        }

        /**
         * @brief Inequality operator to compare two iterators.
         * 
         * @param other The other iterator to compare to.
         * @return true If the iterators are not equal.
         * @return false If the iterators are equal.
         */
        bool operator!=(const MinHeapIterator& other) const {
            return !heap.empty();
        }

        /**
         * @brief Increment the iterator.
         * 
         * @return MinHeapIterator& Reference to the incremented iterator.
         */
        MinHeapIterator& operator++() {
            std::pop_heap(heap.begin(), heap.end(), compare_nodes);
            heap.pop_back();
            return *this;
        }

        /**
         * @brief Dereference operator to access the current node.
         * 
         * @return Node<T>& Reference to the current node.
         */
        Node<T>& operator*() const {
            return *heap.front();
        }

        /**
         * @brief Arrow operator to access the current node.
         * 
         * @return Node<T>* Pointer to the current node.
         */
        Node<T>* operator->() const {
            return heap.front();
        }

    private:
        std::vector<Node<T>*> heap; ///< Vector to store the heap nodes.

        /**
         * @brief Populate the heap with nodes starting from the given node.
         * 
         * @param node The starting node.
         */
        void populate_heap(Node<T>* node) {
            if (!node) return;
            heap.push_back(node);
            for (auto& child : node->children) {
                populate_heap(child);
            }
        }

        /**
         * @brief Compare two nodes for the min-heap property.
         * 
         * @param a Pointer to the first node.
         * @param b Pointer to the second node.
         * @return true If the first node is greater than the second node.
         * @return false If the first node is not greater than the second node.
         */
        static bool compare_nodes(Node<T>* a, Node<T>* b) {
            return a->get_key() > b->get_key();
        }
    };

    /**
     * @brief Get an iterator to the beginning of the min-heap traversal.
     * 
     * @return MinHeapIterator An iterator to the beginning of the min-heap traversal.
     */
    MinHeapIterator begin_min_heap() const {
        return MinHeapIterator(root);
    }

    /**
     * @brief Get an iterator to the end of the min-heap traversal.
     * 
     * @return MinHeapIterator An iterator to the end of the min-heap traversal.
     */
    MinHeapIterator end_min_heap() const {
        return MinHeapIterator(nullptr);
    }

    /**
     * @brief Get an iterator to the beginning of the BFS traversal.
     * 
     * This is the default traversal method.
     * 
     * @return BFSIterator An iterator to the beginning of the BFS traversal.
     */
    BFSIterator begin() const {
        return begin_bfs();
    }

    /**
     * @brief Get an iterator to the end of the BFS traversal.
     * 
     * This is the default traversal method.
     * 
     * @return BFSIterator An iterator to the end of the BFS traversal.
     */
    BFSIterator end() const {
        return end_bfs();
    }

    /**
     * @brief Overload the stream insertion operator to print the tree.
     * 
     * @param os The output stream.
     * @param tree The tree to print.
     * @return std::ostream& The output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Tree<T, k>& tree) {
        if (tree.root) {
            tree.print_node(os, tree.root, 0);
        }
        return os;
    }

private:
    /**
     * @brief Print the node and its children recursively.
     * 
     * @param os The output stream.
     * @param node The current node.
     * @param depth The current depth for indentation.
     */
    void print_node(std::ostream& os, Node<T>* node, int depth) const {
        for (int i = 0; i < depth; ++i) {
            os << "  ";
        }
        os << node->get_key() << "\n";
        for (auto& child : node->children) {
            print_node(os, child, depth + 1);
        }
    }
};

#endif // TREE_HPP
