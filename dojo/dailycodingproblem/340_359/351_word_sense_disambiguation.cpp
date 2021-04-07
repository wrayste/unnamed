#include "catch2/catch.hpp" // for AssertionHandler, Sou...

#include <map>
#include <set>
#include <sstream>

namespace {
std::set<std::string> normalise(const std::string& sentence,
                                const std::set<std::string>& stopWords) {
    std::istringstream iss(sentence);
    std::vector<std::string> words;

    std::transform(
        std::istream_iterator<std::string>(iss),
        std::istream_iterator<std::string>(), std::back_inserter(words),
        [&](std::string word) {
            word.erase(
                std::remove_if(std::begin(word), std::end(word),
                               [](const char c) { return !std::isalpha(c); }),
                word.end());
            std::transform(std::begin(word), std::end(word), std::begin(word),
                           [](const char c) { return std::tolower(c); });
            return word;
        });

    words.erase(std::remove_if(std::begin(words), std::end(words),
                               [&stopWords](const std::string& word) {
                                   return stopWords.contains(word);
                               }),
                std::end(words));

    std::set<std::string> result;
    for (const auto& word : words) {
        result.insert(word);
    }
    return result;
}

std::map<std::string, std::string>
disambiguate(const std::string& sentence,
             const std::map<std::string, std::set<std::string>>& meanings,
             const std::set<std::string>& stopWords) {

    std::map<std::string, std::string> trueSenses;
    const auto sentenceWords = normalise(sentence, stopWords);

    for (const auto& [word, senses] : meanings) {
        size_t maxOverlaps = 0;

        for (const auto& sense : senses) {
            const auto definition = normalise(sense, stopWords);

            std::vector<std::string> overlaps;
            std::set_intersection(std::begin(definition), //
                                  std::end(definition),   //
                                  std::begin(sentenceWords),
                                  std::end(sentenceWords),
                                  std::back_inserter(overlaps));

            if (overlaps.size() > maxOverlaps) {
                maxOverlaps = overlaps.size();
                trueSenses[word] = sense;
            }
        }
    }

    return trueSenses;
}
} // namespace

TEST_CASE(__FILE__, "[dailycodingproblem]") {
    const std::string sentence =
        "I drove my car past the fork in the road to put some "
        "money in the bank.";

    std::map<std::string, std::set<std::string>> meanings;
    meanings["bank"].insert("land beside a river or lake");
    meanings["bank"].insert("place to deposit money");
    meanings["fork"].insert("eating utensil");
    meanings["fork"].insert("bend in the road");

    std::set<std::string> stopWords;
    stopWords.insert("a");
    stopWords.insert("in");
    stopWords.insert("or");
    stopWords.insert("the");
    stopWords.insert("to");

    std::map<std::string, std::string> trueSenses;
    trueSenses["bank"] = "place to deposit money";
    trueSenses["fork"] = "bend in the road";

    REQUIRE(trueSenses == disambiguate(sentence, meanings, stopWords));
}