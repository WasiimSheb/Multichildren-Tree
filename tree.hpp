//wasimshebalny@gmail.com
#ifndef TREE_HPP
#define TREE_HPP

#include "node.hpp"
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>
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

    BFSIterator begin_bfs() const {
        return BFSIterator(root);
    }

    BFSIterator end_bfs() const {
        return BFSIterator(nullptr);
    }

    class DFSIterator {
    public:
        DFSIterator(Node<T>* root) {
            if (root) stack.push(root);
        }

         bool operator!=(const DFSIterator& other) const {
             return !stack.empty();
         }

        DFSIterator& operator++() {
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

    DFSIterator begin_dfs() const {
        return DFSIterator(root);
    }

    DFSIterator end_dfs() const {
        return DFSIterator(nullptr);
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
            if (node->children.size() > 1) {
                push_left(node->children[1]);
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

    class MinHeapIterator {
    public:
        MinHeapIterator(Node<T>* root) {
            if (root) {
                populate_heap(root);
                std::make_heap(heap.begin(), heap.end(), compare_nodes);
            }
        }

        bool operator!=(const MinHeapIterator& other) const {
            return !heap.empty();
        }

        MinHeapIterator& operator++() {
            std::pop_heap(heap.begin(), heap.end(), compare_nodes);
            heap.pop_back();
            return *this;
        }

        Node<T>& operator*() const {
            return *heap.front();
        }

        Node<T>* operator->() const {
            return heap.front();
        }

    private:
        std::vector<Node<T>*> heap;

        void populate_heap(Node<T>* node) {
            if (!node) return;
            heap.push_back(node);
            for (auto& child : node->children) {
                populate_heap(child);
            }
        }

        static bool compare_nodes(Node<T>* a, Node<T>* b) {
            return a->get_key() > b->get_key();
        }
    };

    MinHeapIterator begin_min_heap() const {
        return MinHeapIterator(root);
    }

    MinHeapIterator end_min_heap() const {
        return MinHeapIterator(nullptr);
    }

    BFSIterator begin() const {
        return begin_bfs();
    }

    BFSIterator end() const {
        return end_bfs();
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
