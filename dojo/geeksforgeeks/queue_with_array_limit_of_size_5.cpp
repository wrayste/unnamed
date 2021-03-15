#include <array>   // for array
#include <memory>  // for unique_ptr, make_unique
#include <utility> // for exchange

#include "catch2/catch.hpp" // for AssertionHandler, SourceLineInfo, StringRef

namespace {
class Queue {
    struct Node {
        std::array<int, 5> data;
        int pos = 0;
        int size = 0;
        std::unique_ptr<Node> next;

        void push(int i) {
            if (size < data.size()) {
                data[size++] = i;
            } else if (next) {
                next->push(i);
            } else {
                next = std::make_unique<Node>();
                next->push(i);
            }
        }

        void pop() {
        }

        int peek() {
            return data[pos];
        }
    };

    std::unique_ptr<Node> root;

  public:
    void push(int i) {
        if (!root) {
            root = std::make_unique<Node>();
        }

        root->push(i);
    }

    void pop() {
        if (++root->pos == root->size) {
            root = std::exchange(root->next, nullptr);
        }
    }

    int peek() {
        return root->peek();
    }
};
} // namespace

TEST_CASE(__FILE__, "[geeksforgeeks]") {
    Queue q;
    for (int i = 0; i < 57; ++i) {
        q.push(i);
    }

    for (int i = 0; i < 57; ++i) {
        REQUIRE(i == q.peek());
        q.pop();
    }
}