/**
 * @file test_tree.cpp
 * @brief Test cases for the Tree and Node classes using the doctest framework.
 * @date 2024-06-30
 * @version 1.0
 * @details
 * This file contains test cases for various functionalities of the Tree and Node classes. 
 * It tests operations such as adding children, different traversal methods, and heap operations 
 * for different data types including int, Complex, string, and double.
 * 
 * Contact: wasimshebalny@gmail.com
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "tree.hpp"
#include "node.hpp"
#include "complex.hpp"

/**
 * @brief Test case for adding children to nodes.
 */
TEST_CASE("children check") {
    Node<int> root(10);
    Tree<int> tree;
    tree.add_root(root);

    Node<int> child1(20);
    Node<int> child2(15);

    SUBCASE("adding children") {
        tree.add_sub_node(root, child1);
        tree.add_sub_node(root, child2);

        CHECK(root.children.size() == 2);
        CHECK(root.children[0]->get_key() == 20);
        CHECK(root.children[1]->get_key() == 15);
    }

    SUBCASE("exceeding children") {
        Node<int> child3(30);
        Node<int> child4(40);

        tree.add_sub_node(root, child1);
        tree.add_sub_node(root, child2);

        CHECK_NOTHROW(tree.add_sub_node(child1, child3));
        CHECK_NOTHROW(tree.add_sub_node(child1, child4));
    }
}

/**
 * @brief Test case for different tree traversal methods.
 */
TEST_CASE("traversals") {
    Node<int> root(10);
    Tree<int> tree;
    tree.add_root(root);

    Node<int> child1(20);
    Node<int> child2(15);
    Node<int> child3(25);
    Node<int> child4(30);

    tree.add_sub_node(root, child1);
    tree.add_sub_node(root, child2);
    tree.add_sub_node(child1, child3);
    tree.add_sub_node(child1, child4);

    SUBCASE("BFS traversal") {
        std::vector<int> expected = {10, 20, 15, 25, 30};
        std::vector<int> result;

        for (auto it = tree.begin_bfs(); it != tree.end_bfs(); ++it) {
            result.push_back(it->get_key());
        }

        CHECK(result == expected);
    }

    SUBCASE("DFS traversal") {
        std::vector<int> expected = {10, 20, 25, 30, 15};
        std::vector<int> result;

        for (auto it = tree.begin_dfs(); it != tree.end_dfs(); ++it) {
            result.push_back(it->get_key());
        }

        CHECK(result == expected);
    }

    SUBCASE("In-Order traversal") {
        std::vector<int> expected = {25, 20, 30, 10, 15};
        std::vector<int> result;

        for (auto it = tree.begin_in_order(); it != tree.end_in_order(); ++it) {
            result.push_back(it->get_key());
        }

        CHECK(result == expected);
    }

    SUBCASE("Post-Order traversal") {
        std::vector<int> expected = {25, 30, 20, 15, 10};
        std::vector<int> result;

        for (auto it = tree.begin_post_order(); it != tree.end_post_order(); ++it) {
            result.push_back(it->get_key());
        }

        CHECK(result == expected);
    }

    SUBCASE("Pre-Order traversal") {
        std::vector<int> expected = {10, 20, 25, 30, 15};
        std::vector<int> result;

        for (auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it) {
            result.push_back(it->get_key());
        }

        CHECK(result == expected);
    }
}

/**
 * @brief Test case for heap operations.
 */
TEST_CASE("heap operations") {
    Node<int> root(10);
    Tree<int> tree;
    tree.add_root(root);

    Node<int> child1(20);
    Node<int> child2(15);
    Node<int> child3(25);
    Node<int> child4(30);

    tree.add_sub_node(root, child1);
    tree.add_sub_node(root, child2);
    tree.add_sub_node(child1, child3);
    tree.add_sub_node(child1, child4);

    SUBCASE("Min-Heap traversal") {
        std::vector<int> expected = {10, 15, 20, 25, 30};
        std::vector<int> result;

        for (auto it = tree.begin_min_heap(); it != tree.end_min_heap(); ++it) {
            result.push_back(it->get_key());
        }

        CHECK(result == expected);
    }
}

/**
 * @brief Test case for tree operations with Complex type.
 */
