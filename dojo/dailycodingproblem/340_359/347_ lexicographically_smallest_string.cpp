#include "catch2/catch.hpp" // for AssertionHandler, Sou...

#include <string>

namespace {
std::string solve(std::string s, size_t k) {
    std::string result = s;
    std::string smallests;

    while (!s.empty()) {
        char smallest = s[0];
        char smallestIndex = 0;

        for (size_t i = 0; i < k && i < s.size(); ++i) {
            if (s[i] < smallest) {
                std::tie(smallest, smallestIndex) = std::tie(s[i], i);
            }
        }

        s = std::string(s, 0, smallestIndex) +
            std::string(s, smallestIndex + 1);

        smallests += smallest;

        if (const std::string candidate = s + smallests; candidate < result) {
            result = candidate;
        }
    }

    return result;
}
} // namespace

TEST_CASE(__FILE__, "[dailycodingproblem]") {
    REQUIRE("ailyd" == solve("daily", 1));
}