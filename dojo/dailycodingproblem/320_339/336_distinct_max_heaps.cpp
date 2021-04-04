#include "catch2/catch.hpp" // for AssertionHandler, Sou...

#include <vector>

namespace {
int choose(int n, int k, std::vector<std::vector<int>>& nck) {
    if (k > n) {
        return 0;
    } else if (n <= 1) {
        return 1;
    } else if (k == 0) {
        return 1;
    } else if (nck[n][k] != -1) {
        return nck[n][k];
    } else {
        const int answer = choose(n - 1, k - 1, nck) + choose(n - 1, k, nck);
        nck[n][k] = answer;
        return answer;
    }
}

int getLeft(int n, const std::vector<int>& log2) {
    if (n == 1) {
        return 0;
    }

    const int h = log2[n];
    const int numh = (1 << h);
    const int last = n - ((1 << h) - 1);

    return (last >= (numh / 2)) ? (1 << h) - 1
                                : (1 << h) - 1 - ((numh / 2) - last);
}

int numberOfHeaps(int n, std::vector<int>& dp,
                  std::vector<std::vector<int>>& nck,
                  const std::vector<int>& log2) {
    if (n <= 1) {
        return 1;
    }

    if (dp[n] != -1) {
        return dp[n];
    }

    const int left = getLeft(n, log2);
    dp[n] = choose(n - 1, left, nck) * numberOfHeaps(left, dp, nck, log2) *
            numberOfHeaps(n - 1 - left, dp, nck, log2);
    return dp[n];
}

int solve(int n) {
    std::vector<int> dp(n + 1, -1);
    std::vector<std::vector<int>> nck(n + 1, std::vector<int>(n + 1, -1));
    std::vector<int> log2(n + 1, -1);

    int currLog2 = -1;
    int currPower2 = 1;

    for (int i = 1; i <= n; ++i) {
        if (currPower2 == i) {
            currLog2++;
            currPower2 *= 2;
        }
        log2[i] = currLog2;
    }

    return numberOfHeaps(n, dp, nck, log2);
}
} // namespace

TEST_CASE(__FILE__, "[dailycodingproblem]") {
    REQUIRE(3360 == solve(10));
}