TEST_CASE("Complex type operations") {
    Node<Complex> root(Complex(1.1, 2.2));
    Tree<Complex> tree;
    tree.add_root(root);

    Node<Complex> child1(Complex(1.2, 2.3));
    Node<Complex> child2(Complex(1.3, 2.4));
    Node<Complex> child3(Complex(1.4, 2.5));
    Node<Complex> child4(Complex(1.5, 2.6));

    tree.add_sub_node(root, child1);
    tree.add_sub_node(root, child2);
    tree.add_sub_node(child1, child3);
    tree.add_sub_node(child1, child4);

    SUBCASE("BFS traversal with Complex") {
        std::vector<std::string> expected = {"1.1+2.2i", "1.2+2.3i", "1.3+2.4i", "1.4+2.5i", "1.5+2.6i"};
        std::vector<std::string> result;

        for (auto it = tree.begin_bfs(); it != tree.end_bfs(); ++it) {
            result.push_back(it->toString());
        }

        CHECK(result == expected);
    }

    SUBCASE("DFS traversal with Complex") {
        std::vector<std::string> expected = {"1.1+2.2i", "1.2+2.3i", "1.4+2.5i", "1.5+2.6i", "1.3+2.4i"};
        std::vector<std::string> result;

        for (auto it = tree.begin_dfs(); it != tree.end_dfs(); ++it) {
            result.push_back(it->toString());
        }

        CHECK(result == expected);
    }

    SUBCASE("Min-Heap traversal with Complex") {
        std::vector<std::string> expected = {"1.1+2.2i", "1.2+2.3i", "1.3+2.4i", "1.4+2.5i", "1.5+2.6i"};
        std::vector<std::string> result;

        for (auto it = tree.begin_min_heap(); it != tree.end_min_heap(); ++it) {
            result.push_back(it->toString());
        }

        CHECK(result == expected);
    }
}

/**
 * @brief Test case for tree operations with string type.
 */
TEST_CASE("String type operations") {
    Node<std::string> root("root");
    Tree<std::string> tree;
    tree.add_root(root);

    Node<std::string> child1("child1");
    Node<std::string> child2("child2");
    Node<std::string> child3("child3");
    Node<std::string> child4("child4");

    tree.add_sub_node(root, child1);
    tree.add_sub_node(root, child2);
    tree.add_sub_node(child1, child3);
    tree.add_sub_node(child1, child4);

    SUBCASE("BFS traversal with String") {
        std::vector<std::string> expected = {"root", "child1", "child2", "child3", "child4"};
        std::vector<std::string> result;

        for (auto it = tree.begin_bfs(); it != tree.end_bfs(); ++it) {
            result.push_back(it->get_key());
        }

        CHECK(result == expected);
    }

    SUBCASE("DFS traversal with String") {
        std::vector<std::string> expected = {"root", "child1", "child3", "child4", "child2"};
        std::vector<std::string> result;

        for (auto it = tree.begin_dfs(); it != tree.end_dfs(); ++it) {
            result.push_back(it->get_key());
        }

        CHECK(result == expected);
    }

    SUBCASE("Min-Heap traversal with String") {
        std::vector<std::string> expected = {"child1", "child2", "child3", "child4", "root"};
        std::vector<std::string> result;

        for (auto it = tree.begin_min_heap(); it != tree.end_min_heap(); ++it) {
            result.push_back(it->get_key());
        }

        CHECK(result == expected);
    }
}

/**
 * @brief Test case for tree operations with double type.
 */
TEST_CASE("Double type operations") {
    Node<double> root(10.5);
    Tree<double> tree;
    tree.add_root(root);

    Node<double> child1(20.2);
    Node<double> child2(15.3);
    Node<double> child3(25.7);
    Node<double> child4(30.8);

    tree.add_sub_node(root, child1);
    tree.add_sub_node(root, child2);
    tree.add_sub_node(child1, child3);
    tree.add_sub_node(child1, child4);

    SUBCASE("BFS traversal with Double") {
        std::vector<double> expected = {10.5, 20.2, 15.3, 25.7, 30.8};
        std::vector<double> result;

        for (auto it = tree.begin_bfs(); it != tree.end_bfs(); ++it) {
            result.push_back(it->get_key());
        }

        CHECK(result == expected);
    }

    SUBCASE("DFS traversal with Double") {
        std::vector<double> expected = {10.5, 20.2, 25.7, 30.8, 15.3};
        std::vector<double> result;

        for (auto it = tree.begin_dfs(); it != tree.end_dfs(); ++it) {
            result.push_back(it->get_key());
        }

        CHECK(result == expected);
    }

    SUBCASE("Min-Heap traversal with Double") {
        std::vector<double> expected = {10.5, 15.3, 20.2, 25.7, 30.8};
        std::vector<double> result;

        for (auto it = tree.begin_min_heap(); it != tree.end_min_heap(); ++it) {
            result.push_back(it->get_key());
        }

        CHECK(result == expected);
    }
}
