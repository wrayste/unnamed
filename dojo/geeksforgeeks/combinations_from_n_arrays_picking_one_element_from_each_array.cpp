#include <vector> // for vector, operator==, allocator

#include "catch2/catch.hpp" // for AssertionHandler, SourceLineInfo, StringRef

void solve(const std::vector<std::vector<int>>& input, int i,
           std::vector<int>& temp, std::vector<std::vector<int>>& output) {
    if (i < input.size()) {
        for (int j = 0; j < input[i].size(); ++j) {
            temp.push_back(input[i][j]);
            solve(input, i + 1, temp, output);
            temp.pop_back();
        }
    } else {
        output.push_back(temp);
    }
}

std::vector<std::vector<int>>
solve(const std::vector<std::vector<int>>& input) {
    std::vector<int> temp;
    std::vector<std::vector<int>> output;
    solve(input, 0, temp, output);
    return output;
}

TEST_CASE(__FILE__, "[geeksforgeeks]") {
    const std::vector<std::vector<int>> input{{1, 2, 3}, {4}, {5, 6}};

    const std::vector<std::vector<int>> expected{
        {1, 4, 5}, {1, 4, 6}, {2, 4, 5}, {2, 4, 6}, {3, 4, 5}, {3, 4, 6}};

    REQUIRE(expected == solve(input));
}