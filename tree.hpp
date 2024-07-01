#ifndef TREE_HPP
#define TREE_HPP

#include "node.hpp"
#include <queue>
#include <stack>
#include <iostream>

template <typename T, int k = 2>
class Tree {
private:
    Node<T>* root;

public:
    Tree() : root(nullptr) {}

    void add_root(Node<T>& root_node) {
        root = &root_node;
    }

    void add_sub_node(Node<T>& parent_node, Node<T>& sub_node) {
        Node<T>* parent = find_node(root, parent_node);
        if (parent && parent->children.size() < k) {
            parent->add_child(&sub_node);
        }
    }

    Node<T>* find_node(Node<T>* current, Node<T>& target) {
        if (!current) return nullptr;
        if (current->get_key() == target.get_key()) return current;

        for (auto& child : current->children) {
            auto found = find_node(child, target);
            if (found) return found;
        }

        return nullptr;
    }

    class PreOrderIterator {
    public:
        PreOrderIterator(Node<T>* root) {
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

        Node<T>& operator*() const {
            return *stack.top();
        }

        Node<T>* operator->() const {
            return stack.top();
        }

    private:
        std::stack<Node<T>*> stack;
    };

    PreOrderIterator begin_pre_order() const {
        return PreOrderIterator(root);
    }

    PreOrderIterator end_pre_order() const {
        return PreOrderIterator(nullptr);
    }

    class PostOrderIterator {
    public:
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

        bool operator!=(const PostOrderIterator& other) const {
            return !output.empty();
        }

        PostOrderIterator& operator++() {
            output.pop();
            return *this;
        }

        Node<T>& operator*() const {
            return *output.top();
        }

        Node<T>* operator->() const {
            return output.top();
        }

    private:
        std::stack<Node<T>*> stack;
        std::stack<Node<T>*> output;
    };

    PostOrderIterator begin_post_order() const {
        return PostOrderIterator(root);
    }

    PostOrderIterator end_post_order() const {
        return PostOrderIterator(nullptr);
    }

    class InOrderIterator {
    public:
        InOrderIterator(Node<T>* root) {
            push_left(root);
        }

        bool operator!=(const InOrderIterator& other) const {
            return !stack.empty();
        }

        InOrderIterator& operator++() {
            Node<T>* node = stack.top();
            stack.pop();
            if (!node->children.empty()) {
                for (size_t i = 1; i < node->children.size(); ++i) {
                    push_left(node->children[i]);
                }
            }
            return *this;
        }

        Node<T>& operator*() const {
            return *stack.top();
        }

        Node<T>* operator->() const {
            return stack.top();
        }

    private:
        std::stack<Node<T>*> stack;
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

    InOrderIterator begin_in_order() const {
        return InOrderIterator(root);
    }

    InOrderIterator end_in_order() const {
        return InOrderIterator(nullptr);
    }

    class BFSIterator {
    public:
        BFSIterator(Node<T>* root) {
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

        Node<T>& operator*() const {
            return *queue.front();
        }

        Node<T>* operator->() const {
            return queue.front();
        }

    private:
        std::queue<Node<T>*> queue;
    };

    BFSIterator begin_bfs_scan() const {
        return BFSIterator(root);
    }

    BFSIterator end_bfs_scan() const {
        return BFSIterator(nullptr);
    }

    BFSIterator begin() const {
        return begin_bfs_scan();
    }

    BFSIterator end() const {
        return end_bfs_scan();
    }

    friend std::ostream& operator<<(std::ostream& os, const Tree<T, k>& tree) {
        if (tree.root) {
            tree.print_node(os, tree.root, 0);
        }
        return os;
    }

private:
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
