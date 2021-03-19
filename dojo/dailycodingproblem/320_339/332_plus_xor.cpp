#include "catch2/catch.hpp" // for AssertionHandler, Sou...

namespace {
size_t solve(size_t m, size_t s) {
    int n = s - m;

    size_t result = 1;
    for (; m && n; m >>= 1, n >>= 1) {
        size_t mBit = m & 1;
        size_t nBit = n & 1;

        if (mBit ^ nBit) {
            result *= 2;
        }
    }

    return result;
}
} // namespace

TEST_CASE(__FILE__, "[dailycodingproblem]") {
    REQUIRE(4 == solve(2, 7));
}