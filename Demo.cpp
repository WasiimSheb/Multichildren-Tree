#include <iostream>
#include <SFML/Graphics.hpp>
#include "node.hpp"
#include "tree.hpp"
#include "complex.hpp"

const float NODE_RADIUS = 20.0f;
const float HORIZONTAL_SPACING = 100.0f;
const float VERTICAL_SPACING = 100.0f;

sf::Font& getFont() {
    static sf::Font font;
    static bool isLoaded = false;
    if (!isLoaded) {
        if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
            std::cerr << "Could not load font DejaVuSans.ttf!" << std::endl;
            exit(EXIT_FAILURE);
        }
        isLoaded = true;
    }
    return font;
}

template <typename T>
int calculateSubtreeWidth(std::shared_ptr<Node<T>> node) {
    if (!node) return 0;
    int width = 0;
    for (auto child : node->children) {
        width += calculateSubtreeWidth(child);
    }
    return std::max(width, 1); // Ensure each node has at least width 1
}

template <typename T>
void drawTree(sf::RenderWindow &window, std::shared_ptr<Node<T>> node, float x, float y) {
    if (!node) return;

    sf::CircleShape circle(NODE_RADIUS);
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(x - NODE_RADIUS, y - NODE_RADIUS);
    window.draw(circle);

    sf::Text text;
    text.setFont(getFont());
    text.setString(node->toString());
    text.setCharacterSize(14);
    text.setFillColor(sf::Color::Black);
    text.setPosition(x - NODE_RADIUS / 2, y - NODE_RADIUS / 2);
    window.draw(text);

    int totalWidth = calculateSubtreeWidth(node) * HORIZONTAL_SPACING;
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
    // Integer Tree Example
    auto root_node = std::make_shared<Node<int>>(10);
    auto child1 = std::make_shared<Node<int>>(20);
    auto child2 = std::make_shared<Node<int>>(15);
    auto child3 = std::make_shared<Node<int>>(30);

    Tree<int> binaryTree;
    binaryTree.add_root(*root_node);
    binaryTree.add_sub_node(*root_node, *child1);
    binaryTree.add_sub_node(*root_node, *child2);
    binaryTree.add_sub_node(*child1, *child3);

    auto heap_iterator = binaryTree.begin_heap();

    while (heap_iterator != binaryTree.end_heap()) {
        std::cout << heap_iterator->toString() << " ";
        ++heap_iterator;
    }
    cout << endl;

    // Complex Tree Example
    auto c_root = make_shared<Node<Complex>>(Complex(3, 4));
    auto c_child1 = make_shared<Node<Complex>>(Complex(1, 2));
    auto c_child2 = make_shared<Node<Complex>>(Complex(5, 6));
    auto c_child3 = make_shared<Node<Complex>>(Complex(2, 3));

    Tree<Complex> complexTree;
    complexTree.add_root(*c_root);
    complexTree.add_sub_node(*c_root, *c_child1);
    complexTree.add_sub_node(*c_root, *c_child2);
    // complexTree.add_sub_node(*c_child1, *c_child3);

    auto c_heap_iterator = complexTree.begin_heap();

    while (c_heap_iterator != complexTree.end_heap()) {
        std::cout << c_heap_iterator->toString() << " ";
        ++c_heap_iterator;
    }
    std::cout << std::endl;

    // SFML Window for Visualization
    sf::RenderWindow window(sf::VideoMode(1000, 600), "Tree Visualization");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
       // drawTree(window, binaryTree.get_root(), window.getSize().x / 2, 50);
        drawTree(window, complexTree.get_root(), window.getSize().x / 2, 300);
        window.display();
    }

    return 0;
}
