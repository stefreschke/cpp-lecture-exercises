#include <gtest/gtest.h>
#include "palindrome-checker.h"

TEST(PalindromeChecker, RecognizesEvenPalindromIsPalindrome) {
    std::string myString ("asddsa");
    auto result = isPalindrome(myString);
    EXPECT_TRUE(result);
}

TEST(PalindromeChecker, RecognizesUnevenPalindromIsPalindrome) {
    std::string myString ("asdfdsa");
    auto result = isPalindrome(myString);
    EXPECT_TRUE(result);
}

TEST(PalindromeChecker, RecognizesNonPalindromLineIsNoPalindrome) {
    std::string myString ("asdfqwer");
    auto result = isPalindrome(myString);
    EXPECT_FALSE(result);
}

TEST(PalindromeSorter, SortsUnevenPalindromeTooTheFront) {
    std::vector<std::string> list;
    list.push_back("asdf");
    list.push_back("qwq");
    auto result = sortByPalindrome(list);
    std::vector<std::string> expected;
    expected.push_back("qwq");
    expected.push_back("asdf");
    EXPECT_EQ(expected.size(), result.size());
}

TEST(PalindromeSorter, SortsTwoPalindromesTooTheFront) {
    std::vector<std::string> list;
    list.push_back("asdf");
    list.push_back("otto");
    list.push_back("qwer");
    list.push_back("qwq");
    auto result = sortByPalindrome(list);
    std::vector<std::string> expected;
    expected.push_back("qwq");
    expected.push_back("otto");
    expected.push_back("asdf");
    expected.push_back("qwer");
    EXPECT_EQ(expected.size(), result.size());
    for (int i=0; i<4; i++) {
        EXPECT_EQ(expected[i], result[i]);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
