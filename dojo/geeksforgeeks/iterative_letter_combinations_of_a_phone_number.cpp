#include <iosfwd> // for string
#include <string> // for basic_string, operator==
#include <vector> // for vector, operator==, allocator, __vector_...

#include "catch2/catch.hpp" // for AssertionHandler, SourceLineInfo, StringRef

namespace {
void solve(const std::vector<int>& input, int i, std::string& temp,
           std::vector<std::string>& output) {
    static const std::vector<std::string> digitsToChars{
        "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

    if (i < input.size()) {
        for (const char c : digitsToChars[input[i]]) {
            temp.push_back(c);
            solve(input, i + 1, temp, output);
            temp.pop_back();
        }
    } else {
        output.push_back(temp);
    }
}

std::vector<std::string> solve(const std::vector<int>& input) {
    std::string temp;
    std::vector<std::string> output;
    solve(input, 0, temp, output);
    return output;
}
} // namespace

TEST_CASE(__FILE__, "[geeksforgeeks]") {
    const std::vector<std::string> expected{"ad", "ae", "af", "bd", "be",
                                            "bf", "cd", "ce", "cf"};
    REQUIRE(expected == solve({2, 3}));
}