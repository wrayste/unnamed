#include "catch2/catch.hpp" // for AssertionHandler, Sou...

#include <cmath>
#include <vector>

namespace {
struct Node {
    int value;
    std::vector<Node*> children;

    Node(int _value)
        : value(_value) {
    }

    ~Node() {
        for (const Node* child : children) {
            delete child;
        }
    }

    void addChild(int value) {
        children.push_back(new Node(value));
    }

    Node& getChild(size_t child) {
        return *children[child];
    }

    const Node& getChild(size_t child) const {
        return *children[child];
    }
};

size_t maxEvenSubTrees(const Node& n, size_t& result) {
    size_t sum = 1;
    for (const Node* child : n.children) {
        size_t childSum = maxEvenSubTrees(*child, result);
        if (childSum & 1) {
            sum += childSum;
        } else {
            ++result;
        }
    }
    return sum;
}

size_t maxEvenSubTrees(const Node& n) {
    size_t result = 0;
    maxEvenSubTrees(n, result);
    return result;
}
} // namespace

TEST_CASE(__FILE__, "[dailycodingproblem]") {
    Node root(1);
    root.addChild(2);
    root.addChild(3);
    root.getChild(1).addChild(4);
    root.getChild(1).addChild(5);
    root.getChild(1).getChild(0).addChild(6);
    root.getChild(1).getChild(0).addChild(7);
    root.getChild(1).getChild(0).addChild(8);

    REQUIRE(2 == maxEvenSubTrees(root));
}