#ifndef TREE_HPP
#define TREE_HPP

#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include "node.hpp"

template <typename T, int k = 2>
class Tree {
public:
    Tree() : root(nullptr) {}

    void add_root(Node<T>& root_node) {
        root = &root_node;
    }

    void add_sub_node(Node<T>& parent, Node<T>& child) {
        if (parent.children.size() < k) {
            parent.children.push_back(&child);
        } else {
            throw std::runtime_error("Exceeded maximum number of children");
        }
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
            Node<T>* node = stack.top();
            stack.pop();
            for (auto it = node->children.rbegin(); it != node->children.rend(); ++it) {
                stack.push(*it);
            }
            return *this;
        }

        Node<T>* operator*() const {
            return stack.top();
        }

        Node<T>* operator->() const {
            return stack.top();
        }

    private:
        std::stack<Node<T>*> stack;
    };

    class PostOrderIterator {
    public:
        PostOrderIterator(Node<T>* root) {
            if (root) {
                push_leftmost(root);
            }
        }

        bool operator!=(const PostOrderIterator& other) const {
            return !stack.empty();
        }

        PostOrderIterator& operator++() {
            Node<T>* node = stack.top();
            stack.pop();
            if (!stack.empty() && stack.top()->children.back() == node) {
                Node<T>* parent = stack.top();
                stack.pop();
                push_leftmost(parent);
            }
            return *this;
        }

        Node<T>* operator*() const {
            return stack.top();
        }

        Node<T>* operator->() const {
            return stack.top();
        }

    private:
        void push_leftmost(Node<T>* node) {
            while (node) {
                stack.push(node);
                if (!node->children.empty()) {
                    node = node->children.front();
                } else {
                    node = nullptr;
                }
            }
        }

        std::stack<Node<T>*> stack;
    };

    class InOrderIterator {
    public:
        InOrderIterator(Node<T>* root) {
            if (root) {
                push_leftmost(root);
            }
        }

        bool operator!=(const InOrderIterator& other) const {
            return !stack.empty();
        }

        InOrderIterator& operator++() {
            Node<T>* node = stack.top();
            stack.pop();
            if (!node->children.empty()) {
                node = node->children.back();
                push_leftmost(node);
            }
            return *this;
        }

        Node<T>* operator*() const {
            return stack.top();
        }

        Node<T>* operator->() const {
            return stack.top();
        }

    private:
        void push_leftmost(Node<T>* node) {
            while (node) {
                stack.push(node);
                if (!node->children.empty()) {
                    node = node->children.front();
                } else {
                    node = nullptr;
                }
            }
        }

        std::stack<Node<T>*> stack;
    };

    class BFSIterator {
    public:
        BFSIterator(Node<T>* root) {
            if (root) queue.push(root);
        }

        bool operator!=(const BFSIterator& other) const {
            return !queue.empty();
        }

        BFSIterator& operator++() {
            Node<T>* node = queue.front();
            queue.pop();
            for (auto child : node->children) {
                queue.push(child);
            }
            return *this;
        }

        Node<T>* operator*() const {
            return queue.front();
        }

        Node<T>* operator->() const {
            return queue.front();
        }

    private:
        std::queue<Node<T>*> queue;
    };

    class DFSIterator {
    public:
        DFSIterator(Node<T>* root) {
            if (root) stack.push(root);
        }

        bool operator!=(const DFSIterator& other) const {
            return !stack.empty();
        }

        DFSIterator& operator++() {
            Node<T>* node = stack.top();
            stack.pop();
            for (auto it = node->children.rbegin(); it != node->children.rend(); ++it) {
                stack.push(*it);
            }
            return *this;
        }

        Node<T>* operator*() const {
            return stack.top();
        }

        Node<T>* operator->() const {
            return stack.top();
        }

    private:
        std::stack<Node<T>*> stack;
    };

    class HeapIterator {
    public:
        HeapIterator(Node<T>* root) {
            if (root) {
                build_heap(root);
                std::make_heap(heap.begin(), heap.end(), [](Node<T>* a, Node<T>* b) { return a->get_value() > b->get_value(); });
            }
        }

        bool operator!=(const HeapIterator& other) const {
            return !heap.empty();
        }

        HeapIterator& operator++() {
            std::pop_heap(heap.begin(), heap.end(), [](Node<T>* a, Node<T>* b) { return a->get_value() > b->get_value(); });
            heap.pop_back();
            return *this;
        }

        Node<T>* operator*() const {
            return heap.front();
        }

        Node<T>* operator->() const {
            return heap.front();
        }

    private:
        void build_heap(Node<T>* node) {
            if (!node) return;
            heap.push_back(node);
            for (auto child : node->children) {
                build_heap(child);
            }
        }

        std::vector<Node<T>*> heap;
    };

    PreOrderIterator begin_pre_order() const { return PreOrderIterator(root); }
    PreOrderIterator end_pre_order() const { return PreOrderIterator(nullptr); }

    PostOrderIterator begin_post_order() const { return PostOrderIterator(root); }
    PostOrderIterator end_post_order() const { return PostOrderIterator(nullptr); }

    InOrderIterator begin_in_order() const { return InOrderIterator(root); }
    InOrderIterator end_in_order() const { return InOrderIterator(nullptr); }

    BFSIterator begin_bfs_scan() const { return BFSIterator(root); }
    BFSIterator end_bfs_scan() const { return BFSIterator(nullptr); }

    DFSIterator begin_dfs_scan() const { return DFSIterator(root); }
    DFSIterator end_dfs_scan() const { return DFSIterator(nullptr); }

    HeapIterator myHeap() const { return HeapIterator(root); }

private:
    Node<T>* root;
};

#endif
