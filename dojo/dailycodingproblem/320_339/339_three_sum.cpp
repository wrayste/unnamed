#include "catch2/catch.hpp" // for AssertionHandler, Sou...

#include <algorithm>
#include <vector>

namespace {
bool threeSum(std::vector<int> nums, int target) {
    std::sort(std::begin(nums), std::end(nums));

    for (int i = 1; i < nums.size(); ++i) {
        int j = i - 1;
        int k = i + 1;

        while (0 <= j && k < nums.size()) {
            const int sum = nums[i] + nums[j] + nums[k];
            if (sum == target) {
                return true;
            } else if (sum < target) {
                ++k;
            } else {
                --j;
            }
        }
    }

    return false;
}
} // namespace

TEST_CASE(__FILE__, "[dailycodingproblem]") {
    REQUIRE(threeSum({20, 303, 3, 4, 25}, 49));
    REQUIRE(!threeSum({1, 2, 3}, 7));
}