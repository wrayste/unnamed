#include "catch2/catch.hpp" // for AssertionHandler, Sou...

#include <algorithm>
#include <vector>

namespace {
bool twentyFourGame(const std::vector<int>& nums) {
    for (size_t i = 0; i < nums.size() - 1; ++i) {
        for (size_t j = i + 1; j < nums.size(); ++j) {
            const double a = nums[i];
            const double b = nums[j];

            std::vector<double> operations{a + b, a * b, a - b, b - a};

            if (a) {
                operations.push_back(b / a);
            }

            if (b) {
                operations.push_back(a / b);
            }

            if (2 < nums.size()) {
                std::vector<int> nextNums;
                for (size_t k = 0; k < i; ++k) {
                    if (k != i && k != j) {
                        nextNums.push_back(nums[k]);
                    }
                }

                for (const auto operation : operations) {
                    nextNums.push_back(operation);
                    if (twentyFourGame(nextNums)) {
                        return true;
                    }
                    nextNums.pop_back();
                }
            } else {
                return std::any_of(std::begin(operations), std::end(operations),
                                   [](double d) { return abs(d - 24) < 0.1; });
            }
        }
    }

    return false;
}
} // namespace

TEST_CASE(__FILE__, "[dailycodingproblem]") {
    REQUIRE(twentyFourGame({4, 1, 8, 7}));
    REQUIRE(!twentyFourGame({1, 2, 1, 2}));
}