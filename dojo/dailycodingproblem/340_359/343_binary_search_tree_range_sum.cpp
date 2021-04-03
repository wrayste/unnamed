#include "catch2/catch.hpp" // for AssertionHandler, Sou...

#include <memory>

namespace {
struct Node {
    int value_;
    std::unique_ptr<Node> left_;
    std::unique_ptr<Node> right_;

    Node(int value)
        : value_(value) {
    }

    void left(int value) {
        left_ = std::make_unique<Node>(value);
    }

    Node* left() {
        return left_.get();
    }

    const Node* left() const {
        return left_.get();
    }

    void right(int value) {
        right_ = std::make_unique<Node>(value);
    }

    Node* right() {
        return right_.get();
    }

    const Node* right() const {
        return right_.get();
    }
};

int bstRangeSum(const Node* root, int minRange, int maxRange, int minTree,
                int maxTree) {
    if (!root) {
        return 0;
    }

    int result = 0;

    if (minRange <= root->value_ && root->value_ <= maxRange) {
        result += root->value_;
    }

    if (minRange < root->value_ && minRange < maxTree) {
        result += bstRangeSum(root->left(), minRange, maxRange, minTree,
                              root->value_);
    }

    if (root->value_ < maxRange && minTree < maxRange) {
        result += bstRangeSum(root->right(), minRange, maxRange, root->value_,
                              maxTree);
    }

    return result;
}

int bstRangeSum(const Node* root, int minRange, int maxRange) {
    return bstRangeSum(root, minRange, maxRange,
                       std::numeric_limits<int>::min(),
                       std::numeric_limits<int>::max());
}
} // namespace

TEST_CASE(__FILE__, "[dailycodingproblem]") {
    auto root = std::make_unique<Node>(5);
    root->left(3);
    root->left()->left(2);
    root->left()->right(4);
    root->right(8);
    root->right()->left(6);
    root->right()->right(10);

    REQUIRE(23 == bstRangeSum(root.get(), 4, 9));
}