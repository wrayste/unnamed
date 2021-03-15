#include <iosfwd> // for string
#include <string> // for operator==, basic_string
#include <vector> // for vector, operator==, allocator

#include "catch2/catch.hpp" // for AssertionHandler, SourceLineInfo, StringRef

void solve(int n, int pos, int open, int close, std::string& temp,
           std::vector<std::string>& output) {
    if (n == close) {
        output.push_back(temp);
    } else {
        if (close < open) {
            temp[pos] = ')';
            solve(n, pos + 1, open, close + 1, temp, output);
        }

        if (open < n) {
            temp[pos] = '(';
            solve(n, pos + 1, open + 1, close, temp, output);
        }
    }
}

std::vector<std::string> solve(int n) {
    std::vector<std::string> output;
    if (0 < n) {
        std::string temp(2 * n, ' ');
        solve(n, 0, 0, 0, temp, output);
    }
    return output;
}

TEST_CASE(__FILE__, "[geeksforgeeks]") {
    {
        const std::vector<std::string> expected{};
        REQUIRE(expected == solve(0));
    }

    {
        const std::vector<std::string> expected{"()"};
        REQUIRE(expected == solve(1));
    }

    {
        const std::vector<std::string> expected{"()()", "(())"};
        REQUIRE(expected == solve(2));
    }

    {
        const std::vector<std::string> expected{"()()()", "()(())", "(())()",
                                                "(()())", "((()))"};
        REQUIRE(expected == solve(3));
    }

    {
        const std::vector<std::string> expected{
            "()()()()", "()()(())", "()(())()", "()(()())", "()((()))",
            "(())()()", "(())(())", "(()())()", "(()()())", "(()(()))",
            "((()))()", "((())())", "((()()))", "(((())))"};
        REQUIRE(expected == solve(4));
    }
}