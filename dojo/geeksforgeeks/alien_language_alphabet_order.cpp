#include <algorithm>     // for find_if
#include <iosfwd>        // for string
#include <iterator>      // for end, begin
#include <unordered_map> // for unordered_map, __hash_map_iterator, oper...
#include <unordered_set> // for unordered_set
#include <utility>       // for pair
#include <vector>        // for vector, operator==, __vector_base<>::val...

#include "catch2/catch.hpp" // for AssertionHandler, operator""_catch_sr

namespace {
std::vector<char>
topologicalSort(std::unordered_map<char, std::unordered_set<char>> graph) {
    std::vector<char> result;

    while (!graph.empty()) {
        auto iter =
            std::find_if(std::begin(graph), std::end(graph),
                         [](const auto& pair) { return pair.second.empty(); });

        if (iter != std::end(graph)) {
            const char c = iter->first;
            result.push_back(c);
            graph.erase(iter);

            for (auto& [k, v] : graph) {
                v.erase(c);
            }
        } else {
            return {};
        }
    }

    return result;
}

void createGraph(std::vector<std::string> sortedWords,
                 std::unordered_map<char, std::unordered_set<char>>& result) {
    const auto innerCreateGraph = [&](int begin, int end) {
        std::vector<std::string> nextSortedWords;
        for (; begin != end; ++begin) {
            if (1 < sortedWords.size()) {
                nextSortedWords.emplace_back(sortedWords[begin], 1);
            }
        }

        createGraph(nextSortedWords, result);
    };

    if (!sortedWords.empty()) {
        int begin = 0;

        for (int end = begin + 1; end < sortedWords.size(); ++end) {
            if (sortedWords[begin][0] != sortedWords[end][0]) {
                result[sortedWords[begin][0]];
                result[sortedWords[end][0]].insert(sortedWords[begin][0]);
                innerCreateGraph(begin, end);
                begin = end;
            }
        }

        innerCreateGraph(begin, sortedWords.size());
    }
}

std::unordered_map<char, std::unordered_set<char>>
createGraph(std::vector<std::string> sortedWords) {
    std::unordered_map<char, std::unordered_set<char>> result;
    createGraph(sortedWords, result);

    return result;
}

std::vector<char> solve(std::vector<std::string> sortedWords) {
    return topologicalSort(createGraph(sortedWords));
}
} // namespace

TEST_CASE(__FILE__, "[geeksforgeeks]") {
    {
        const std::vector<char> expected{'b', 'd', 'a', 'c'};
        REQUIRE(expected == solve({"baa", "abcd", "abca", "cab", "cad"}));
    }

    {
        const std::vector<char> expected{'c', 'a', 'b'};
        REQUIRE(expected == solve({"caa", "aaa", "aab"}));
    }
}