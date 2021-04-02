#include "catch2/catch.hpp" // for AssertionHandler, Sou...

#include <queue>
#include <vector>

namespace {
size_t solveCombinationLock(const size_t target,
                            const std::vector<size_t>& deadends) {
    std::vector<int> visited(1000);
    for (const size_t deadend : deadends) {
        visited[deadend] = true;
    }

    const auto prev = [](size_t i) { return 0 < i ? i - 1 : 9; };
    const auto next = [](size_t i) { return i < 9 ? i + 1 : 0; };
    const auto combine = [](size_t i, size_t j, size_t k) {
        return i + (j * 10) + (k * 100);
    };

    std::queue<std::pair<size_t, size_t>> work;
    work.emplace(0, 0);

    while (!work.empty()) {
        auto [current, distance] = work.front();
        work.pop();

        if (std::exchange(visited[current], 1)) {
            continue;
        } else if (current == target) {
            return distance;
        } else {
            const size_t first = current % 10;
            current /= 10;
            const size_t second = current % 10;
            current /= 10;
            const size_t third = current % 10;

            ++distance;

            work.emplace(combine(next(first), second, third), distance);
            work.emplace(combine(prev(first), second, third), distance);
            work.emplace(combine(first, next(second), third), distance);
            work.emplace(combine(first, prev(second), third), distance);
            work.emplace(combine(first, second, next(third)), distance);
            work.emplace(combine(first, second, prev(third)), distance);
        }
    }

    return std::numeric_limits<size_t>::max();
}
} // namespace

TEST_CASE(__FILE__, "[dailycodingproblem]") {
    REQUIRE(1 == solveCombinationLock(9, {}));
    REQUIRE(2 == solveCombinationLock(909, {}));
    REQUIRE(4 == solveCombinationLock(909, {9, 900}));
}