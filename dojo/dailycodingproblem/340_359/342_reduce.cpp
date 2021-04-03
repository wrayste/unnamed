#include "catch2/catch.hpp" // for AssertionHandler, Sou...

#include <vector>

namespace {
template <class InputIt, class T, class BinaryOperation>
constexpr T myReduce(InputIt first, InputIt last, T init, BinaryOperation op) {
    for (; first != last; ++first) {
        init = op(std::move(init), *first);
    }
    return init;
}
} // namespace

TEST_CASE(__FILE__, "[dailycodingproblem]") {
    const std::vector<int> nums{1, 2, 3};
    REQUIRE(6 == myReduce(std::begin(nums), std::end(nums), 0,
                          [](const auto& i, const auto& j) { return i + j; }));
}