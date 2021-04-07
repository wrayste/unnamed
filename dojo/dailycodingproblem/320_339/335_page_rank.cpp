#include "catch2/catch.hpp" // for AssertionHandler, Sou...

#include <map>
#include <set>

namespace {
double calculateScore(const size_t page, const double damping,
                      const std::map<size_t, std::set<size_t>>& graph,
                      const std::map<size_t, double>& pageScores) {
    double aggScore = 0.0;
    for (const auto& [other, otherLinks] : graph) {
        if (const auto i = graph.find(other);
            i != std::end(graph) && i->second.contains(page)) {
            const auto j = pageScores.find(other);
            const double pageScore = j != std::end(pageScores) ? j->second : 0;
            aggScore += pageScore / i->second.size();
        }
    }

    return ((1 - damping) / graph.size()) + (damping * aggScore);
}

std::map<size_t, double>
rankPages(const std::map<size_t, std::set<size_t>>& graph,
          const double damping) {
    std::map<size_t, double> result;

    double startProb = 1.0 / graph.size();
    for (const auto& [node, nodeLinks] : graph) {
        result[node] = startProb;
    }

    for (const auto& [node, nodeLinks] : graph) {
        result[node] = calculateScore(node, damping, graph, result);
    }

    for (const auto& [k, v] : result) {
        WARN(k << ": " << v);
    }

    return result;
}

} // namespace

TEST_CASE(__FILE__, "[dailycodingproblem]") {
    std::map<size_t, std::set<size_t>> graph;
    graph[0].insert(1);
    graph[0].insert(2);
    graph[1].insert(2);

    std::map<size_t, double> expectedRanks;
    expectedRanks[0] = 0.075;
    expectedRanks[1] = 0.106875;

    const auto actualRanks = rankPages(graph, 0.85);

    REQUIRE(expectedRanks.size() == actualRanks.size());
    REQUIRE(std::equal(std::begin(expectedRanks), std::end(expectedRanks),
                       std::begin(actualRanks),
                       [](const auto expected, const auto actual) {
                           REQUIRE(expected.first == actual.first);
                           REQUIRE(Approx(expected.second) == actual.second);
                           return true;
                       }));
}