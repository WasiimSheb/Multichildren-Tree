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
    Tree();

    void add_root(Node<T>& root_node);
    void add_sub_node(Node<T>& parent_node, Node<T>& sub_node);

    class PreOrderIterator {
    public:
        PreOrderIterator(Node<T>* root);

        bool operator!=(const PreOrderIterator& other) const;

        PreOrderIterator& operator++();
        Node<T>* operator*() const;
        Node<T>* operator->() const;

    private:
        std::stack<Node<T>*> stack;
    };

    PreOrderIterator begin_pre_order() const;
    PreOrderIterator end_pre_order() const;

    class PostOrderIterator {
    public:
        PostOrderIterator(Node<T>* root);

        bool operator!=(const PostOrderIterator& other) const;

        PostOrderIterator& operator++();
        Node<T>* operator*() const;
        Node<T>* operator->() const;

    private:
        std::stack<Node<T>*> stack;
        std::stack<Node<T>*> output;
    };

    PostOrderIterator begin_post_order() const;
    PostOrderIterator end_post_order() const;

    class InOrderIterator {
    public:
        InOrderIterator(Node<T>* root);

        bool operator!=(const InOrderIterator& other) const;

        InOrderIterator& operator++();
        Node<T>* operator*() const;
        Node<T>* operator->() const;

    private:
        std::stack<Node<T>*> stack;
        void push_left(Node<T>* node);
    };

    InOrderIterator begin_in_order() const;
    InOrderIterator end_in_order() const;

    class BFSIterator {
    public:
        BFSIterator(Node<T>* root);

        bool operator!=(const BFSIterator& other) const;

        BFSIterator& operator++();
        Node<T>* operator*() const;
        Node<T>* operator->() const;

    private:
        std::queue<Node<T>*> queue;
    };

    BFSIterator begin_bfs_scan() const;
    BFSIterator end_bfs_scan() const;

    BFSIterator begin() const {
        return begin_bfs_scan();
    }

    BFSIterator end() const {
        return end_bfs_scan();
    }

    template <typename U, int m>
    friend std::ostream& operator<<(std::ostream& os, const Tree<U, m>& tree);

private:
    void print_node(std::ostream& os, Node<T>* node, int depth) const;
    Node<T>* find_node(Node<T>* current, Node<T>& target);
};

#endif // TREE_HPP
