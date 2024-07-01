//wasimshebalny@gmail.com
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "tree.hpp"
#include "node.hpp"
#include "complex.hpp"

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

        //CHECK_THROWS_MESSAGE(tree.add_sub_node(root, child3), "error adding a sub node");
        CHECK_NOTHROW(tree.add_sub_node(child1, child3));
        CHECK_NOTHROW(tree.add_sub_node(child1, child4));
    }
}

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
