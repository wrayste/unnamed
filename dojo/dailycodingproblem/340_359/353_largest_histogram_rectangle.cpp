#include "catch2/catch.hpp" // for AssertionHandler, Sou...

#include <stack>
#include <vector>

namespace {
size_t solve(const std::vector<size_t>& hist) {
    std::stack<int> s;

    const auto& calculateArea = [&hist, &s](const auto i) {
        size_t peak = s.top();
        s.pop();

        return hist[peak] * (s.empty() ? i : i - s.top() - 1);
    };

    size_t max_area = 0;

    for (size_t i = 0; i < hist.size();) {
        if (s.empty() || hist[s.top()] <= hist[i]) {
            s.push(i++);
        } else {
            max_area = std::max(max_area, calculateArea(i));
        }
    }

    while (!s.empty()) {
        max_area = std::max(max_area, calculateArea(hist.size()));
    }

    return max_area;
}
} // namespace

TEST_CASE(__FILE__, "[dailycodingproblem]") {
    REQUIRE(6 == solve({1, 3, 2, 5}));
}