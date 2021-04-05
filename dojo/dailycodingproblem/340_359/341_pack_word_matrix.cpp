#include "catch2/catch.hpp" // for AssertionHandler, Sou...

#include <map>
#include <set>

namespace {
std::vector<std::set<std::pair<int, int>>>
consume_word(const std::pair<int, int>& start, const std::string& word, int pos,
             const std::vector<std::vector<char>>& matrix,
             std::set<std::pair<int, int>>& seen_cells) {
    if (pos == word.size()) {
        return {seen_cells};
    } else if (start.first < 0 || matrix.size() <= start.first ||
               start.second < 0 || matrix[start.first].size() < start.second ||
               seen_cells.contains(start) ||
               matrix[start.first][start.second] != word[pos]) {
        return {};
    } else {
        std::vector<std::set<std::pair<int, int>>> results;
        seen_cells.insert(start);

        {
            const auto temp = consume_word({start.first + 1, start.second},
                                           word, pos + 1, matrix, seen_cells);
            results.insert(std::end(results), std::begin(temp), std::end(temp));
        }

        {
            const auto temp = consume_word({start.first, start.second + 1},
                                           word, pos + 1, matrix, seen_cells);
            results.insert(std::end(results), std::begin(temp), std::end(temp));
        }

        {
            const auto temp = consume_word({start.first - 1, start.second},
                                           word, pos + 1, matrix, seen_cells);
            results.insert(std::end(results), std::begin(temp), std::end(temp));
        }

        {
            const auto temp = consume_word({start.first, start.second - 1},
                                           word, pos + 1, matrix, seen_cells);
            results.insert(std::end(results), std::begin(temp), std::end(temp));
        }

        seen_cells.erase(start);
        return results;
    }
}

bool overlap(const std::set<std::pair<int, int>>& lhs,
             const std::set<std::pair<int, int>>& rhs) {
    for (const auto& entry : lhs) {
        if (rhs.contains(entry)) {
            return true;
        }
    }
    for (const auto& entry : rhs) {
        if (lhs.contains(entry)) {
            return true;
        }
    }

    return false;
}

size_t
findMax(const std::vector<std::string> dictionary, const size_t position,
        std::map<std::string, std::vector<std::set<std::pair<int, int>>>>&
            word_positions,
        std::set<std::pair<int, int>>& all_seen, const size_t current_max) {

    size_t result = current_max;

    if (position != dictionary.size()) {
        result =
            std::max(result, findMax(dictionary, position + 1, word_positions,
                                     all_seen, current_max));

        for (const auto& positions : word_positions[dictionary[position]]) {
            if (!overlap(positions, all_seen)) {
                all_seen.insert(std::begin(positions), std::end(positions));
                result = std::max(result, findMax(dictionary, position + 1,
                                                  word_positions, all_seen,
                                                  current_max + 1));

                for (const auto& position : positions) {
                    all_seen.erase(position);
                }
            }
        }
    }

    return result;
}

size_t solve(const std::vector<std::vector<char>>& matrix,
             const std::vector<std::string> dictionary) {

    std::map<std::string, std::vector<std::set<std::pair<int, int>>>>
        word_positions;

    for (const auto& word : dictionary) {
        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = 0; j < matrix.size(); ++j) {
                std::set<std::pair<int, int>> seen_cells;
                const auto temp =
                    consume_word({i, j}, word, 0, matrix, seen_cells);
                if (!temp.empty()) {
                    word_positions[word].insert(std::end(word_positions[word]),
                                                std::begin(temp),
                                                std::end(temp));
                }
            }
        }
    }

    std::set<std::pair<int, int>> all_seen;
    return findMax(dictionary, 0, word_positions, all_seen, 0);
}
} // namespace

TEST_CASE(__FILE__, "[dailycodingproblem]") {
    const std::vector<std::vector<char>> matrix{{'e', 'a', 'n'}, //
                                                {'t', 't', 'i'}, //
                                                {'a', 'r', 'a'}};
    const std::vector<std::string> dictionary{"eat", "rain", "in", "rat"};

    REQUIRE(3 == solve(matrix, dictionary));
}