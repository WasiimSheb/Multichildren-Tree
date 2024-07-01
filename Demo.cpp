/**
 * @file main.cpp
 * @brief Main file for demonstrating tree operations and visualizing trees using SFML.
 * @date 2024-06-30
 * @version 1.0
 * @details
 * This file contains the main function to demonstrate various tree operations, including 
 * adding nodes, and traversing the tree using different iterators. It also includes 
 * visualization of the tree structure using the SFML library.
 * 
 * Contact: wasimshebalny@gmail.com
 */

#include <iostream>
#include <SFML/Graphics.hpp>
#include "node.hpp"
#include "tree.hpp"
#include "complex.hpp"

using namespace std;

// Constants for node and tree layout
const float NODE_RADIUS = 40.0f;
const float HORIZONTAL_SPACING = 100.0f;
const float VERTICAL_SPACING = 100.0f;

/**
 * @brief Load and return the font for drawing text.
 * 
 * @return sf::Font& Reference to the loaded font.
 */
sf::Font& getFont() {
    static sf::Font font;
    static bool isLoaded = false;
    if (!isLoaded) {
        if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
            cerr << "Could not load font DejaVuSans.ttf!" << endl;
            exit(EXIT_FAILURE);
        }
        isLoaded = true;
    }
    return font;
}

/**
 * @brief Calculate the width of the subtree rooted at the given node.
 * 
 * @tparam T The type of data stored in the nodes.
 * @param node Pointer to the root node of the subtree.
 * @return int The width of the subtree.
 */
template <typename T>
int calculateSubtreeWidth(Node<T>* node) {
    if (!node) return 0;
    int width = 0;
    for (auto child : node->children) {
        width += calculateSubtreeWidth(child);
    }
    return max(width, 1); // Ensure each node has at least width 1
}

/**
 * @brief Draw the tree recursively starting from the given node.
 * 
 * @tparam T The type of data stored in the nodes.
 * @param window The SFML render window.
 * @param node Pointer to the current node.
 * @param x The x-coordinate of the node.
 * @param y The y-coordinate of the node.
 */
template <typename T>
void drawTree(sf::RenderWindow &window, Node<T>* node, float x, float y) {
    if (!node) return;

    // Draw the node as a circle
    sf::CircleShape circle(NODE_RADIUS);
    circle.setFillColor(sf::Color::Black);
    circle.setPosition(x - NODE_RADIUS, y - NODE_RADIUS);
    window.draw(circle);

    // Draw the node's value as text
    sf::Text text;
    text.setFont(getFont());
    text.setString(node->toString());
    text.setCharacterSize(14);
    text.setFillColor(sf::Color::White);
    text.setPosition(x - NODE_RADIUS / 2, y - NODE_RADIUS / 2);
    window.draw(text);

    // Calculate total width of all children
    int totalWidth = calculateSubtreeWidth(node) * HORIZONTAL_SPACING;
    float child_x = x - totalWidth / 2 + HORIZONTAL_SPACING / 2;
    for (auto child : node->children) {
        if (child) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(x, y), sf::Color::White),
                sf::Vertex(sf::Vector2f(child_x, y + VERTICAL_SPACING), sf::Color::White)
            };
            window.draw(line, 2, sf::Lines);
            drawTree(window, child, child_x, y + VERTICAL_SPACING);
            child_x += calculateSubtreeWidth(child) * HORIZONTAL_SPACING;
        }
    }
}

/**
 * @brief Main function to demonstrate tree operations and visualizations.
 * 
 * @return int Exit status of the program.
 */
int main() {
    // Test the == operator for Complex numbers
    Complex c1(1.1, 2.2);
    Complex c2(1.1, 2.2);
    Complex c3(1.2, 2.3);

    cout << "c1 == c2: " << (c1 == c2) << endl; // Should print 1 (true)
    cout << "c1 == c3: " << (c1 == c3) << endl; // Should print 0 (false)

    // Existing tree visualization code with strings
    Node<string> root_node("c");
    Tree<string> tree;
    tree.add_root(root_node);

    Node<string> n1("a");
    Node<string> n2("b");
    Node<string> n3("d");
    Node<string> n4("e");
    Node<string> n5("f");

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);

    // Test the BFS iterator
    cout << "BFS traversal: ";
    for (auto it = tree.begin_bfs(); it != tree.end_bfs(); ++it) {
        cout << it->toString() << " ";
    }
    cout << endl;

    // Test the DFS iterator
    cout << "DFS traversal: ";
    for (auto it = tree.begin_dfs(); it != tree.end_dfs(); ++it) {
        cout << it->toString() << " ";
    }
    cout << endl;

    // Test the In-Order iterator
    cout << "In-Order traversal: ";
    for (auto it = tree.begin_in_order(); it != tree.end_in_order(); ++it) {
        cout << it->toString() << " ";
    }
    cout << endl;

    // Test the Post-Order iterator
    cout << "Post-Order traversal: ";
    for (auto it = tree.begin_post_order(); it != tree.end_post_order(); ++it) {
        cout << it->toString() << " ";
    }
    cout << endl;

    // Test the Pre-Order iterator
    cout << "Pre-Order traversal: ";
    for (auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it) {
        cout << it->toString() << " ";
    }
    cout << endl;

    // Test the Min-Heap iterator
    cout << "Min-Heap traversal: ";
    for (auto it = tree.begin_min_heap(); it != tree.end_min_heap(); ++it) {
        cout << it->toString() << " ";
    }
    cout << endl;

    // Set up SFML window for tree visualization
    sf::RenderWindow window(sf::VideoMode(1000, 600), "Tree Visualization");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Blue);
        drawTree(window, &root_node, window.getSize().x / 2, 50);
        window.display();
    }

    return 0;
}
