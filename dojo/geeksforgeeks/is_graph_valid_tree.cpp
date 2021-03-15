#include <unordered_map> // for unordered_map
#include <unordered_set> // for unordered_set

#include "catch2/catch.hpp" // for AssertionHandler, operator""_catch_sr

namespace {
struct Graph {
    std::unordered_map<int, std::unordered_set<int>> g;
    std::optional<int> f;

    void addEdge(int src, int dst) {
        f = src;
        g[src].insert(dst);
        g[dst].insert(src);
    }
};

bool isCyclic(const Graph& g, int src, std::unordered_set<int>& visited,
              std::optional<int> parent) {
    visited.insert(src);

    if (const auto i = g.g.find(src); i != std::end(g.g)) {
        for (const auto& dst : i->second) {
            if (!visited.count(dst)) {
                if (isCyclic(g, dst, visited, src)) {
                    return true;
                }
            } else if (parent && dst != *parent) {
                return true;
            }
        }
    }

    return false;
}

bool isTree(const Graph& g) {
    std::unordered_set<int> visited;

    if (g.f && isCyclic(g, *(g.f), visited, std::nullopt)) {
        return false;
    }

    return visited.size() == g.g.size();
}
} // namespace

TEST_CASE(__FILE__, "[geeksforgeeks]") {
    {
        Graph g;
        g.addEdge(1, 0);
        g.addEdge(0, 2);
        g.addEdge(0, 3);
        g.addEdge(3, 4);
        REQUIRE(isTree(g));
    }

    {
        Graph g;
        g.addEdge(1, 0);
        g.addEdge(0, 2);
        g.addEdge(2, 1);
        g.addEdge(0, 3);
        g.addEdge(3, 4);
        REQUIRE(!isTree(g));
    }
}