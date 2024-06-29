#include <iostream>
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "node.hpp"
#include "tree.hpp"
#include "complex.hpp"

using namespace std;

const float NODE_RADIUS = 20.0f;
const float HORIZONTAL_SPACING = 100.0f;
const float VERTICAL_SPACING = 100.0f;

// Function to load font
sf::Font& getFont() {
    static sf::Font font;
    static bool isLoaded = false;
    if (!isLoaded) {
        // Try to load a commonly available font
        if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
            cerr << "Could not load font DejaVuSans.ttf!" << endl;
            exit(EXIT_FAILURE);
        }
        isLoaded = true;
    }
    return font;
}

// Function to calculate the width of the subtree
template <typename T>
int calculateSubtreeWidth(Node<T>* node) {
    if (!node) return 0;
    int width = 0;
    for (auto child : node->children) {
        width += calculateSubtreeWidth(child);
    }
    return max(width, 1); // Ensure each node has at least width 1
}

template <typename T>
void drawTree(sf::RenderWindow &window, Node<T>* node, float x, float y) {
    if (!node) return;

    // Draw the node as a circle
    sf::CircleShape circle(NODE_RADIUS);
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(x - NODE_RADIUS, y - NODE_RADIUS);
    window.draw(circle);

    // Draw the node's value as text
    sf::Text text;
    text.setFont(getFont());
    stringstream ss;
    ss << node->get_value();
    text.setString(ss.str());
    text.setCharacterSize(14);
    text.setFillColor(sf::Color::Black);
    text.setPosition(x - NODE_RADIUS / 2, y - NODE_RADIUS / 2);
    window.draw(text);

    // Calculate total width of all children
    int totalWidth = calculateSubtreeWidth(node) * HORIZONTAL_SPACING;

    // Draw edges and recursively draw child nodes
    float child_x = x - totalWidth / 2 + HORIZONTAL_SPACING / 2;
    for (auto child : node->children) {
        if (child) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(x, y), sf::Color::Black),
                sf::Vertex(sf::Vector2f(child_x, y + VERTICAL_SPACING), sf::Color::Black)
            };
            window.draw(line, 2, sf::Lines);
            drawTree(window, child, child_x, y + VERTICAL_SPACING);
            child_x += calculateSubtreeWidth(child) * HORIZONTAL_SPACING;
        }
    }
}

template <>
void drawTree<Complex>(sf::RenderWindow &window, Node<Complex>* node, float x, float y) {
    if (!node) return;

    // Draw the node as a circle
    sf::CircleShape circle(NODE_RADIUS);
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(x - NODE_RADIUS, y - NODE_RADIUS);
    window.draw(circle);

    // Draw the node's value as text
    sf::Text text;
    text.setFont(getFont());
    stringstream ss;
    ss << node->get_value();
    text.setString(ss.str());
    text.setCharacterSize(14);
    text.setFillColor(sf::Color::Black);
    text.setPosition(x - NODE_RADIUS / 2, y - NODE_RADIUS / 2);
    window.draw(text);

    // Calculate total width of all children
    int totalWidth = calculateSubtreeWidth(node) * HORIZONTAL_SPACING;

    // Draw edges and recursively draw child nodes
    float child_x = x - totalWidth / 2 + HORIZONTAL_SPACING / 2;
    for (auto child : node->children) {
        if (child) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(x, y), sf::Color::Black),
                sf::Vertex(sf::Vector2f(child_x, y + VERTICAL_SPACING), sf::Color::Black)
            };
            window.draw(line, 2, sf::Lines);
            drawTree(window, child, child_x, y + VERTICAL_SPACING);
            child_x += calculateSubtreeWidth(child) * HORIZONTAL_SPACING;
        }
    }
}

int main() {
    Node<Complex> root_node(Complex(1.1, 1.1));
    Tree<Complex, 3> tree; // Ternary tree that contains Complex numbers.
    tree.add_root(root_node);

    Node<Complex> n1(Complex(1.2, 1.2));
    Node<Complex> n2(Complex(1.3, 1.3));
    Node<Complex> n3(Complex(1.4, 1.4));
    Node<Complex> n4(Complex(1.5, 1.5));
    Node<Complex> n5(Complex(1.6, 1.6));

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(root_node, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);

    // Demonstrating use of iterators
    cout << "Pre-order traversal:" << endl;
    for (auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it) {
        cout << it->get_value() << " ";
    }
    cout << endl;

    cout << "Post-order traversal:" << endl;
    for (auto it = tree.begin_post_order(); it != tree.end_post_order(); ++it) {
        cout << it->get_value() << " ";
    }
    cout << endl;

    cout << "In-order traversal:" << endl;
    for (auto it = tree.begin_in_order(); it != tree.end_in_order(); ++it) {
        cout << it->get_value() << " ";
    }
    cout << endl;

    cout << "BFS traversal:" << endl;
    for (auto it = tree.begin_bfs_scan(); it != tree.end_bfs_scan(); ++it) {
        cout << it->get_value() << " ";
    }
    cout << endl;

    cout << "DFS traversal:" << endl;
    for (auto it = tree.begin_dfs_scan(); it != tree.end_dfs_scan(); ++it) {
        cout << it->get_value() << " ";
    }
    cout << endl;

    cout << "Heap traversal:" << endl;
    auto heap_it = tree.myHeap();
    for (auto it = heap_it; it != Tree<Complex, 3>::HeapIterator(nullptr); ++it) {
        cout << it->get_value() << " ";
    }
    cout << endl;

    sf::RenderWindow window(sf::VideoMode(800, 600), "Tree Visualization");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        // Draw the tree starting from the root node
        drawTree(window, &root_node, window.getSize().x / 2, 50);

        window.display();
    }

    return 0;
}
