
#include "catch2/catch.hpp"
#include "rapidcheck/rapidcheck.h"

std::vector<int> kmp_table(const std::string& needle) {
    std::vector<int> table(needle.size() + 1);
    table[0] = -1;

    int cnd = 0;

    for (int pos = 1; pos < needle.size(); ++pos, ++cnd) {
        if (needle[pos] == needle[cnd]) {
            table[pos] = table[cnd];
        } else {
            for (table[pos] = cnd; 0 <= cnd && needle[pos] != needle[cnd];
                 cnd = table[cnd])
                ;
        }
    }

    table[needle.size()] = cnd;
    return table;
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
    REQUIRE(rc::check("string find", [](const std::string& needle,
                                        const std::string& haystack) {
        RC_ASSERT(kmp_search(haystack, needle) == haystack.find(needle));
    }));
}
