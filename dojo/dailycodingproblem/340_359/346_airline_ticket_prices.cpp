#include "catch2/catch.hpp" // for AssertionHandler, Sou...

#include <map>
#include <string>

namespace {
struct Route {
    std::vector<std::string> stops;
    size_t cost = 0;
};

void solve(const std::map<std::string, std::map<std::string, size_t>>& prices,
           const size_t maxConnections, const std::string& destination,
           Route& current, Route& cheapest) {
    if (current.stops.back() == destination) {
        if (current.cost < cheapest.cost || cheapest.stops.empty()) {
            cheapest = current;
        }
    } else if (maxConnections) {
        if (const auto nextStops = prices.find(current.stops.back());
            nextStops != std::end(prices)) {
            for (const auto& [nextStop, cost] : nextStops->second) {
                if (std::none_of(std::begin(current.stops),
                                 std::end(current.stops),
                                 [nextStop = nextStop](const auto& stop) {
                                     return stop == nextStop;
                                 })) {
                    current.stops.push_back(nextStop);
                    current.cost += cost;
                    solve(prices, maxConnections - 1, destination, current,
                          cheapest);
                    current.cost -= cost;
                    current.stops.pop_back();
                }
            }
        }
    }
}

std::vector<std::string>
solve(const std::map<std::string, std::map<std::string, size_t>>& prices,
      const size_t maxConnections, const std::string& origin,
      const std::string& destination) {
    Route cheapest;
    Route current;
    current.stops.push_back(origin);
    solve(prices, maxConnections, destination, current, cheapest);
    return cheapest.stops;
}
} // namespace

TEST_CASE(__FILE__, "[dailycodingproblem]") {
    std::map<std::string, std::map<std::string, size_t>> prices;
    prices["JFK"]["ATL"] = 150;
    prices["ATL"]["SFO"] = 400;
    prices["ORD"]["LAX"] = 200;
    prices["LAX"]["DFW"] = 80;
    prices["JFK"]["HKG"] = 800;
    prices["ATL"]["ORD"] = 90;
    prices["JFK"]["LAX"] = 500;

    const std::vector<std::string> expected{"JFK", "ATL", "ORD", "LAX"};
    REQUIRE(expected == solve(prices, 3, "JFK", "LAX"));
}