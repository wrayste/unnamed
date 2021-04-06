#include "catch2/catch.hpp" // for AssertionHandler, Sou...

#include <stack>
#include <vector>

namespace {
template <typename Function>
void dfs(size_t u, const std::vector<std::vector<size_t>>& adj,
         std::vector<bool>& visited, Function&& function) {
    if (!visited[u]) {
        visited[u] = 1;

        for (const size_t v : adj[u]) {
            dfs(v, adj, visited, function);
        }

        function(u);
    }
}

bool isTwoSatisfiable(const size_t terms,
                      const std::vector<std::pair<int, int>> expression) {

    std::vector<std::vector<size_t>> adj(2 * terms + 1);
    std::vector<std::vector<size_t>> adjInv(2 * terms + 1);
    const auto addEdge = [&adj, &adjInv](const size_t a, const size_t b) {
        adj[a].push_back(b);
        adjInv[b].push_back(a);
    };

    for (const auto& [a, b] : expression) {
        if (a > 0 && b > 0) {
            addEdge(a + terms, b);
            addEdge(b + terms, a);
        } else if (a > 0 && b < 0) {
            addEdge(a + terms, terms - b);
            addEdge(-b, a);
        } else if (a < 0 && b > 0) {
            addEdge(-a, b);
            addEdge(b + terms, terms - a);
        } else {
            addEdge(-a, terms - b);
            addEdge(-b, terms - a);
        }
    }

    std::vector<bool> visited(2 * terms + 1);
    std::stack<size_t> s;
    for (size_t u = 1; u <= 2 * terms; ++u) {
        dfs(u, adj, visited, //
            [&](const size_t u) { s.push(u); });
    }

    std::vector<bool> visitedInv(2 * terms + 1);
    std::vector<size_t> scc((2 * terms) + 1);
    for (size_t counter = 1; !s.empty(); ++counter, s.pop()) {
        dfs(s.top(), adjInv, visitedInv,
            [&](const size_t u) { scc[u] = counter; });
    }

    for (size_t i = 1; i <= terms; ++i) {
        if (scc[i] == scc[i + terms]) {
            return false;
        }
    }

    return true;
}
} // namespace

TEST_CASE(__FILE__, "[dailycodingproblem]") {
    {
        const size_t terms = 5;
        const std::vector<std::pair<int, int>> expression{
            {1, 2}, {-2, 3}, {-1, -2}, {3, 4}, {-3, 5}, {-4, -5}, {-3, 4}};

        REQUIRE(isTwoSatisfiable(terms, expression));
    }

    {
        const size_t terms = 3;
        const std::vector<std::pair<int, int>> expression{
            {-3, 2}, {2, 3}, {-2, 3}, {-3, 1}};

        REQUIRE(isTwoSatisfiable(terms, expression));
    }
}