#include "tree.hpp"

template <typename T, int k>
Tree<T, k>::Tree() : root(nullptr) {}

template <typename T, int k>
void Tree<T, k>::add_root(Node<T>& root_node) {
    root = &root_node;
}

template <typename T, int k>
void Tree<T, k>::add_sub_node(Node<T>& parent_node, Node<T>& sub_node) {
    Node<T>* parent = find_node(root, parent_node);
    if (parent && parent->children.size() < k) {
        parent->add_child(&sub_node);
    }
}

template <typename T, int k>
Node<T>* Tree<T, k>::find_node(Node<T>* current, Node<T>& target) {
    if (!current) return nullptr;
    if (current->value == target.value) return current;

    for (auto& child : current->children) {
        auto found = find_node(child, target);
        if (found) return found;
    }

    return nullptr;
}

template <typename T, int k>
Tree<T, k>::PreOrderIterator::PreOrderIterator(Node<T>* root) {
    if (root) stack.push(root);
}

template <typename T, int k>
bool Tree<T, k>::PreOrderIterator::operator!=(const PreOrderIterator& other) const {
    return !stack.empty();
}

template <typename T, int k>
typename Tree<T, k>::PreOrderIterator& Tree<T, k>::PreOrderIterator::operator++() {
    auto node = stack.top();
    stack.pop();
    for (auto it = node->children.rbegin(); it != node->children.rend(); ++it) {
        stack.push(*it);
    }
    return *this;
}

template <typename T, int k>
Node<T>* Tree<T, k>::PreOrderIterator::operator*() const {
    return stack.top();
}

template <typename T, int k>
Node<T>* Tree<T, k>::PreOrderIterator::operator->() const {
    return stack.top();
}

template <typename T, int k>
typename Tree<T, k>::PreOrderIterator Tree<T, k>::begin_pre_order() const {
    return PreOrderIterator(root);
}

template <typename T, int k>
typename Tree<T, k>::PreOrderIterator Tree<T, k>::end_pre_order() const {
    return PreOrderIterator(nullptr);
}

template <typename T, int k>
Tree<T, k>::PostOrderIterator::PostOrderIterator(Node<T>* root) {
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

template <typename T, int k>
bool Tree<T, k>::PostOrderIterator::operator!=(const PostOrderIterator& other) const {
    return !output.empty();
}

template <typename T, int k>
typename Tree<T, k>::PostOrderIterator& Tree<T, k>::PostOrderIterator::operator++() {
    output.pop();
    return *this;
}

template <typename T, int k>
Node<T>* Tree<T, k>::PostOrderIterator::operator*() const {
    return output.top();
}

template <typename T, int k>
Node<T>* Tree<T, k>::PostOrderIterator::operator->() const {
    return output.top();
}

template <typename T, int k>
typename Tree<T, k>::PostOrderIterator Tree<T, k>::begin_post_order() const {
    return PostOrderIterator(root);
}

template <typename T, int k>
typename Tree<T, k>::PostOrderIterator Tree<T, k>::end_post_order() const {
    return PostOrderIterator(nullptr);
}

template <typename T, int k>
Tree<T, k>::InOrderIterator::InOrderIterator(Node<T>* root) {
    push_left(root);
}

template <typename T, int k>
void Tree<T, k>::InOrderIterator::push_left(Node<T>* node) {
    while (node) {
        stack.push(node);
        if (!node->children.empty()) {
            node = node->children[0];
        } else {
            node = nullptr;
        }
    }
}

template <typename T, int k>
bool Tree<T, k>::InOrderIterator::operator!=(const InOrderIterator& other) const {
    return !stack.empty();
}

template <typename T, int k>
typename Tree<T, k>::InOrderIterator& Tree<T, k>::InOrderIterator::operator++() {
    Node<T>* node = stack.top();
    stack.pop();
    if (!node->children.empty()) {
        for (size_t i = 1; i < node->children.size(); ++i) {
            push_left(node->children[i]);
        }
    }
    return *this;
}

template <typename T, int k>
Node<T>* Tree<T, k>::InOrderIterator::operator*() const {
    return stack.top();
}

template <typename T, int k>
Node<T>* Tree<T, k>::InOrderIterator::operator->() const {
    return stack.top();
}

template <typename T, int k>
typename Tree<T, k>::InOrderIterator Tree<T, k>::begin_in_order() const {
    return InOrderIterator(root);
}

template <typename T, int k>
typename Tree<T, k>::InOrderIterator Tree<T, k>::end_in_order() const {
    return InOrderIterator(nullptr);
}

template <typename T, int k>
Tree<T, k>::BFSIterator::BFSIterator(Node<T>* root) {
    if (root) queue.push(root);
}

template <typename T, int k>
bool Tree<T, k>::BFSIterator::operator!=(const BFSIterator& other) const {
    return !queue.empty();
}

template <typename T, int k>
typename Tree<T, k>::BFSIterator& Tree<T, k>::BFSIterator::operator++() {
    auto node = queue.front();
    queue.pop();
    for (auto& child : node->children) {
        queue.push(child);
    }
    return *this;
}

template <typename T, int k>
Node<T>* Tree<T, k>::BFSIterator::operator*() const {
    return queue.front();
}

template <typename T, int k>
Node<T>* Tree<T, k>::BFSIterator::operator->() const {
    return queue.front();
}

template <typename T, int k>
typename Tree<T, k>::BFSIterator Tree<T, k>::begin_bfs_scan() const {
    return BFSIterator(root);
}

template <typename T, int k>
typename Tree<T, k>::BFSIterator Tree<T, k>::end_bfs_scan() const {
    return BFSIterator(nullptr);
}

template <typename T, int k>
void Tree<T, k>::print_node(std::ostream& os, Node<T>* node, int depth) const {
    for (int i = 0; i < depth; ++i) {
        os << "  ";
    }
    os << node->value << "\n";
    for (auto& child : node->children) {
        print_node(os, child, depth + 1);
    }
}

template <typename T, int k>
std::ostream& operator<<(std::ostream& os, const Tree<T, k>& tree) {
    if (tree.root) {
        tree.print_node(os, tree.root, 0);
    }
    return os;
}

// Explicit template instantiation
template class Tree<double, 3>;

template std::ostream& operator<< <double>(std::ostream& os, const Tree<double, 3>& tree);
