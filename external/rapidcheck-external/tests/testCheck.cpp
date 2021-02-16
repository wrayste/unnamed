#include "catch2/catch.hpp" // for AssertionHandler, SourceLi...
#include "rapidcheck/rapidcheck.h"

TEST_CASE("check", "[rapidcheck-ext]") {
    REQUIRE(rc::check("string find", [](const std::string& needle,
                                        const std::string& haystack) {
        RC_ASSERT(haystack.find(needle) == haystack.find(needle));
    }));
}