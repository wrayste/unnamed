#include "catch2/catch.hpp" // for AssertionHandler, Sou...

namespace {
double winProbability(double rating1, double rating2) {
    return 1 / (1 + pow(10.0, (rating1 - rating2) / 400));
}

void eloRating(double& ratingA, double& ratingB, int constant, bool isWinA) {
    const double winProbabilityA = winProbability(ratingB, ratingA);
    const double winProbabilityB = winProbability(ratingA, ratingB);

    if (isWinA == 1) {
        ratingA += constant * (1 - winProbabilityA);
        ratingB += constant * (0 - winProbabilityB);
    } else {
        ratingA += constant * (0 - winProbabilityA);
        ratingB += constant * (1 - winProbabilityB);
    }
}
} // namespace

TEST_CASE(__FILE__, "[dailycodingproblem]") {
    double ratingA = 1200;
    double ratingB = 1000;
    eloRating(ratingA, ratingB, 30, true);
    REQUIRE(Approx(1207.207642) == ratingA);
    REQUIRE(Approx(992.792419) == ratingB);
}