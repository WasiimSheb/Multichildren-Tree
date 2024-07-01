//wasimshebalny@gmail.com
#include <iostream>
#include <SFML/Graphics.hpp>
#include "node.hpp"
#include "tree.hpp"
#include "complex.hpp"

using namespace std;

const float NODE_RADIUS = 40.0f;
const float HORIZONTAL_SPACING = 100.0f;
const float VERTICAL_SPACING = 100.0f;

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

    sf::CircleShape circle(NODE_RADIUS);
    circle.setFillColor(sf::Color::Black);
    circle.setPosition(x - NODE_RADIUS, y - NODE_RADIUS);
    window.draw(circle);

    sf::Text text;
    text.setFont(getFont());
    text.setString(node->toString());
    text.setCharacterSize(14);
    text.setFillColor(sf::Color::White);
    text.setPosition(x - NODE_RADIUS / 2, y - NODE_RADIUS / 2);
    window.draw(text);

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


int main() {
    // Test the == operator
    Complex c1(1.1, 2.2);
    Complex c2(1.1, 2.2);
    Complex c3(1.2, 2.3);

    cout << "c1 == c2: " << (c1 == c2) << endl; // Should print 1 (true)
    cout << "c1 == c3: " << (c1 == c3) << endl; // Should print 0 (false)

    // // Existing tree visualization code
    // Node<Complex> root_node(Complex(1.1, 2.2));
    // Tree<Complex> tree;
    // tree.add_root(root_node);

    // Node<Complex> n1(Complex(1.2, 2.3));
    // Node<Complex> n2(Complex(1.3, 2.4));
    // Node<Complex> n3(Complex(1.4, 2.5));
    // Node<Complex> n4(Complex(1.5, 2.6));
    // Node<Complex> n5(Complex(1.6, 2.7));

    // tree.add_sub_node(root_node, n1);
    // tree.add_sub_node(root_node, n2);
    // tree.add_sub_node(n1, n3);
    // tree.add_sub_node(n1, n4);
    // tree.add_sub_node(n2, n5);

    // Existing tree visualization code
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
