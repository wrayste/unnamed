#include <stack>

#include "catch2/catch.hpp" // for AssertionHandler, SourceLineInfo, StringRef

namespace {
class Queue {
    std::stack<int> s1;
    std::stack<int> s2;

  public:
    void push(int i) {
        for (; !s1.empty(); s1.pop()) {
            s2.push(s1.top());
        }

        s2.push(i);

        for (; !s2.empty(); s2.pop()) {
            s1.push(s2.top());
        }
    }

    void pop() {
        s1.pop();
    }

    int peek() {
        return s1.top();
    }
};
} // namespace

TEST_CASE(__FILE__, "[geeksforgeeks]") {
    Queue q;
    for (int i = 0; i < 5; ++i) {
        q.push(i);
    }

    for (int i = 0; i < 5; ++i) {
        REQUIRE(i == q.peek());
        q.pop();
    }
}