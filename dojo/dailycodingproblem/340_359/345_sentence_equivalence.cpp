#include "catch2/catch.hpp" // for AssertionHandler, Sou...

#include <set>
#include <sstream>
#include <unordered_map>
#include <vector>

namespace {
bool isEquivalent(
    const std::string& s1, const std::string& s2,
    const std::unordered_map<std::string, std::set<std::string>>& synonyms) {

    const auto isSynonym = [&synonyms](const auto& w1, const auto& w2) {
        const auto i1 = synonyms.find(w1);
        const auto i2 = synonyms.find(w2);

        return (i1 != std::end(synonyms) && i1->second.contains(w2)) ||
               (i2 != std::end(synonyms) && i2->second.contains(w1));
    };

    std::string w1;
    std::string w2;

    std::istringstream iss1(s1);
    std::istringstream iss2(s2);

    while (std::getline(iss1, w1, ' ') && std::getline(iss2, w2, ' ')) {
        if (w1 != w2 && !isSynonym(w1, w2)) {
            return false;
        }
    }

    return iss1.eof() && iss2.eof();
}
} // namespace

TEST_CASE(__FILE__, "[dailycodingproblem]") {
    std::unordered_map<std::string, std::set<std::string>> synonyms;
    synonyms["big"].insert("large");
    synonyms["eat"].insert("consume");

    REQUIRE(isEquivalent("He wants to eat food.", "He wants to consume food.",
                         synonyms));
}