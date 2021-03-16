#include "catch2/catch.hpp" // for AssertionHandler, Sou...

namespace {
template <typename F>
int findCelebrity(const int people, const F& knows) {
    int result = 0;

    for (int i = 0; i < people; ++i) {
        result = knows(result, i) ? i : result;
    }

    return result;
}
} // namespace

TEST_CASE(__FILE__, "[dailycodingproblem]") {
    const std::vector<std::vector<int>> knowsData = {{1, 0, 1, 0}, //
                                                     {0, 1, 1, 0},
                                                     {1, 0, 1, 0},
                                                     {0, 1, 1, 1}};

    const auto knows = [&knowsData](int a, int b) {
        return 0 <= a && a < knowsData.size() && 0 <= b &&
               b < knowsData[a].size() && knowsData[a][b];
    };

    REQUIRE(2 == findCelebrity(knowsData.size(), knows));
}