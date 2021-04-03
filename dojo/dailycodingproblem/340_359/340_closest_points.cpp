#include "catch2/catch.hpp" // for AssertionHandler, Sou...

#include <algorithm>
#include <cmath>
#include <vector>

namespace {
double calcDistance(const std::pair<int, int>& p1,
                    const std::pair<int, int>& p2) {
    return sqrt(pow(p1.first - p2.first, 2) + pow(p1.second - p2.second, 2));
}

std::tuple<std::pair<int, int>, std::pair<int, int>, double>
bruteForce(const std::vector<std::pair<int, int>>& points, const size_t begin,
           const size_t end) {
    double minDistance = std::numeric_limits<double>::max();
    size_t minI = 0;
    size_t minJ = 0;

    for (size_t i = begin; i < end; ++i) {
        for (size_t j = i + 1; j < end; ++j) {
            if (const double distance = calcDistance(points[i], points[j]);
                distance < minDistance) {
                std::tie(minDistance, minI, minJ) = std::tie(distance, i, j);
            }
        }
    }

    return {points[minI], points[minJ], minDistance};
}

std::tuple<std::pair<int, int>, std::pair<int, int>, double>
findClosestPointsStrip(const std::vector<std::pair<int, int>>& points,
                       const double min) {
    double minDistance = min;
    size_t minI = 0;
    size_t minJ = 0;

    for (size_t i = 0; i < points.size(); ++i) {
        for (size_t j = i + 1;
             j < points.size() && (points[j].second - points[i].second) < min;
             ++j) {
            if (const double distance = calcDistance(points[i], points[j]);
                distance < minDistance) {
                std::tie(minDistance, minI, minJ) = std::tie(distance, i, j);
            }
        }
    }

    return {points[minI], points[minJ], minDistance};
}

std::tuple<std::pair<int, int>, std::pair<int, int>, double>
findClosestPointsInner(const std::vector<std::pair<int, int>>& points,
                       const size_t begin, const size_t end) {
    if (end - begin <= 3) {
        return bruteForce(points, begin, end);
    } else {
        const size_t mid = begin + ((end - begin) / 2);

        const auto left = findClosestPointsInner(points, begin, mid);
        const auto right = findClosestPointsInner(points, mid, end);

        const double min = std::min(std::get<2>(left), std::get<2>(right));

        std::vector<std::pair<int, int>> stripPoints;
        for (size_t i = begin; i < end; ++i) {
            if (abs(points[i].first - points[mid].first) < min) {
                stripPoints.push_back(points[i]);
            }
        }

        std::sort(std::begin(stripPoints), std::end(stripPoints),
                  [](const auto& p1, const auto& p2) {
                      return p1.second < p2.second;
                  });

        const auto strip = findClosestPointsStrip(stripPoints, min);
        std::vector<std::remove_const_t<decltype(strip)>> results{
            {left, right, strip}};
        std::sort(std::begin(results), std::end(results),
                  [](const auto& r1, const auto& r2) {
                      return std::get<2>(r1) < std::get<2>(r2);
                  });
        return results.front();
    }
}

std::tuple<std::pair<int, int>, std::pair<int, int>>
findClosestPoints(std::vector<std::pair<int, int>> points) {
    std::sort(
        std::begin(points), std::end(points),
        [](const auto& p1, const auto& p2) { return p1.first < p2.first; });

    const auto result = findClosestPointsInner(points, 0, points.size());
    return {std::get<0>(result), std::get<1>(result)};
}
} // namespace

TEST_CASE(__FILE__, "[dailycodingproblem]") {
    const auto [p1, p2] = findClosestPoints(
        {{1, 1}, {-1, -1}, {3, 4}, {6, 1}, {-1, -6}, {-4, -3}});

    const auto expectedP1 = std::make_pair(-1, -1);
    const auto expectedP2 = std::make_pair(1, 1);

    REQUIRE(expectedP1 == p1);
    REQUIRE(expectedP2 == p2);
}