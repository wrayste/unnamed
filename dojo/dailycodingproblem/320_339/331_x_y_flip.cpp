#include "catch2/catch.hpp" // for AssertionHandler, Sou...

namespace {
int xyFlip(const std::string& input) {
    if (input.empty()) {
        return 0;
    }

    int n = input.size();
    std::vector<int> y_on_left(input.size());
    std::vector<int> x_on_right(input.size());
    int prev_y = 0;
    int prev_x = 0;

    for (int i = 0; i < n; ++i) {
        y_on_left[i] = prev_y;
        prev_y += input[i] == 'y' ? 1 : 0;
    }

    for (int j = n - 1; 0 <= j; --j) {
        x_on_right[j] = prev_x;
        prev_x += input[j] == 'x' ? 1 : 0;
    }

    int num_flip = n;
    for (int k = 0; k < n; ++k) {
        num_flip = std::min(num_flip, y_on_left[k] + x_on_right[k]);
    }

    return num_flip;
}
} // namespace

TEST_CASE(__FILE__, "[dailycodingproblem]") {
    REQUIRE(2 == xyFlip("xyxxxyxyy"));
    REQUIRE(1 == xyFlip("yyx"));
    REQUIRE(2 == xyFlip("xyxxxyxyyy"));
    REQUIRE(3 == xyFlip("xyxxxyxyyx"));
    REQUIRE(4 == xyFlip("xyxxxyxyyxxx"));
    REQUIRE(2 == xyFlip("yyxxx"));
}