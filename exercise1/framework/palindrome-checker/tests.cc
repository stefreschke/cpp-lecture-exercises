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

/*int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}*/
