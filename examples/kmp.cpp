#include "catch2/catch.hpp"

#include "rapidcheck.h"

std::vector<int> kmp_table(const std::string& w) {
    std::vector<int> t(w.size() + 1);

    int pos = 1;
    int cnd = 0;

    t[0] = -1;

    while (pos < w.size()) {
        if (w[pos] == w[cnd]) {
            t[pos] = t[cnd];
        } else {
            t[pos] = cnd;
            while (0 <= cnd && w[pos != w[cnd]]) {
                cnd = t[cnd];
            }
        }
        ++pos;
        ++cnd;
    }

    t[pos] = cnd;
    return t;
}

int kmp_search(const std::string& s, const std::string& w) {
    int j = 0;
    int k = 0;
    std::vector<int> t = kmp_table(w);

    if (w.empty()) {
        return 0;
    }

    while (j < s.size()) {
        if (w[k] == s[j]) {
            ++j;
            ++k;
            if (k == w.size()) {
                return j - k;
            }
        } else {
            k = t[k];
            if (k < 0) {
                ++j;
                ++k;
            }
        }
    }

    return -1;
}

TEST_CASE("kmp", "[examples]") {
    REQUIRE(rc::check("string find",
            [](const std::string& needle, const std::string& haystack) {
              RC_ASSERT(kmp_search(haystack, needle) == haystack.find(needle));
            }));
}
