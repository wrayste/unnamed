#include "catch2/catch.hpp" // for AssertionHandler, Sou...

#include <memory>
#include <string>
#include <vector>

namespace {
struct Node {
    char value_;
    std::unique_ptr<Node> left_;
    std::unique_ptr<Node> center_;
    std::unique_ptr<Node> right_;

    Node(const char value)
        : value_(value) {
    }

    Node(const std::string& word, size_t begin)
        : value_(word[begin]) {
        if (begin + 1 < word.size()) {
            center_ = std::make_unique<Node>(word, begin + 1);
        }
    }

    void insert(const std::string& word, size_t begin) {
        if (begin == word.size()) {
            return;
        } else if (value_ == word[begin]) {
            center_->insert(word, begin + 1);
        } else if (word[begin] < value_) {
            if (!left_) {
                left_ = std::make_unique<Node>(word, begin);
            } else if (left_->value_ < word[begin]) {
                auto newLeft = std::make_unique<Node>(word, begin);
                newLeft->left_.swap(left_);
                left_.swap(newLeft);
            } else {
                left_->insert(word, begin);
            }
        } else {
            if (!right_) {
                right_ = std::make_unique<Node>(word, begin);
            } else if (word[begin] < right_->value_) {
                auto newRight = std::make_unique<Node>(word, begin);
                newRight->right_.swap(right_);
                right_.swap(newRight);
            } else {
                right_->insert(word, begin);
            }
        }
    }

    bool contains(const std::string& word, size_t begin) const {
        if (value_ == word[begin]) {
            return (begin + 1 == word.size()) ||
                   (center_ && center_->contains(word, begin + 1));
        } else if (word[begin] < value_) {
            return left_ && word[begin] <= left_->value_ &&
                   left_->contains(word, begin);
        } else {
            return right_ && right_->value_ <= word[begin] &&
                   right_->contains(word, begin);
        }
    }

    void toVector(std::string& w, std::vector<std::string>& o) {
        if (left_) {
            left_->toVector(w, o);
        }

        w.push_back(value_);
        if (center_) {
            center_->toVector(w, o);
        } else {
            o.push_back(w);
        }
        w.pop_back();

        if (right_) {
            right_->toVector(w, o);
        }
    }
};

struct TernaryTree {
    std::unique_ptr<Node> root_;

    void insert(const std::string& word) {
        if (!root_) {
            root_ = std::make_unique<Node>(word, 0);
        } else {
            root_->insert(word, 0);
        }
    }

    bool contains(const std::string& word) const {
        return root_ ? root_->contains(word, 0) : false;
    }

    void toVector(std::vector<std::string>& o) const {
        if (root_) {
            std::string w;
            root_->toVector(w, o);
        }
    }
};
} // namespace

TEST_CASE(__FILE__, "[dailycodingproblem]") {
    std::vector<std::string> inputWords{"code", "cob", "be", "ax", "war", "we"};

    TernaryTree tt;
    for (const auto& word : inputWords) {
        tt.insert(word);
    }

    for (const auto& word : inputWords) {
        REQUIRE(tt.contains(word));
    }

    REQUIRE(!tt.contains("hello"));

    std::vector<std::string> outputWords;
    tt.toVector(outputWords);

    std::sort(std::begin(inputWords), std::end(inputWords));
    REQUIRE(inputWords == outputWords);
}