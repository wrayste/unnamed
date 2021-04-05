#include "catch2/catch.hpp" // for AssertionHandler, Sou...

#include <vector>

namespace {
bool isValidAmericanCrossword(std::vector<std::vector<int>> input) {
    const size_t n = input.size();

    if (input.empty()) {
        return false;
    }

    for (const auto& row : input) {
        if (n != row.size()) {
            return false;
        }
    }

    for (size_t i = 0; i < n; ++i) {
        size_t wordSize = 0;
        for (size_t j = 0; j < n; ++j) {
            if (input[i][j] == 0) {
                ++wordSize;
            } else if (0 < wordSize && wordSize < 3) {
                return false;
            } else {
                wordSize = 0;
            }
        }

        if (0 < wordSize && wordSize < 3) {
            return false;
        }
    }

    for (size_t j = 0; j < n; ++j) {
        size_t wordSize = 0;
        for (size_t i = 0; i < n; ++i) {
            if (input[i][j] == 0) {
                ++wordSize;
            } else if (0 < wordSize && wordSize < 3) {
                return false;
            } else {
                wordSize = 0;
            }
        }

        if (0 < wordSize && wordSize < 3) {
            return false;
        }
    }

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            if (input[i][j] != input[n - i - 1][n - j - 1]) {
                return false;
            }
        }
    }

    std::function<void(size_t, size_t)> bfs;
    bfs = [&](const size_t i, const size_t j) {
        if (0 == std::exchange(input[i][j], 1)) {
            if (0 < i) {
                bfs(i - 1, j);
            }
            if (0 < j) {
                bfs(i, j - 1);
            }
            if (i + 1 < n) {
                bfs(i + 1, j);
            }
            if (j + 1 < n) {
                bfs(i, j + 1);
            }
        }
    };

    bool isSearched = false;
    for (size_t i = 0; i < n && !isSearched; ++i) {
        for (size_t j = 0; j < n && !isSearched; ++j) {
            if (input[i][j] == 0) {
                bfs(i, j);
                isSearched = true;
            }
        }
    }

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            if (input[i][j] == 0) {
                return false;
            }
        }
    }

    return true;
}
} // namespace

TEST_CASE(__FILE__, "[dailycodingproblem]") {
    {
        std::vector<std::vector<int>> input{
            {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
            {1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1},
            {0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0},
            {1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1},
            {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}};

        REQUIRE(isValidAmericanCrossword(input));
    }

    {
        std::vector<std::vector<int>> input{
            {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
            {1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1},
            {0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0},
            {1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1},
            {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}};

        REQUIRE(!isValidAmericanCrossword(input));
    }
}