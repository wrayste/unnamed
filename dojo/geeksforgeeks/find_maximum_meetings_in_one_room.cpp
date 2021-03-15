#include <algorithm> // for sort
#include <iterator>  // for begin, end
#include <vector>    // for vector, operator==, allocator

#include "catch2/catch.hpp" // for AssertionHandler, operator""_catch_sr

namespace {
std::vector<int> solve(const std::vector<int>& s, const std::vector<int>& f) {
    struct Meeting {
        int start;
        int finish;
        int position;

        Meeting(int _start, int _finish, int _position)
            : start(_start)
            , finish(_finish)
            , position(_position) {
        }
    };

    std::vector<Meeting> meetings;
    for (int i = 0; i < s.size(); ++i) {
        meetings.emplace_back(s[i], f[i], i);
    }

    std::sort(std::begin(meetings), std::end(meetings),
              [](const auto& lhs, const auto& rhs) {
                  return lhs.finish < rhs.finish;
              });

    std::vector<int> result;

    int currentTime = 0;
    for (const Meeting& meeting : meetings) {
        if (currentTime <= meeting.start) {
            result.push_back(meeting.position + 1);
            currentTime = meeting.finish;
        }
    }

    return result;
}
} // namespace

TEST_CASE(__FILE__, "[geeksforgeeks]") {
    {
        const std::vector<int> expected{1, 2, 4, 5};
        REQUIRE(expected == solve({1, 3, 0, 5, 8, 5}, {2, 4, 6, 7, 9, 9}));
    }

    {
        const std::vector<int> expected{6, 7, 1};
        REQUIRE(
            expected ==
            solve({75250, 50074, 43659, 8931, 11273, 27545, 50879, 77924},
                  {112960, 114515, 81825, 93424, 54316, 35533, 73383, 160252}));
    }
}