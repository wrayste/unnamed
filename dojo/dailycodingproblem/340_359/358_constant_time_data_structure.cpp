#include "catch2/catch.hpp" // for AssertionHandler, Sou...

#include <unordered_map>
#include <unordered_set>

namespace {
template <typename T>
class MinMaxSet {
  private:
    struct Bucket {
        std::unordered_set<T> keys_;
        Bucket* prev_ = this;
        Bucket* next_ = this;
        const size_t count_;

        Bucket(const size_t count)
            : count_(count) {
        }
    };

    Bucket sentinel_;
    std::unordered_map<T, size_t> keyToCount_;
    std::unordered_map<size_t, Bucket*> countToBucket_;

  public:
    MinMaxSet()
        : sentinel_(0) {
    }

    void plus(const T& t) {
        if (const auto i = keyToCount_.find(t); i != std::end(keyToCount_)) {
            Bucket* currentBucket = countToBucket_[i->second++];
            getNext(currentBucket)->keys_.insert(t);
            remove(t, currentBucket);
        } else {
            keyToCount_[t] = 1;
            getNext(&sentinel_)->keys_.insert(t);
        }
    }

    void minus(const T& t) {
        if (const auto i = keyToCount_.find(t); i != std::end(keyToCount_)) {
            Bucket* currentBucket = countToBucket_[i->second--];

            if (0 < i->second) {
                getPrev(currentBucket)->keys_.insert(t);
            } else {
                keyToCount_.erase(t);
            }

            remove(t, currentBucket);
        }
    }

    bool empty() const {
        return &sentinel_ == sentinel_.next_;
    }

    const T& get_min() const {
        return *std::begin(sentinel_.next_->keys_);
    }

    const T& get_max() const {
        return *std::begin(sentinel_.prev_->keys_);
    }

  private:
    Bucket* getNext(Bucket* currentBucket) {
        const size_t nextCount = currentBucket->count_ + 1;
        if (nextCount != currentBucket->next_->count_) {
            Bucket* nextBucket = new Bucket(nextCount);
            link(currentBucket, nextBucket, currentBucket->next_);
            countToBucket_[nextCount] = nextBucket;
            return nextBucket;
        } else {
            return currentBucket->next_;
        }
    }

    Bucket* getPrev(Bucket* currentBucket) {
        const size_t prevCount = currentBucket->count_ - 1;
        if (prevCount != currentBucket->prev_->count_) {
            Bucket* prevBucket = new Bucket(prevCount);
            link(currentBucket->prev_, prevBucket, currentBucket);
            countToBucket_[prevCount] = prevBucket;
            return prevBucket;
        } else {
            return currentBucket->prev_;
        }
    }

    void link(Bucket* prev, Bucket* next) {
        prev->next_ = next;
        next->prev_ = prev;
    }

    void link(Bucket* previous, Bucket* current, Bucket* next) {
        link(previous, current);
        link(current, next);
    }

    void remove(const T& key, Bucket* bucket) {
        bucket->keys_.erase(key);
        if (bucket->keys_.empty()) {
            bucket->prev_->next_ = bucket->next_;
            bucket->next_->prev_ = bucket->prev_;
            countToBucket_.erase(bucket->count_);
            delete bucket;
        }
    }
};
} // namespace

TEST_CASE(__FILE__, "[dailycodingproblem]") {
    MinMaxSet<int> minMaxSet;
    REQUIRE(minMaxSet.empty());

    minMaxSet.plus(5);
    REQUIRE(5 == minMaxSet.get_min());
    REQUIRE(5 == minMaxSet.get_max());

    minMaxSet.plus(10);
    REQUIRE(10 == minMaxSet.get_min());
    REQUIRE(10 == minMaxSet.get_max());

    minMaxSet.plus(5);
    REQUIRE(10 == minMaxSet.get_min());
    REQUIRE(5 == minMaxSet.get_max());

    minMaxSet.minus(10);
    REQUIRE(5 == minMaxSet.get_min());
    REQUIRE(5 == minMaxSet.get_max());

    minMaxSet.minus(5);
    REQUIRE(5 == minMaxSet.get_min());
    REQUIRE(5 == minMaxSet.get_max());

    minMaxSet.minus(5);
    REQUIRE(minMaxSet.empty());
}