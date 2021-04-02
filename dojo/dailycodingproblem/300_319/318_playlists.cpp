#include "catch2/catch.hpp" // for AssertionHandler, Sou...

#include <vector>

namespace {
size_t solve(size_t playlistLength, size_t songsDownloaded,
             size_t repeatBuffer) {
    std::vector<std::vector<size_t>> dp(
        playlistLength + 1, std::vector<size_t>(songsDownloaded + 1));
    dp[0][0] = 1;

    for (size_t i = 1; i <= playlistLength; ++i) {
        for (size_t j = 1; j <= songsDownloaded; ++j) {
            dp[i][j] += dp[i - 1][j - 1] * (songsDownloaded - j + 1);

            if (repeatBuffer < j) {
                dp[i][j] += dp[i - 1][j] * (j - repeatBuffer);
            }

            dp[i][j] %= 1000000007;
        }
    }

    return dp[playlistLength][songsDownloaded];
}
} // namespace

TEST_CASE(__FILE__, "[dailycodingproblem]") {
    REQUIRE(6 == solve(3, 3, 1));
    REQUIRE(6 == solve(3, 2, 0));
    REQUIRE(2 == solve(3, 2, 1));
}