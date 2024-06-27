#ifndef TREE_HPP
#define TREE_HPP

#include "node.hpp"
#include <queue>
#include <stack>
#include <iostream>

template <typename T, int k = 2>
class Tree {
private:
    std::shared_ptr<Node<T>> root;

public:
    Tree() : root(nullptr) {}

    void add_root(Node<T>& root_node) {
        root = std::make_shared<Node<T>>(root_node);
    }

    void add_sub_node(Node<T>& parent_node, Node<T>& sub_node) {
        std::shared_ptr<Node<T>> parent = find_node(root, parent_node);
        if (parent && parent->children.size() < k) {
            parent->add_child(std::make_shared<Node<T>>(sub_node));
        }
    }

    // Find a node in the tree (recursive)
    std::shared_ptr<Node<T>> find_node(std::shared_ptr<Node<T>> current, Node<T>& target) {
        if (!current) return nullptr;
        if (current->value == target.value) return current;

        for (auto& child : current->children) {
            auto found = find_node(child, target);
            if (found) return found;
        }

        return nullptr;
    }

    // Pre-order traversal
    class PreOrderIterator {
    public:
        PreOrderIterator(std::shared_ptr<Node<T>> root) {
            if (root) stack.push(root);
        }

        bool operator!=(const PreOrderIterator& other) const {
            return !stack.empty();
        }

        PreOrderIterator& operator++() {
            auto node = stack.top();
            stack.pop();
            for (auto it = node->children.rbegin(); it != node->children.rend(); ++it) {
                stack.push(*it);
            }
            return *this;
        }

        std::shared_ptr<Node<T>> operator*() const {
            return stack.top();
        }

    private:
        std::stack<std::shared_ptr<Node<T>>> stack;
    };

    PreOrderIterator begin_pre_order() const {
        return PreOrderIterator(root);
    }

    PreOrderIterator end_pre_order() const {
        return PreOrderIterator(nullptr);
    }

    // Implement other iterators (PostOrder, InOrder, BFS) similarly...

    // BFS traversal
    class BFSIterator {
    public:
        BFSIterator(std::shared_ptr<Node<T>> root) {
            if (root) queue.push(root);
        }

        bool operator!=(const BFSIterator& other) const {
            return !queue.empty();
        }

        BFSIterator& operator++() {
            auto node = queue.front();
            queue.pop();
            for (auto& child : node->children) {
                queue.push(child);
            }
            return *this;
        }

        std::shared_ptr<Node<T>> operator*() const {
            return queue.front();
        }

    private:
        std::queue<std::shared_ptr<Node<T>>> queue;
    };

    BFSIterator begin_bfs_scan() const {
        return BFSIterator(root);
    }

    BFSIterator end_bfs_scan() const {
        return BFSIterator(nullptr);
    }

    // Overload the output stream operator
    friend std::ostream& operator<<(std::ostream& os, const Tree& tree) {
        if (tree.root) {
            tree.print_node(os, tree.root, 0);
        }
        return os;
    }

private:
    void print_node(std::ostream& os, std::shared_ptr<Node<T>> node, int depth) const {
        for (int i = 0; i < depth; ++i) {
            os << "  ";
        }
        os << node->value << "\n";
        for (auto& child : node->children) {
            print_node(os, child, depth + 1);
        }
    }
};

#endif // TREE_HPP
