#include "catch2/catch.hpp" // for AssertionHandler, Sou...

namespace {
size_t sameNumberOfOneBits(size_t x) {
    size_t next = 0;

    if (x) {
        size_t rightOne = x & -(signed)x;
        size_t nextHigherOneBit = x + rightOne;
        size_t rightOnesPattern = x ^ nextHigherOneBit;
        rightOnesPattern = (rightOnesPattern) / rightOne;
        rightOnesPattern >>= 2;
        next = nextHigherOneBit | rightOnesPattern;
    }

    return next;
}
} // namespace

TEST_CASE(__FILE__, "[dailycodingproblem]") {
    REQUIRE(163 == sameNumberOfOneBits(156));
}