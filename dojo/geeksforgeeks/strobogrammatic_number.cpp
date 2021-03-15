#include <iosfwd> // for string
#include <string> // for operator+, basic_string, operator==, all...
#include <vector> // for vector, operator==

#include "catch2/catch.hpp" // for AssertionHandler, SourceLineInfo, StringRef

namespace {
std::vector<std::string> solve(int i, int n) {
    if (i == 0) {
        return {""};
    } else if (i == 1) {
        return {"0", "1", "8"};
    } else {
        std::vector<std::string> result;
        for (auto middle : solve(i - 2, n)) {
            if (i != n) {
                result.push_back("0" + middle + "0");
            }

            result.push_back("1" + middle + "1");
            result.push_back("6" + middle + "9");
            result.push_back("8" + middle + "8");
            result.push_back("9" + middle + "6");
        }
        return result;
    }
}

std::vector<std::string> solve(int n) {
    return solve(n, n);
}
} // namespace

TEST_CASE(__FILE__, "[geeksforgeeks]") {
    const std::vector<std::string> expected{"101", "609", "808", "906",
                                            "111", "619", "818", "916",
                                            "181", "689", "888", "986"};
    REQUIRE(expected == solve(3));
}