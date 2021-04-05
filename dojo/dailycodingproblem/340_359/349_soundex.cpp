#include "catch2/catch.hpp" // for AssertionHandler, Sou...

#include <string>

namespace {
char soundexCharEncoding(const char c) {
    switch (tolower(c)) {
    case 'b':
    case 'f':
    case 'p':
    case 'v':
        return '1';
    case 'c':
    case 'g':
    case 'j':
    case 'k':
    case 'q':
    case 's':
    case 'x':
    case 'z':
        return '2';
    case 'd':
    case 't':
        return '3';
    case 'l':
        return '4';
    case 'm':
    case 'n':
        return '5';
    case 'r':
        return '6';
    default:
        return '0';
    }
}

std::string soundexEncode(const std::string& s) {
    if (s.empty()) {
        return s;
    }

    std::string result(1, soundexCharEncoding(s[0]));
    for (size_t i = 1; i < s.size(); ++i) {
        if (const char n = soundexCharEncoding(s[i]);
            n != '0' && (n != result.back() || result.size() == 1 ||
                         (soundexCharEncoding(s[i - 1]) == 0 &&
                          s[i - 1] != 'h' && s[i - 1] != 'w'))) {
            result += n;
        }
    }

    for (; result.size() < 4; result += '0')
        ;

    result[0] = s[0];
    return result.substr(0, 4);
}
} // namespace

TEST_CASE(__FILE__, "[dailycodingproblem]") {
    REQUIRE("J250" == soundexEncode("Jackson"));
    REQUIRE("J250" == soundexEncode("Jaxen"));
}