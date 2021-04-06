#include "catch2/catch.hpp" // for AssertionHandler, Sou...

#include <vector>

namespace {
struct Node {
    int value;
    Node* left;
    Node* right;

    Node(int _value)
        : value(_value)
        , left(nullptr)
        , right(nullptr) {
    }

    ~Node() {
        delete left;
        delete right;
    }
};

bool equal(const Node* lhs, const Node* rhs) {
    if (lhs == nullptr && rhs == nullptr) {
        return true;
    } else if (lhs != nullptr && rhs != nullptr) {
        return lhs->value == rhs->value &&    //
               equal(lhs->left, rhs->left) && //
               equal(lhs->right, rhs->right);
    } else {
        return false;
    }
}

Node* buildCartesianTreeUtil(const std::vector<int>& input, int root,
                             const std::vector<int>& parent,
                             const std::vector<int>& leftchild,
                             const std::vector<int>& rightchild) {
    Node* result = nullptr;

    if (0 <= root) {
        result = new Node(input[root]);

        result->left = buildCartesianTreeUtil(input, leftchild[root], parent,
                                              leftchild, rightchild);
        result->right = buildCartesianTreeUtil(input, rightchild[root], parent,
                                               leftchild, rightchild);
    }

    return result;
}

Node* buildCartesianTree(const std::vector<int>& input) {
    std::vector<int> parent(input.size(), -1);
    std::vector<int> leftchild(input.size(), -1);
    std::vector<int> rightchild(input.size(), -1);

    int root = 0;
    for (size_t i = 1; i < input.size(); ++i) {
        int last = i - 1;
        for (; input[i] < input[last] && last != root; last = parent[last])
            ;

        if (input[i] < input[last]) {
            parent[root] = i;
            leftchild[i] = root;
            root = i;
        } else if (rightchild[last] == -1) {
            rightchild[last] = i;
            parent[i] = last;
            leftchild[i] = -1;
        } else {
            parent[rightchild[last]] = i;
            leftchild[i] = rightchild[last];
            rightchild[last] = i;
            parent[i] = last;
        }
    }

    parent[root] = -1;
    return buildCartesianTreeUtil(input, root, parent, leftchild, rightchild);
}
} // namespace

TEST_CASE(__FILE__, "[dailycodingproblem]") {
    const std::vector<int> input{3, 2, 6, 1, 9};

    Node expected(1);
    expected.left = new Node(2);
    expected.right = new Node(9);
    expected.left->left = new Node(3);
    expected.left->right = new Node(6);

    Node* actual = buildCartesianTree({3, 2, 6, 1, 9});

    REQUIRE(equal(&expected, actual));
    delete actual;
}