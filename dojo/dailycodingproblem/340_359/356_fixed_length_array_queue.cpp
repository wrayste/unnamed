#include "catch2/catch.hpp" // for AssertionHandler, Sou...

#include <array>

namespace {
template <typename T, size_t S>
class FixedLengthArrayQueue {
  private:
    struct Node {
        std::array<T, S> block_;
        std::unique_ptr<Node> next_;
        size_t readPosition_ = 0;
        size_t writePosition_ = 0;
    };

    std::unique_ptr<Node> root_;

  public:
    FixedLengthArrayQueue()
        : root_(std::make_unique<Node>()) {
    }

    void enqueue(const T& t) {
        Node* n = root_.get();
        for (; n->next_; n = n->next_.get())
            ;

        if (S == n->writePosition_) {
            n->next_ = std::make_unique<Node>();
            n = n->next_.get();
        }

        n->block_[n->writePosition_++] = t;
    }

    T dequeue() {
        T result = root_->block_[root_->readPosition_++];

        if (S == root_->readPosition_) {
            root_ = root_->next_ ? std::move(root_->next_)
                                 : std::make_unique<Node>();
        }

        return result;
    }

    size_t get_size() const {
        size_t result = 0;
        for (const Node* n = root_.get(); n; n = n->next_.get()) {
            result += (n->writePosition_ - n->readPosition_);
        }
        return result;
    }
};
} // namespace

TEST_CASE(__FILE__, "[dailycodingproblem]") {
    FixedLengthArrayQueue<int, 5> flaq;
    for (int i = 0; i < 20; ++i) {
        REQUIRE(i == flaq.get_size());
        flaq.enqueue(i);
        REQUIRE(i + 1 == flaq.get_size());
    }

    for (int i = 0; i < 20; ++i) {
        REQUIRE(20 - i == flaq.get_size());
        REQUIRE(i == flaq.dequeue());
        REQUIRE(20 - i - 1 == flaq.get_size());
    }
}