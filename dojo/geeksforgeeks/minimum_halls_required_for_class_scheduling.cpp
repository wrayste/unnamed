#include <algorithm>         // for sort
#include <iterator>          // for begin, end
#include <queue>             // for priority_queue
#include <vector>            // for vector, swap

#include "catch2/catch.hpp"  // for AssertionHandler, SourceLineInfo, StringRef

namespace {
int solve(std::vector<std::vector<int>> meetings) {
    std::sort(std::begin(meetings), std::end(meetings),
              [](const auto& lhs, const auto& rhs) {
                  return lhs.back() < rhs.back();
              });

    std::priority_queue<int> halls;
    halls.push(0);

    for (const std::vector<int>& meeting : meetings) {
        if (halls.top() <= meeting[0]) {
            halls.pop();
        }

        halls.push(meeting[1]);
    }

    return halls.size();
}
} // namespace

TEST_CASE(__FILE__, "[geeksforgeeks]") {
    REQUIRE(3 == solve({{0, 5}, {1, 2}, {1, 10}}));
}