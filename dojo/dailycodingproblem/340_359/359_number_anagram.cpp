#include "catch2/catch.hpp" // for AssertionHandler, Sou...

#include <string>
#include <unordered_map>
#include <vector>

namespace {
std::string unscramble(const std::string& anagram) {
    std::unordered_map<char, size_t> letterCounts;
    for (const auto& c : anagram) {
        ++letterCounts[c];
    }

    std::vector<size_t> intCounts(10ul, 0ul);

    intCounts[0] = letterCounts['z'];
    intCounts[2] = letterCounts['w'];
    intCounts[4] = letterCounts['u'];
    intCounts[6] = letterCounts['x'];
    intCounts[8] = letterCounts['g'];

    intCounts[3] = letterCounts['h'] - intCounts[8];
    intCounts[5] = letterCounts['f'] - intCounts[4];
    intCounts[7] = letterCounts['s'] - intCounts[6];

    intCounts[1] =
        letterCounts['o'] - intCounts[0] - intCounts[2] - intCounts[4];
    intCounts[9] =
        letterCounts['i'] - intCounts[5] - intCounts[6] - intCounts[8];

    std::string result;
    for (size_t i = 0; i < intCounts.size(); ++i) {
        result += std::string(intCounts[i], '0' + i);
    }
    return result;
}
} // namespace

TEST_CASE(__FILE__, "[dailycodingproblem]") {
    REQUIRE("357" == unscramble("niesevehrtfeev"));
}