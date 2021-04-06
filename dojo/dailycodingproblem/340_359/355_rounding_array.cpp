#include "catch2/catch.hpp" // for AssertionHandler, Sou...

#include <cmath>
#include <vector>

namespace {
std::vector<long> roundArray(const std::vector<double>& prices) {
    std::vector<std::pair<double, size_t>> ceilDifferences;
    double total = 0.0;
    long floorTotal = 0;

    for (const double price : prices) {
        ceilDifferences.emplace_back(ceil(price) - price,
                                     ceilDifferences.size());

        total += price;
        floorTotal += floor(price);
    }

    std::sort(std::begin(ceilDifferences), std::end(ceilDifferences));

    std::vector<long> result(prices.size());
    for (size_t i = 0; i < prices.size(); ++i) {
        const size_t position = ceilDifferences[i].second;
        result[position] = i < round(total) - floorTotal
                               ? ceil(prices[position])
                               : floor(prices[position]);
    }
    return result;
}
} // namespace

TEST_CASE(__FILE__, "[dailycodingproblem]") {
    const std::vector<long> expected{1, 2, 5};
    REQUIRE(expected == roundArray({1.3, 2.3, 4.4}));
}