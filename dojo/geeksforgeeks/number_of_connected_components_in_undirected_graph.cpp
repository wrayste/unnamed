#include <__hash_table>  // for __hash_const_iterator, operator!=
#include <iterator>      // for end
#include <optional>      // for optional
#include <unordered_map> // for unordered_map, operator!=, __hash_map_co...
#include <unordered_set> // for unordered_set
#include <utility>       // for pair

#include "catch2/catch.hpp" // for AssertionHandler, SourceLineInfo, StringRef

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

void search(const Graph& g, int src, std::unordered_set<int>& visited) {
    if (visited.insert(src).second) {
        if (const auto i = g.g.find(src); i != std::end(g.g)) {
            for (const auto dst : i->second) {
                search(g, dst, visited);
            }
        }
    }
}

int countConnectedComponents(const Graph& g) {
    std::unordered_set<int> visited;

    int result = 0;
    for (const auto& [k, _] : g.g) {
        if (!visited.count(k)) {
            ++result;
            search(g, k, visited);
        }
    }

    return result;
}
} // namespace

TEST_CASE(__FILE__, "[geeksforgeeks]") {
    {
        Graph g;
        g.addEdge(1, 0);
        g.addEdge(2, 3);
        g.addEdge(3, 4);
        REQUIRE(2 == countConnectedComponents(g));
    }
}