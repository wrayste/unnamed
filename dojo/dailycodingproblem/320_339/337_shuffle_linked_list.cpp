#include "catch2/catch.hpp" // for AssertionHandler, Sou...

#include <random>
#include <vector>

namespace {
struct Node {
    int value_;
    Node* next_;

    Node(int value)
        : value_(value)
        , next_(nullptr) {
    }

    ~Node() {
        delete next_;
    }
};

template <typename F>
Node* shuffle(Node* n, F flip) {
    if (!n || !n->next_) {
        return n;
    } else {
        Node* n1 = nullptr;
        Node* n2 = nullptr;

        while (n) {
            Node* t = std::exchange(n->next_, n1);
            n1 = std::exchange(n, t);
            std::swap(n1, n2);
        }

        n1 = shuffle(n1, flip);
        n2 = shuffle(n2, flip);

        Node* result = nullptr;

        while (n1 && n2) {
            if (flip()) {
                Node* t = std::exchange(n1->next_, result);
                result = std::exchange(n1, t);
            } else {
                Node* t = std::exchange(n2->next_, result);
                result = std::exchange(n2, t);
            }
        }

        while (n1) {
            Node* t = std::exchange(n1->next_, result);
            result = std::exchange(n1, t);
        }

        while (n2) {
            Node* t = std::exchange(n2->next_, result);
            result = std::exchange(n2, t);
        }

        return result;
    }
}
} // namespace

TEST_CASE(__FILE__, "[dailycodingproblem]") {
    Node* root = new Node(1);

    {
        Node* n = root;
        for (size_t i = 2; i <= 20; ++i) {
            n->next_ = new Node(i);
            n = n->next_;
        }
    }

    std::mt19937 gen;
    std::uniform_int_distribution<> distrib(0, 1);
    const auto flip = [&]() { return distrib(gen); };

    Node* shuffled = shuffle(root, flip);

    std::vector<int> expected{9,  1, 3,  17, 11, 10, 2,  16, 12, 20,
                              13, 4, 14, 7,  6,  5,  18, 15, 8,  19};

    {
        Node* n = shuffled;
        for (size_t i = 0; i < expected.size(); ++i) {
            REQUIRE(n);
            REQUIRE(expected[i] == n->value_);
            n = n->next_;
        }
    }

    delete shuffled;
}