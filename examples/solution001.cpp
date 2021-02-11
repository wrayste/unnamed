#include "catch2/catch.hpp"

int sumOfArithmeticSeries(const int begin, const int end, const int step) {
    const int n = (end - begin) / step;
    return (n + 1) * (begin + end) / 2;
}

TEST_CASE("solution001", "[projectEuler]") {
    auto result = sumOfArithmeticSeries(3, 999, 3) +
                  sumOfArithmeticSeries(5, 995, 5) -
                  sumOfArithmeticSeries(15, 990, 15);

    REQUIRE(233168 == result);
}
