#include <iosfwd>   // for string
#include <iterator> // for end
#include <map>      // for map, operator!=, __map_const_iterator
#include <string>   // for basic_string, operator==, allocator
#include <utility>  // for pair
#include <vector>   // for vector, operator==, __vector_base<>::val...

#include "catch2/catch.hpp" // for AssertionHandler, SourceLineInfo, StringRef

namespace {
struct TrieNode {
    std::map<char, TrieNode> children;
    bool isWord = false;
};

void solve(const std::vector<int>& input, const TrieNode& n, int i,
           std::string& temp, std::vector<std::string>& output) {
    static const std::vector<std::string> digitsToChars{
        "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

    if (i < input.size()) {
        for (const char c : digitsToChars[input[i]]) {
            if (auto iter = n.children.find(c); iter != std::end(n.children)) {
                temp.push_back(c);
                solve(input, iter->second, i + 1, temp, output);
                temp.pop_back();
            }
        }
    } else if (n.isWord) {
        output.push_back(temp);
    }
}

TrieNode makeTrie(const std::vector<std::string>& words) {
    TrieNode root;

    for (const auto& word : words) {
        TrieNode* n = &root;
        for (const auto c : word) {
            n = &(n->children[c]);
        }
        n->isWord = true;
    }

    return root;
}

std::vector<std::string> solve(const std::vector<int>& input,
                               const std::vector<std::string>& words) {
    TrieNode root = makeTrie(words);

    std::string temp;
    std::vector<std::string> output;
    solve(input, root, 0, temp, output);
    return output;
}
} // namespace

TEST_CASE(__FILE__, "[geeksforgeeks]") {
    const std::vector<std::string> expected{"and", "cod"};
    REQUIRE(expected == solve({2, 6, 3}, {"and", "cod", "the"}));
}