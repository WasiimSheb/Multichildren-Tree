#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "node.hpp"
#include "tree.hpp"

using namespace std;
using namespace sf;

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
int calculateSubtreeWidth(Node<double>* node) {
    if (!node) return 0;
    int width = 0;
    for (auto child : node->children) {
        width += calculateSubtreeWidth(child);
    }
    return max(width, 1); // Ensure each node has at least width 1
}

void drawTree(sf::RenderWindow &window, Node<double>* node, float x, float y) {
    if (!node) return;

    // Draw the node as a circle
    sf::CircleShape circle(NODE_RADIUS);
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(x - NODE_RADIUS, y - NODE_RADIUS);
    window.draw(circle);

    // Draw the node's value as text
    sf::Text text;
    text.setFont(getFont());
    text.setString(to_string(node->get_value()));
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
    Node<double> root_node(1.1);
    Tree<double, 2> tree; // Binary tree that contains doubles.
    tree.add_root(root_node);

    Node<double> n1(1.2);
    Node<double> n2(1.3);
    Node<double> n3(1.4);
    Node<double> n4(1.5);
    Node<double> n5(1.6);

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);

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
