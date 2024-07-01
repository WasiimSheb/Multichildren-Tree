#ifndef TREE_HPP
#define TREE_HPP

#include "node.hpp"
#include <vector>
#include <queue>
#include <stack>
#include <stdexcept>
#include <algorithm>
#include <memory>
#include <iostream>

template <typename T, int K = 2>
class Tree {
private:
    std::shared_ptr<Node<T>> root;
    int k;
    bool is_binary_tree;

    std::vector<std::shared_ptr<Node<T>>> pre_order_nodes;
    std::vector<std::shared_ptr<Node<T>>> post_order_nodes;
    std::vector<std::shared_ptr<Node<T>>> in_order_nodes;
    std::vector<std::shared_ptr<Node<T>>> bfs_nodes;
    std::vector<std::shared_ptr<Node<T>>> dfs_nodes;
    std::vector<std::shared_ptr<Node<T>>> heap_nodes;

    void pre_order_traversal(std::shared_ptr<Node<T>> node) {
        if (!node) return;
        pre_order_nodes.push_back(node);
        for (auto child : node->children) {
            pre_order_traversal(child);
        }
    }

    void post_order_traversal(std::shared_ptr<Node<T>> node) {
        if (!node) return;
        for (auto child : node->children) {
            post_order_traversal(child);
        }
        post_order_nodes.push_back(node);
    }

    void in_order_traversal(std::shared_ptr<Node<T>> node) {
        if (!node || K != 2) return;
        if (!node->children.empty()) {
            in_order_traversal(node->children[0]);
        }
        in_order_nodes.push_back(node);
        if (node->children.size() > 1) {
            in_order_traversal(node->children[1]);
        }
    }

    void bfs_traversal(std::shared_ptr<Node<T>> node) {
        if (!node) return;
        std::queue<std::shared_ptr<Node<T>>> q;
        q.push(node);
        while (!q.empty()) {
            std::shared_ptr<Node<T>> current = q.front();
            q.pop();
            bfs_nodes.push_back(current);
            for (auto child : current->children) {
                q.push(child);
            }
        }
    }

    void dfs_traversal(std::shared_ptr<Node<T>> node) {
        if (!node) return;
        std::stack<std::shared_ptr<Node<T>>> s;
        s.push(node);
        while (!s.empty()) {
            std::shared_ptr<Node<T>> current = s.top();
            s.pop();
            dfs_nodes.push_back(current);
            for (auto it = current->children.rbegin(); it != current->children.rend(); ++it) {
                s.push(*it);
            }
        }
    }

    void myHeap() {
        if (K != 2) {
            throw std::runtime_error("Heap transformation is only supported for binary trees.");
        }

        heap_nodes.clear();
        std::queue<std::shared_ptr<Node<T>>> q;
        if (root) q.push(root);

        while (!q.empty()) {
            std::shared_ptr<Node<T>> current = q.front();
            q.pop();
            heap_nodes.push_back(current);
            for (auto child : current->children) {
                q.push(child);
            }
        }

        auto compare = [](std::shared_ptr<Node<T>> a, std::shared_ptr<Node<T>> b) { return a->key > b->key; };
        std::make_heap(heap_nodes.begin(), heap_nodes.end(), compare);

        for (size_t i = 0; i < heap_nodes.size(); ++i) {
            heap_nodes[i]->children.clear();
            size_t left_index = 2 * i + 1;
            size_t right_index = 2 * i + 2;
            if (left_index < heap_nodes.size()) {
                heap_nodes[i]->children.push_back(heap_nodes[left_index]);
            }
            if (right_index < heap_nodes.size()) {
                heap_nodes[i]->children.push_back(heap_nodes[right_index]);
            }
        }
    }

public:
    Tree() : root(nullptr), k(K), is_binary_tree(K == 2) {}

    int get_k() const { return k; }
    void add_root(const Node<T>& node) {
        if (root == nullptr) {
            root = std::make_shared<Node<T>>(node.get_key());
            std::cout << "Added root node: " << node.get_key() << std::endl;
        } else {
            throw std::runtime_error("Root node already exists. Updating the root's key.");
        }
    }

    void add_sub_node(const Node<T>& parent, const Node<T>& child) {
        if (root == nullptr) {
            throw std::runtime_error("Root node not found. Please add a root node before adding sub-nodes.");
        }

        std::queue<std::shared_ptr<Node<T>>> q;
        q.push(root);
        std::shared_ptr<Node<T>> parent_ptr = nullptr;

        while (!q.empty()) {
            std::shared_ptr<Node<T>> node = q.front();
            q.pop();

            if (node->get_key() == parent.get_key()) {
                parent_ptr = node;
                break;
            }

            for (auto& child_node : node->children) {
                q.push(child_node);
            }
        }

        if (parent_ptr == nullptr) {
            throw std::runtime_error("Parent node not found. Cannot add the child node.");
        }

        if (parent_ptr->children.size() >= static_cast<size_t>(k)) {
            throw std::runtime_error("Parent node has reached the maximum number of children.");
        }

        parent_ptr->add_child(std::make_shared<Node<T>>(child));
        std::cout << "Added child node: " << child.get_key() << " to parent node: " << parent.get_key() << std::endl;
    }

    class iterator {
    private:
        typename std::vector<std::shared_ptr<Node<T>>>::iterator it;

    public:
        iterator(typename std::vector<std::shared_ptr<Node<T>>>::iterator iter) : it(iter) {}

        iterator& operator++() {
            ++it;
            return *this;
        }

        bool operator!=(const iterator& other) const {
            return it != other.it;
        }

        Node<T>& operator*() const {
            return **it;
        }

        Node<T>* operator->() const {
            return it->get();
        }
    };

    iterator begin_pre_order() {
        pre_order_nodes.clear();
        pre_order_traversal(root);
        return iterator(pre_order_nodes.begin());
    }

    iterator end_pre_order() {
        return iterator(pre_order_nodes.end());
    }

    iterator begin_post_order() {
        post_order_nodes.clear();
        post_order_traversal(root);
        return iterator(post_order_nodes.begin());
    }

    iterator end_post_order() {
        return iterator(post_order_nodes.end());
    }

    iterator begin_in_order() {
        in_order_nodes.clear();
        in_order_traversal(root);
        return iterator(in_order_nodes.begin());
    }

    iterator end_in_order() {
        return iterator(in_order_nodes.end());
    }

    iterator begin_bfs_scan() {
        bfs_nodes.clear();
        bfs_traversal(root);
        return iterator(bfs_nodes.begin());
    }

    iterator end_bfs_scan() {
        return iterator(bfs_nodes.end());
    }

    iterator begin_dfs_scan() {
        dfs_nodes.clear();
        dfs_traversal(root);
        return iterator(dfs_nodes.begin());
    }

    iterator end_dfs_scan() {
        return iterator(dfs_nodes.end());
    }

    iterator begin_heap() {
        myHeap();
        return iterator(heap_nodes.begin());
    }

    iterator end_heap() {
        return iterator(heap_nodes.end());
    }

    std::shared_ptr<Node<T>> get_root() const {
        return root;
    }
};

#endif // TREE_HPP
