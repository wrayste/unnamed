#include <functional> // for greater
#include <iterator>   // for begin
#include <queue>      // for priority_queue
#include <vector>     // for vector, operator==, allocator

#include "catch2/catch.hpp" // for AssertionHandler, operator""_catch_sr

namespace {
void sort(std::vector<int>& nums, int k) {
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap(
        std::begin(nums), std::begin(nums) + k + 1);

    int index = 0;
    for (int i = k + 1; i < nums.size(); ++i) {
        nums[index++] = minHeap.top();
        minHeap.pop();
        minHeap.push(nums[i]);
    }

    for (; !minHeap.empty(); minHeap.pop()) {
        nums[index++] = minHeap.top();
    }
}
} // namespace

TEST_CASE(__FILE__, "[geeksforgeeks]") {
    {
        std::vector<int> input{6, 5, 3, 2, 8, 10, 9};
        sort(input, 3);
        std::vector<int> expected{2, 3, 5, 6, 8, 9, 10};
        REQUIRE(expected == input);
    }

    {
        std::vector<int> input{10, 9, 8, 7, 4, 70, 60, 50};
        sort(input, 4);
        std::vector<int> expected{4, 7, 8, 9, 10, 50, 60, 70};
        REQUIRE(expected == input);
    }
}