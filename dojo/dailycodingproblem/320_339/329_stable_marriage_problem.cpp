#include "catch2/catch.hpp" // for AssertionHandler, Sou...

#include <algorithm>
#include <set>
#include <unordered_map>
#include <vector>

namespace {
std::vector<std::pair<int, int>>
findStableMarriages(const std::vector<std::vector<int>>& guy_preferences,
                    const std::vector<std::vector<int>>& gal_preferences) {
    const auto marriageStability = [&](const int gal, const int guy) {
        const auto& gal_preference = gal_preferences[gal];
        return std::distance(std::begin(gal_preference),
                             std::find(std::begin(gal_preference),
                                       std::end(gal_preference), guy));
    };

    std::vector<std::set<int>> guy_tries(guy_preferences.size());

    std::vector<int> guy_partners(guy_preferences.size(), -1);
    std::vector<int> gal_partners(gal_preferences.size(), -1);

    while (std::any_of(std::begin(guy_partners), std::end(guy_partners),
                       [](const auto& i) { return i == -1; })) {
        const int guy = std::distance(
            std::begin(guy_partners),
            std::find(std::begin(guy_partners), std::end(guy_partners), -1));
        const int gal = *std::find_if(
            std::begin(guy_preferences[guy]), std::end(guy_preferences[guy]),
            [&](const auto& gal) { return !guy_tries[guy].contains(gal); });

        guy_tries[guy].insert(gal);

        if (gal_partners[gal] == -1) {
            guy_partners[guy] = gal;
            gal_partners[gal] = guy;
        } else if (marriageStability(gal, guy) <
                   marriageStability(gal, gal_partners[gal])) {
            guy_partners[gal_partners[gal]] = -1;
            guy_partners[guy] = gal;
            gal_partners[gal] = guy;
        }
    }

    std::vector<std::pair<int, int>> result;
    for (int guy = 0; guy < guy_partners.size(); ++guy) {
        result.emplace_back(guy, guy_partners[guy]);
    }
    return result;
}
} // namespace

TEST_CASE(__FILE__, "[dailycodingproblem]") {
    const std::vector<std::vector<int>> guy_preferences{
        {2, 0, 1}, {2, 1, 0}, {1, 2, 0}};
    const std::vector<std::vector<int>> gal_preferences{
        {0, 1, 2}, {1, 0, 2}, {1, 2, 0}};

    std::vector<std::pair<int, int>> expectedMarriages{{0, 0}, {1, 2}, {2, 1}};
    REQUIRE(expectedMarriages ==
            findStableMarriages(guy_preferences, gal_preferences));
}