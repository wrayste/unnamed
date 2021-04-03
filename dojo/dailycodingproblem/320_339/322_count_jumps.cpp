#include "catch2/catch.hpp" // for AssertionHandler, Sou...

namespace {
size_t countJumps(size_t n) {
    const auto getSum = [](int x) { return (x * (x + 1)) / 2; };

    size_t ans = 0;

    for (; getSum(ans) < n || (getSum(ans) - n) & 1; ++ans)
        ;

    return ans;
}
} // namespace

TEST_CASE(__FILE__, "[dailycodingproblem]") {
    REQUIRE(5 == countJumps(9));
}