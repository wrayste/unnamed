#include "catch2/catch.hpp" // for AssertionHandler, Sou...

#include <memory>
#include <queue>
#include <vector>

namespace {
std::pair<int, int> findBlank(const std::vector<std::vector<int>>& current) {
    for (int i = 0; i < current.size(); ++i) {
        for (int j = 0; j < current[i].size(); ++j) {
            if (current[i][j] == 0) {
                return {i, j};
            }
        }
    }

    return {-1, -1};
}

int calculateCost(const std::vector<std::vector<int>>& current,
                  const std::vector<std::vector<int>>& target) {
    int count = 0;

    for (int i = 0; i < current.size(); ++i) {
        for (int j = 0; j < current[i].size(); ++j) {
            if (current[i][j] != target[i][j]) {
                count++;
            }
        }
    }

    return count;
}

struct Node {
    std::vector<std::vector<int>> current_;
    int blankX_;
    int blankY_;
    int level_;
    int cost_;

    Node(const std::vector<std::vector<int>>& current, int blankX, int blankY,
         const std::vector<std::vector<int>>& target)
        : current_(current)
        , blankX_(blankX)
        , blankY_(blankY)
        , level_(0)
        , cost_(calculateCost(current, target)) {
    }

    Node(const Node& parent, int xMod, int yMod,
         const std::vector<std::vector<int>>& target)
        : current_(parent.current_)
        , blankX_(parent.blankX_ + xMod)
        , blankY_(parent.blankY_ + yMod)
        , level_(parent.level_ + 1) {
        std::swap(current_[parent.blankX_][parent.blankY_],
                  current_[blankX_][blankY_]);
        cost_ = calculateCost(current_, target);
    }

    bool isSafe(int xMod, int yMod) const {
        const int newBlankX = blankX_ + xMod;
        const int newBlankY = blankY_ + yMod;
        return 0 <= newBlankX && newBlankX < current_.size() &&
               0 <= newBlankY && newBlankY < current_[newBlankX].size();
    }

    bool operator<(const Node& rhs) const {
        return (this->cost_ + this->level_) > (rhs.cost_ + rhs.level_);
    }
};

int solve(const std::vector<std::vector<int>>& initial) {
    const auto [blankX, blankY] = findBlank(initial);
    const std::vector<std::vector<int>> target = {
        {1, 2, 3}, {4, 5, 6}, {7, 8, 0}};

    std::priority_queue<Node> queue;
    queue.emplace(initial, blankX, blankY, target);

    while (!queue.empty()) {
        const Node current = queue.top();
        queue.pop();

        if (current.cost_ == 0) {
            return current.level_;
        } else {
            static const std::vector<std::pair<int, int>> modifiers{
                {1, 0}, {0, -1}, {-1, 0}, {0, 1}};
            for (const auto& [xMod, yMod] : modifiers) {
                if (current.isSafe(xMod, yMod)) {
                    queue.emplace(current, xMod, yMod, target);
                }
            }
        }
    }

    return std::numeric_limits<int>::max();
}
} // namespace

TEST_CASE(__FILE__, "[dailycodingproblem]") {
    const std::vector<std::vector<int>> initial = {
        {1, 2, 3}, {5, 6, 0}, {7, 8, 4}};
    REQUIRE(13 == solve(initial));
}