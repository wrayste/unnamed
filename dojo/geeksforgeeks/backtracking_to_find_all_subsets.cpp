#include <vector> // for vector, operator==, allocator

#include "catch2/catch.hpp" // for AssertionHandler, SourceLineInfo, StringRef

void solve(const std::vector<int>& input, int i, std::vector<int>& temp,
           std::vector<std::vector<int>>& output) {
    if (i < input.size()) {
        temp.push_back(input[i]);
        output.push_back(temp);
        solve(input, i + 1, temp, output);
        temp.pop_back();
        solve(input, i + 1, temp, output);
    }
}

std::vector<std::vector<int>> solve(const std::vector<int>& input) {
    std::vector<int> temp;
    std::vector<std::vector<int>> output;
    solve(input, 0, temp, output);
    return output;
}

TEST_CASE(__FILE__, "[geeksforgeeks]") {
    const std::vector<std::vector<int>> expected{{1}, {1, 2}, {1, 2, 3}, {1, 3},
                                                 {2}, {2, 3}, {3}};
    REQUIRE(expected == solve({1, 2, 3}));
}