#include "catch2/catch.hpp" // for AssertionHandler, Sou...

namespace {
size_t calculateHeight(const std::string& input) {
    size_t max = 0;
    size_t current = 0;

    for (const char c : input) {
        switch (c) {
        case '(':
            max = std::max(max, ++current);
            break;
        case ')':
            --current;
            break;
        }
    }

    return max;
}
} // namespace

TEST_CASE(__FILE__, "[dailycodingproblem]") {
    REQUIRE(1 == calculateHeight("(00)"));
    REQUIRE(2 == calculateHeight("((00)(00))"));
    REQUIRE(4 == calculateHeight("((((00)0)0)0)"));
}