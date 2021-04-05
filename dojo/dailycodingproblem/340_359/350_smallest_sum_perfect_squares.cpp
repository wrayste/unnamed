#include "catch2/catch.hpp" // for AssertionHandler, Sou...

namespace {
size_t solve(const size_t n) {
    if (n <= 3) {
        return n;
    }

    std::vector<size_t> dp(n + 1);
    std::iota(std::begin(dp), std::end(dp), 0);

    for (size_t i = 4; i <= n; ++i) {
        for (size_t k = 1; k * k <= i; ++k) {
            dp[i] = std::min(dp[i], 1 + dp[i - k * k]);
        }
    }

    return dp.back();
}
} // namespace

TEST_CASE(__FILE__, "[dailycodingproblem]") {
    REQUIRE(1 == solve(4));
    REQUIRE(2 == solve(17));
    REQUIRE(2 == solve(18));
}