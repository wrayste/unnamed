#include <algorithm> // for rotate, sort
#include <cstdlib>   // for size_t
#include <iterator>  // for begin, end

#include "catch2/catch.hpp"        // for AssertionHandler, Sou...
#include "rapidcheck/rapidcheck.h" // for vector, check, CaseRe...

int searchInRotatedSortedArrayOptimised(const size_t needle,
                                        const std::vector<size_t>& haystack,
                                        const int first, const int last) {
    if (last < first) {
        return -1;
    }
    if (first == last) {
        return haystack[first] == needle ? first : -1;
    }

    if (last == first + 1) {
        if (haystack[first] == needle) {
            return first;
        } else if (haystack[last] == needle) {
            return last;
        } else {
            return -1;
        }
    }

    const int middle = first + ((last - first) / 2);
    if (haystack[middle] == needle) {
        return middle;
    }

    if ((needle < haystack[middle] && needle < haystack[last]) ||
        (needle > haystack[middle] && needle < haystack[last])) {
        return searchInRotatedSortedArrayOptimised(needle, haystack, middle + 1,
                                                   last);
    } else {
        return searchInRotatedSortedArrayOptimised(needle, haystack, first,
                                                   middle - 1);
    }
}

int searchInRotatedSortedArrayOptimised(const size_t needle,
                                        const std::vector<size_t>& haystack) {
    return searchInRotatedSortedArrayOptimised(needle, haystack, 0,
                                               haystack.size() - 1);
}

int searchInRotatedSortedArrayNaive(const size_t needle,
                                    const std::vector<size_t>& haystack) {
    for (int i = 0; i < haystack.size(); ++i) {
        if (haystack[i] == needle) {
            return i;
        }
    }

    return -1;
}

TEST_CASE(__FILE__, "[leetcode]") {
    std::vector<size_t> haystack{4, 5, 6, 7, 0, 1, 2};
    // REQUIRE(4 == searchInRotatedSortedArrayOptimised(0, haystack));

    REQUIRE(rc::check(__FILE__, [](const size_t needle,
                                   std::vector<size_t> haystack,
                                   const size_t rotation) {
        std::sort(std::begin(haystack), std::end(haystack));

        if (!haystack.empty()) {
            std::rotate(std::begin(haystack),
                        std::begin(haystack) + (rotation % haystack.size()),
                        std::end(haystack));
        }

        RC_ASSERT(searchInRotatedSortedArrayNaive(needle, haystack) ==
                  searchInRotatedSortedArrayOptimised(needle, haystack));
    }));
}