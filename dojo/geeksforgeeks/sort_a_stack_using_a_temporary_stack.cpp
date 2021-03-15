#include <algorithm>  // for sort
#include <cstdlib>    // for size_t
#include <functional> // for greater
#include <iterator>   // for begin, end
#include <stack>      // for stack
#include <vector>     // for vector, operator==, allocator

#include "catch2/catch.hpp" // for AssertionHandler, SourceLineInfo, StringRef

template <typename T>
void sort(std::stack<T>& s) {
    std::stack<T> s_;

    while (!s.empty()) {
        T t = s.top();
        s.pop();

        int count = 0;
        for (; !s_.empty() && t < s_.top(); s_.pop()) {
            ++count;
            s.push(s_.top());
        }

        s_.push(t);

        for (; 0 < count; --count) {
            s_.push(s.top());
            s.pop();
        }
    }

    s.swap(s_);
}

TEST_CASE(__FILE__, "[geeksforgeeks]") {
    std::vector<size_t> d{4, 5, 6, 7, 0, 1, 2};
    std::stack<size_t> s;
    for (auto i : d) {
        s.push(i);
    }

    std::sort(std::begin(d), std::end(d), std::greater<int>());
    sort(s);

    std::vector<size_t> actual;
    for (; !s.empty(); s.pop()) {
        actual.push_back(s.top());
    }

    REQUIRE(d == actual);
}