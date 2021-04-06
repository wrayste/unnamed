#include "catch2/catch.hpp" // for AssertionHandler, Sou...

#include <random>
#include <set>
#include <vector>

namespace {
int approximateMedium(const std::vector<int>& input) {
    if (input.empty()) {
        return 0;
    }

    std::mt19937 generator;
    std::uniform_int_distribution<int> distribution(0, input.size() - 1);

    const size_t k = 10 * log2(input.size());

    std::set<int> selected;
    for (size_t i = 0; i < k; ++i) {
        selected.insert(input[distribution(generator)]);
    }

    auto itr = std::begin(selected);
    std::advance(itr, (selected.size() / 2) - 1);
    return *itr;
}
} // namespace

TEST_CASE(__FILE__, "[dailycodingproblem]") {
    REQUIRE(4 == approximateMedium({1, 3, 2, 4, 5, 6, 8, 7}));
}