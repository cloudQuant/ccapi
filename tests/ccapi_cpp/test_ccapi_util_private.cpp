#include <algorithm>
#include <regex>
#include <string>
#include <vector>

#include "../../include/ccapi_cpp/ccapi_util_private.h"
#include "gtest/gtest.h"

//// 测试第一个 split 函数（基于 char 作为分隔符）
TEST(SplitCharTest, EmptyString) {
    std::string input;
    char sep = ',';
    std::vector<std::string> expected = {""};
    EXPECT_EQ(ccapi::UtilString::split(input, sep), expected);
}

TEST(SplitCharTest, NoSeparator) {
    std::string input = "test";
    char sep = ',';
    std::vector<std::string> expected = {"test"};
    EXPECT_EQ(ccapi::UtilString::split(input, sep), expected);
}

TEST(SplitCharTest, SingleSeparator) {
    std::string input = "test1,test2";
    char sep = ',';
    std::vector<std::string> expected = {"test1", "test2"};
    EXPECT_EQ(ccapi::UtilString::split(input, sep), expected);
}

TEST(SplitCharTest, MultipleSeparators) {
    std::string input = "a,b,c,d";
    char sep = ',';
    std::vector<std::string> expected = {"a", "b", "c", "d"};
    EXPECT_EQ(ccapi::UtilString::split(input, sep), expected);
}

TEST(SplitCharTest, LeadingAndTrailingSeparators) {
    std::string input = ",test1,test2,";
    char sep = ',';
    std::vector<std::string> expected = {"", "test1", "test2", ""};
    EXPECT_EQ(ccapi::UtilString::split(input, sep), expected);
}

// 测试第二个 split 函数（基于字符串作为分隔符）
TEST(SplitStringTest, EmptyString) {
    std::string input;
    std::string delimiter = ",";
    std::vector<std::string> expected = {""};
    EXPECT_EQ(ccapi::UtilString::split(input, delimiter), expected);
}

TEST(SplitStringTest, NoDelimiter) {
    std::string input = "test";
    std::string delimiter = ",";
    std::vector<std::string> expected = {"test"};
    EXPECT_EQ(ccapi::UtilString::split(input, delimiter), expected);
}

TEST(SplitStringTest, SingleDelimiter) {
    std::string input = "test1,test2";
    std::string delimiter = ",";
    std::vector<std::string> expected = {"test1", "test2"};
    EXPECT_EQ(ccapi::UtilString::split(input, delimiter), expected);
}

TEST(SplitStringTest, MultipleDelimiters) {
    std::string input = "a,b,c,d";
    std::string delimiter = ",";
    std::vector<std::string> expected = {"a", "b", "c", "d"};
    EXPECT_EQ(ccapi::UtilString::split(input, delimiter), expected);
}

TEST(SplitStringTest, LeadingAndTrailingDelimiters) {
    std::string input = ",test1,test2,";
    std::string delimiter = ",";
    std::vector<std::string> expected = {"", "test1", "test2", ""};
    EXPECT_EQ(ccapi::UtilString::split(input, delimiter), expected);
}

TEST(SplitStringTest, CustomDelimiter) {
    std::string input = "test1##test2##test3";
    std::string delimiter = "##";
    std::vector<std::string> expected = {"test1", "test2", "test3"};
    EXPECT_EQ(ccapi::UtilString::split(input, delimiter), expected);
}

// test splitToSet function
TEST(SplitToSetTest, EmptyString) {
    std::string input1;
    std::string delimiter = ",";
    std::set<std::string> expected = {""};
    std::cout << "input = " << input1 << std::endl;
    EXPECT_EQ(ccapi::UtilString::splitToSet(input1, delimiter), expected);
}

TEST(SplitToSetTest, NoDelimiter) {
    std::string input = "test";
    std::string delimiter = ",";
    std::set<std::string> expected = {"test"};
    EXPECT_EQ(ccapi::UtilString::splitToSet(input, delimiter), expected);
}

TEST(SplitToSetTest, SingleDelimiter) {
    std::string input = "test1,test2";
    std::string delimiter = ",";
    std::set<std::string> expected = {"test1", "test2"};
    EXPECT_EQ(ccapi::UtilString::splitToSet(input, delimiter), expected);
}

TEST(SplitToSetTest, MultipleDelimiters) {
    std::string input = "a,b,c,d";
    std::string delimiter = ",";
    std::set<std::string> expected = {"a", "b", "c", "d"};
    EXPECT_EQ(ccapi::UtilString::splitToSet(input, delimiter), expected);
}

TEST(SplitToSetTest, LeadingAndTrailingDelimiters) {
    std::string input = ",test1,test2,";
    std::string delimiter = ",";
    std::set<std::string> expected = {"", "test1", "test2"};
    EXPECT_EQ(ccapi::UtilString::splitToSet(input, delimiter), expected);
}

TEST(SplitToSetTest, DuplicateValues) {
    std::string input = "test1,test2,test1,test3";
    std::string delimiter = ",";
    std::set<std::string> expected = {"test1", "test2", "test3"};
    EXPECT_EQ(ccapi::UtilString::splitToSet(input, delimiter), expected);
}

TEST(SplitToSetTest, CustomDelimiter) {
    std::string input = "test1##test2##test1##test3";
    std::string delimiter = "##";
    std::set<std::string> expected = {"test1", "test2", "test3"};
    EXPECT_EQ(ccapi::UtilString::splitToSet(input, delimiter), expected);
}

TEST(SplitToSetTest, EmptyDelimiter) {
    std::string input = "test1 test2 test3";
    std::string delimiter = " ";
    std::set<std::string> expected = {"test1", "test2", "test3"};  // Or handle this case differently, depending on your function's design
    EXPECT_EQ(ccapi::UtilString::splitToSet(input, delimiter), expected);
}

// test function join
TEST(JoinTest, EmptyVector) {
    std::vector<std::string> input = {};
    std::string delimiter = ",";
    std::string expected;
    EXPECT_EQ(ccapi::UtilString::join(input, delimiter), expected);
}

TEST(JoinTest, SingleElement) {
    std::vector<std::string> input = {"test"};
    std::string delimiter = ",";
    std::string expected = "test";
    EXPECT_EQ(ccapi::UtilString::join(input, delimiter), expected);
}

TEST(JoinTest, MultipleElements) {
    std::vector<std::string> input = {"test1", "test2", "test3"};
    std::string delimiter = ",";
    std::string expected = "test1,test2,test3";
    EXPECT_EQ(ccapi::UtilString::join(input, delimiter), expected);
}

TEST(JoinTest, DifferentDelimiter) {
    std::vector<std::string> input = {"a", "b", "c"};
    std::string delimiter = "|";
    std::string expected = "a|b|c";
    EXPECT_EQ(ccapi::UtilString::join(input, delimiter), expected);
}

TEST(JoinTest, EmptyStrings) {
    std::vector<std::string> input = {"", "", ""};
    std::string delimiter = ",";
    std::string expected = ",,";
    EXPECT_EQ(ccapi::UtilString::join(input, delimiter), expected);
}

TEST(JoinTest, EmptyDelimiter) {
    std::vector<std::string> input = {"test1", "test2", "test3"};
    std::string delimiter;
    std::string expected = "test1test2test3";
    EXPECT_EQ(ccapi::UtilString::join(input, delimiter), expected);
}

TEST(JoinTest, MixedStrings) {
    std::vector<std::string> input = {"test1", "", "test3"};
    std::string delimiter = ",";
    std::string expected = "test1,,test3";
    EXPECT_EQ(ccapi::UtilString::join(input, delimiter), expected);
}

TEST(JoinTest, LongDelimiter) {
    std::vector<std::string> input = {"test1", "test2", "test3"};
    std::string delimiter = "+++";
    std::string expected = "test1+++test2+++test3";
    EXPECT_EQ(ccapi::UtilString::join(input, delimiter), expected);
}

// test function toUpper
TEST(StringTransformTest, ToUpper_EmptyString) {
    std::string input;
    std::string expected;
    EXPECT_EQ(ccapi::UtilString::toUpper(input), expected);
}

TEST(StringTransformTest, ToUpper_AllLowercase) {
    std::string input = "hello";
    std::string expected = "HELLO";
    EXPECT_EQ(ccapi::UtilString::toUpper(input), expected);
}

TEST(StringTransformTest, ToUpper_MixedCase) {
    std::string input = "HeLLo";
    std::string expected = "HELLO";
    EXPECT_EQ(ccapi::UtilString::toUpper(input), expected);
}

TEST(StringTransformTest, ToUpper_NumericAndSpecialChars) {
    std::string input = "1234!@#$";
    std::string expected = "1234!@#$";
    EXPECT_EQ(ccapi::UtilString::toUpper(input), expected);
}

TEST(StringTransformTest, ToUpper_AlreadyUppercase) {
    std::string input = "HELLO";
    std::string expected = "HELLO";
    EXPECT_EQ(ccapi::UtilString::toUpper(input), expected);
}

// test function toLower
TEST(StringTransformTest, ToLower_EmptyString) {
    std::string input;
    std::string expected;
    EXPECT_EQ(ccapi::UtilString::toLower(input), expected);
}

TEST(StringTransformTest, ToLower_AllUppercase) {
    std::string input = "HELLO";
    std::string expected = "hello";
    EXPECT_EQ(ccapi::UtilString::toLower(input), expected);
}

TEST(StringTransformTest, ToLower_MixedCase) {
    std::string input = "HeLLo";
    std::string expected = "hello";
    EXPECT_EQ(ccapi::UtilString::toLower(input), expected);
}

TEST(StringTransformTest, ToLower_NumericAndSpecialChars) {
    std::string input = "1234!@#$";
    std::string expected = "1234!@#$";
    EXPECT_EQ(ccapi::UtilString::toLower(input), expected);
}

TEST(StringTransformTest, ToLower_AlreadyLowercase) {
    std::string input = "hello";
    std::string expected = "hello";
    EXPECT_EQ(ccapi::UtilString::toLower(input), expected);
}

// test function ltrim
TEST(LtrimTest, Ltrim_EmptyString_WithChars) {
    std::string input;
    std::string expected;
    EXPECT_EQ(ccapi::UtilString::ltrim(input), expected);
}

TEST(LtrimTest, Ltrim_NoLeadingWhitespace_WithChars) {
    std::string input = "hello";
    std::string expected = "hello";
    EXPECT_EQ(ccapi::UtilString::ltrim(input), expected);
}

TEST(LtrimTest, Ltrim_LeadingSpaces_WithChars) {
    std::string input = "   hello";
    std::string expected = "hello";
    EXPECT_EQ(ccapi::UtilString::ltrim(input), expected);
}

TEST(LtrimTest, Ltrim_LeadingTabsAndSpaces_WithChars) {
    std::string input = "\t   hello";
    std::string expected = "hello";
    EXPECT_EQ(ccapi::UtilString::ltrim(input), expected);
}

TEST(LtrimTest, Ltrim_OnlyWhitespace_WithChars) {
    std::string input = "\t \n";
    std::string expected;
    EXPECT_EQ(ccapi::UtilString::ltrim(input), expected);
}

TEST(LtrimTest, Ltrim_CustomCharSet) {
    std::string input = "!!!hello";
    std::string expected = "hello";
    EXPECT_EQ(ccapi::UtilString::ltrim(input, "!"), expected);
}

TEST(LtrimTest, Ltrim_MultipleCustomChars) {
    std::string input = "!@!@hello";
    std::string expected = "hello";
    EXPECT_EQ(ccapi::UtilString::ltrim(input, "!@"), expected);
}

// test function ltrim
TEST(LtrimTest, Ltrim_EmptyString_WithSingleChar) {
    std::string input;
    std::string expected;
    EXPECT_EQ(ccapi::UtilString::ltrim(input, '!'), expected);
}

TEST(LtrimTest, Ltrim_NoLeadingCharacter_WithSingleChar) {
    std::string input = "hello";
    std::string expected = "hello";
    EXPECT_EQ(ccapi::UtilString::ltrim(input, '!'), expected);
}

TEST(LtrimTest, Ltrim_LeadingCharacter_WithSingleChar) {
    std::string input = "!!hello";
    std::string expected = "hello";
    EXPECT_EQ(ccapi::UtilString::ltrim(input, '!'), expected);
}

TEST(LtrimTest, Ltrim_LeadingCharacterAndSpaces_WithSingleChar) {
    std::string input = "!   hello";
    std::string expected = "   hello";
    EXPECT_EQ(ccapi::UtilString::ltrim(input, '!'), expected);
}

TEST(LtrimTest, Ltrim_AllTargetChars_WithSingleChar) {
    std::string input = "!!!!!";
    std::string expected;
    EXPECT_EQ(ccapi::UtilString::ltrim(input, '!'), expected);
}

// test function ltrimInPlace
TEST(LtrimInPlaceTest, LtrimInPlace_EmptyString_WithChars) {
    std::string input;
    std::string expected;
    ccapi::UtilString::ltrimInPlace(input);
    EXPECT_EQ(input, expected);
}

TEST(LtrimInPlaceTest, LtrimInPlace_NoLeadingWhitespace_WithChars) {
    std::string input = "hello";
    std::string expected = "hello";
    ccapi::UtilString::ltrimInPlace(input);
    EXPECT_EQ(input, expected);
}

TEST(LtrimInPlaceTest, LtrimInPlace_LeadingSpaces_WithChars) {
    std::string input = "   hello";
    std::string expected = "hello";
    ccapi::UtilString::ltrimInPlace(input);
    EXPECT_EQ(input, expected);
}

TEST(LtrimInPlaceTest, LtrimInPlace_LeadingTabsAndSpaces_WithChars) {
    std::string input = "\t   hello";
    std::string expected = "hello";
    ccapi::UtilString::ltrimInPlace(input);
    EXPECT_EQ(input, expected);
}

TEST(LtrimInPlaceTest, LtrimInPlace_OnlyWhitespace_WithChars) {
    std::string input = "\t \n";
    std::string expected;
    ccapi::UtilString::ltrimInPlace(input);
    EXPECT_EQ(input, expected);
}

TEST(LtrimInPlaceTest, LtrimInPlace_CustomCharSet) {
    std::string input = "!!!hello";
    std::string expected = "hello";
    ccapi::UtilString::ltrimInPlace(input, "!");
    EXPECT_EQ(input, expected);
}

TEST(LtrimInPlaceTest, LtrimInPlace_MultipleCustomChars) {
    std::string input = "!@!@hello";
    std::string expected = "hello";
    ccapi::UtilString::ltrimInPlace(input, "!@");
    EXPECT_EQ(input, expected);
}

// test function ltrimInPlace
TEST(LtrimInPlaceTest, LtrimInPlace_EmptyString_WithSingleChar) {
    std::string input;
    std::string expected;
    ccapi::UtilString::ltrimInPlace(input, '!');
    EXPECT_EQ(input, expected);
}

TEST(LtrimInPlaceTest, LtrimInPlace_NoLeadingCharacter_WithSingleChar) {
    std::string input = "hello";
    std::string expected = "hello";
    ccapi::UtilString::ltrimInPlace(input, '!');
    EXPECT_EQ(input, expected);
}

TEST(LtrimInPlaceTest, LtrimInPlace_LeadingCharacter_WithSingleChar) {
    std::string input = "!!hello";
    std::string expected = "hello";
    ccapi::UtilString::ltrimInPlace(input, '!');
    EXPECT_EQ(input, expected);
}

TEST(LtrimInPlaceTest, LtrimInPlace_LeadingCharacterAndSpaces_WithSingleChar) {
    std::string input = "!   hello";
    std::string expected = "   hello";
    ccapi::UtilString::ltrimInPlace(input, '!');
    EXPECT_EQ(input, expected);
}

TEST(LtrimInPlaceTest, LtrimInPlace_AllTargetChars_WithSingleChar) {
    std::string input = "!!!!!";
    std::string expected;
    ccapi::UtilString::ltrimInPlace(input, '!');
    EXPECT_EQ(input, expected);
}

// test function rtrim
TEST(RtrimTest, Rtrim_EmptyString_WithChars) {
    std::string input;
    std::string expected;
    EXPECT_EQ(ccapi::UtilString::rtrim(input), expected);
}

TEST(RtrimTest, Rtrim_NoTrailingWhitespace_WithChars) {
    std::string input = "hello";
    std::string expected = "hello";
    EXPECT_EQ(ccapi::UtilString::rtrim(input), expected);
}

TEST(RtrimTest, Rtrim_TrailingSpaces_WithChars) {
    std::string input = "hello   ";
    std::string expected = "hello";
    EXPECT_EQ(ccapi::UtilString::rtrim(input), expected);
}

TEST(RtrimTest, Rtrim_TrailingTabsAndSpaces_WithChars) {
    std::string input = "hello\t   ";
    std::string expected = "hello";
    EXPECT_EQ(ccapi::UtilString::rtrim(input), expected);
}

TEST(RtrimTest, Rtrim_OnlyWhitespace_WithChars) {
    std::string input = "\t \n";
    std::string expected;
    EXPECT_EQ(ccapi::UtilString::rtrim(input), expected);
}

TEST(RtrimTest, Rtrim_CustomCharSet) {
    std::string input = "hello!!!";
    std::string expected = "hello";
    EXPECT_EQ(ccapi::UtilString::rtrim(input, "!"), expected);
}

TEST(RtrimTest, Rtrim_MultipleCustomChars) {
    std::string input = "hello!!@@";
    std::string expected = "hello";
    EXPECT_EQ(ccapi::UtilString::rtrim(input, "!@"), expected);
}

// test rtrim function
TEST(RtrimTest, Rtrim_EmptyString_WithSingleChar) {
    std::string input;
    std::string expected;
    EXPECT_EQ(ccapi::UtilString::rtrim(input, '!'), expected);
}

TEST(RtrimTest, Rtrim_NoTrailingCharacter_WithSingleChar) {
    std::string input = "hello";
    std::string expected = "hello";
    EXPECT_EQ(ccapi::UtilString::rtrim(input, '!'), expected);
}

TEST(RtrimTest, Rtrim_TrailingCharacter_WithSingleChar) {
    std::string input = "hello!!";
    std::string expected = "hello";
    EXPECT_EQ(ccapi::UtilString::rtrim(input, '!'), expected);
}

TEST(RtrimTest, Rtrim_TrailingCharacterAndSpaces_WithSingleChar) {
    std::string input = "hello   !";
    std::string expected = "hello   ";
    EXPECT_EQ(ccapi::UtilString::rtrim(input, '!'), expected);
}

TEST(RtrimTest, Rtrim_AllTargetChars_WithSingleChar) {
    std::string input = "!!!!!";
    std::string expected;
    EXPECT_EQ(ccapi::UtilString::rtrim(input, '!'), expected);
}

// test function rtrimInPlace
TEST(RtrimInPlaceTest, RtrimInPlace_EmptyString_WithChars) {
    std::string input;
    std::string expected;
    ccapi::UtilString::rtrimInPlace(input);
    EXPECT_EQ(input, expected);
}

TEST(RtrimInPlaceTest, RtrimInPlace_NoTrailingWhitespace_WithChars) {
    std::string input = "hello";
    std::string expected = "hello";
    ccapi::UtilString::rtrimInPlace(input);
    EXPECT_EQ(input, expected);
}

TEST(RtrimInPlaceTest, RtrimInPlace_TrailingSpaces_WithChars) {
    std::string input = "hello   ";
    std::string expected = "hello";
    ccapi::UtilString::rtrimInPlace(input);
    EXPECT_EQ(input, expected);
}

TEST(RtrimInPlaceTest, RtrimInPlace_TrailingTabsAndSpaces_WithChars) {
    std::string input = "hello\t   ";
    std::string expected = "hello";
    ccapi::UtilString::rtrimInPlace(input);
    EXPECT_EQ(input, expected);
}

TEST(RtrimInPlaceTest, RtrimInPlace_OnlyWhitespace_WithChars) {
    std::string input = "\t \n";
    std::string expected;
    ccapi::UtilString::rtrimInPlace(input);
    EXPECT_EQ(input, expected);
}

TEST(RtrimInPlaceTest, RtrimInPlace_CustomCharSet) {
    std::string input = "hello!!!";
    std::string expected = "hello";
    ccapi::UtilString::rtrimInPlace(input, "!");
    EXPECT_EQ(input, expected);
}

TEST(RtrimInPlaceTest, RtrimInPlace_MultipleCustomChars) {
    std::string input = "hello!!@@";
    std::string expected = "hello";
    ccapi::UtilString::rtrimInPlace(input, "!@");
    EXPECT_EQ(input, expected);
}

// test function rtrimInPlace
TEST(RtrimInPlaceTest, RtrimInPlace_EmptyString_WithSingleChar) {
    std::string input;
    std::string expected;
    ccapi::UtilString::rtrimInPlace(input, '!');
    EXPECT_EQ(input, expected);
}

TEST(RtrimInPlaceTest, RtrimInPlace_NoTrailingCharacter_WithSingleChar) {
    std::string input = "hello";
    std::string expected = "hello";
    ccapi::UtilString::rtrimInPlace(input, '!');
    EXPECT_EQ(input, expected);
}

TEST(RtrimInPlaceTest, RtrimInPlace_TrailingCharacter_WithSingleChar) {
    std::string input = "hello!!";
    std::string expected = "hello";
    ccapi::UtilString::rtrimInPlace(input, '!');
    EXPECT_EQ(input, expected);
}

TEST(RtrimInPlaceTest, RtrimInPlace_TrailingCharacterAndSpaces_WithSingleChar) {
    std::string input = "hello   !";
    std::string expected = "hello   ";
    ccapi::UtilString::rtrimInPlace(input, '!');
    EXPECT_EQ(input, expected);
}

TEST(RtrimInPlaceTest, RtrimInPlace_AllTargetChars_WithSingleChar) {
    std::string input = "!!!!!";
    std::string expected;
    ccapi::UtilString::rtrimInPlace(input, '!');
    EXPECT_EQ(input, expected);
}

// test function trim
TEST(TrimTest, Trim_EmptyString_WithChars) {
    std::string input;
    std::string expected;
    EXPECT_EQ(ccapi::UtilString::trim(input), expected);
}

TEST(TrimTest, Trim_NoWhitespace_WithChars) {
    std::string input = "hello";
    std::string expected = "hello";
    EXPECT_EQ(ccapi::UtilString::trim(input), expected);
}

TEST(TrimTest, Trim_LeadingAndTrailingSpaces_WithChars) {
    std::string input = "   hello   ";
    std::string expected = "hello";
    EXPECT_EQ(ccapi::UtilString::trim(input), expected);
}

TEST(TrimTest, Trim_LeadingAndTrailingTabsAndSpaces_WithChars) {
    std::string input = "\t   hello   \t";
    std::string expected = "hello";
    EXPECT_EQ(ccapi::UtilString::trim(input), expected);
}

TEST(TrimTest, Trim_OnlyWhitespace_WithChars) {
    std::string input = "\t \n\v\f\r";
    std::string expected;
    EXPECT_EQ(ccapi::UtilString::trim(input), expected);
}

TEST(TrimTest, Trim_CustomCharSet) {
    std::string input = "***hello***";
    std::string expected = "hello";
    EXPECT_EQ(ccapi::UtilString::trim(input, "*"), expected);
}

TEST(TrimTest, Trim_MultipleCustomChars) {
    std::string input = "***!!!hello!!!***";
    std::string expected = "hello";
    EXPECT_EQ(ccapi::UtilString::trim(input, "!*"), expected);
}

// test function trim
TEST(TrimTest, Trim_EmptyString_WithSingleChar) {
    std::string input;
    std::string expected;
    EXPECT_EQ(ccapi::UtilString::trim(input, '!'), expected);
}

TEST(TrimTest, Trim_NoTargetCharacter_WithSingleChar) {
    std::string input = "hello";
    std::string expected = "hello";
    EXPECT_EQ(ccapi::UtilString::trim(input, '!'), expected);
}

TEST(TrimTest, Trim_LeadingAndTrailingCharacter_WithSingleChar) {
    std::string input = "!!!hello!!!";
    std::string expected = "hello";
    char c = '!';
    std::string actual_string = ccapi::UtilString::trim(input, c);
    EXPECT_EQ(actual_string, expected);
}

TEST(TrimTest, Trim_LeadingAndTrailingCharacter_WithSingleChar2) {
    std::string input = "!!!!hello!!!!";
    std::string expected = "hello";
    EXPECT_EQ(ccapi::UtilString::trim(input, '!'), expected);
}

TEST(TrimTest, Trim_LeadingAndTrailingCharacter_WithSingleChar3) {
    std::string input = "***hello***";
    std::string expected = "hello";
    EXPECT_EQ(ccapi::UtilString::trim(input, '*'), expected);
}

TEST(TrimTest, Trim_LeadingAndTrailingCharacter_WithSingleChar4) {
    std::string input = "!!!qqq!!!";
    std::string expected = "qqq";
    EXPECT_EQ(ccapi::UtilString::trim(input, '!'), expected);
}

TEST(TrimTest, Trim_OnlyTargetCharacter_WithSingleChar) {
    std::string input = "!!!!!";
    std::string expected;
    EXPECT_EQ(ccapi::UtilString::trim(input, '!'), expected);
}

TEST(TrimTest, Trim_LeadingAndTrailingCharacterAndSpaces_WithSingleChar) {
    std::string input = "  !hello!  ";
    std::string expected = "!hello!";
    EXPECT_EQ(ccapi::UtilString::trim(input, ' '), expected);
}

// test function trimInPlace
TEST(TrimInPlaceTest, TrimInPlace_EmptyString_WithChars) {
    std::string input;
    ccapi::UtilString::trimInPlace(input);
    EXPECT_EQ(input, "");
}

TEST(TrimInPlaceTest, TrimInPlace_NoWhitespace_WithChars) {
    std::string input = "hello";
    ccapi::UtilString::trimInPlace(input);
    EXPECT_EQ(input, "hello");
}

TEST(TrimInPlaceTest, TrimInPlace_LeadingAndTrailingSpaces_WithChars) {
    std::string input = "   hello   ";
    ccapi::UtilString::trimInPlace(input);
    EXPECT_EQ(input, "hello");
}

TEST(TrimInPlaceTest, TrimInPlace_LeadingAndTrailingTabsAndSpaces_WithChars) {
    std::string input = "\t   hello   \t";
    ccapi::UtilString::trimInPlace(input);
    EXPECT_EQ(input, "hello");
}

TEST(TrimInPlaceTest, TrimInPlace_OnlyWhitespace_WithChars) {
    std::string input = "\t \n\v\f\r";
    ccapi::UtilString::trimInPlace(input);
    EXPECT_EQ(input, "");
}

TEST(TrimInPlaceTest, TrimInPlace_CustomCharSet) {
    std::string input = "***hello***";
    ccapi::UtilString::trimInPlace(input, "*");
    EXPECT_EQ(input, "hello");
}

TEST(TrimInPlaceTest, TrimInPlace_MultipleCustomChars) {
    std::string input = "***!!!hello!!!***";
    ccapi::UtilString::trimInPlace(input, "!*");
    EXPECT_EQ(input, "hello");
}

// test function trimInPlace
TEST(TrimInPlaceTest, TrimInPlace_EmptyString_WithSingleChar) {
    std::string input;
    ccapi::UtilString::trimInPlace(input, '!');
    EXPECT_EQ(input, "");
}

TEST(TrimInPlaceTest, TrimInPlace_NoTargetCharacter_WithSingleChar) {
    std::string input = "hello";
    ccapi::UtilString::trimInPlace(input, '!');
    EXPECT_EQ(input, "hello");
}

TEST(TrimInPlaceTest, TrimInPlace_LeadingAndTrailingCharacter_WithSingleChar) {
    std::string input = "!!!hello!!!";
    ccapi::UtilString::trimInPlace(input, '!');
    EXPECT_EQ(input, "hello");
}

TEST(TrimInPlaceTest, TrimInPlace_OnlyTargetCharacter_WithSingleChar) {
    std::string input = "!!!!!";
    ccapi::UtilString::trimInPlace(input, '!');
    EXPECT_EQ(input, "");
}

TEST(TrimInPlaceTest, TrimInPlace_LeadingAndTrailingCharacterAndSpaces_WithSingleChar) {
    std::string input = "  !hello!  ";
    ccapi::UtilString::trimInPlace(input, ' ');
    EXPECT_EQ(input, "!hello!");
}

// test function firstNCharacter
TEST(FirstNCharacterTest, ReturnsOriginalStringWhenLengthLessThanN) {
    std::string input = "hello";
    size_t n = 10;
    EXPECT_EQ(ccapi::UtilString::firstNCharacter(input, n), input);
}

TEST(FirstNCharacterTest, ReturnsOriginalStringWhenLengthEqualToN) {
    std::string input = "hello";
    size_t n = 5;
    EXPECT_EQ(ccapi::UtilString::firstNCharacter(input, n), input);
}

TEST(FirstNCharacterTest, ReturnsFirstNCharactersAndEllipsisWhenLengthGreaterThanN) {
    std::string input = "hello, world!";
    size_t n = 5;
    EXPECT_EQ(ccapi::UtilString::firstNCharacter(input, n), "hello...");
}

TEST(FirstNCharacterTest, HandlesEmptyString) {
    std::string input;
    size_t n = 5;
    EXPECT_EQ(ccapi::UtilString::firstNCharacter(input, n), "");
}

TEST(FirstNCharacterTest, HandlesNEqualToZero) {
    std::string input = "hello";
    size_t n = 0;
    EXPECT_EQ(ccapi::UtilString::firstNCharacter(input, n), "...");
}

TEST(FirstNCharacterTest, HandlesLargeN) {
    std::string input = "short";
    size_t n = 100;
    EXPECT_EQ(ccapi::UtilString::firstNCharacter(input, n), input);
}

// test function normalizeDecimalString
TEST(NormalizeDecimalStringTest, ReturnsOriginalIfNoDecimalPoint) {
    std::string input = "12345";
    EXPECT_EQ(ccapi::UtilString::normalizeDecimalString(input), input);
}

TEST(NormalizeDecimalStringTest, RemovesTrailingZerosAfterDecimal) {
    std::string input = "123.45000";
    EXPECT_EQ(ccapi::UtilString::normalizeDecimalString(input), "123.45");
}

TEST(NormalizeDecimalStringTest, RemovesTrailingDecimalPointIfNoFractionalPartRemains) {
    std::string input = "123.00000";
    EXPECT_EQ(ccapi::UtilString::normalizeDecimalString(input), "123");
}

TEST(NormalizeDecimalStringTest, DoesNotModifyIfNoTrailingZeros) {
    std::string input = "123.45";
    EXPECT_EQ(ccapi::UtilString::normalizeDecimalString(input), input);
}

TEST(NormalizeDecimalStringTest, HandlesStringWithOnlyDecimalPoint) {
    std::string input = ".00000";
    EXPECT_EQ(ccapi::UtilString::normalizeDecimalString(input), "");
}

TEST(NormalizeDecimalStringTest, HandlesEmptyString) {
    std::string input;
    EXPECT_EQ(ccapi::UtilString::normalizeDecimalString(input), "");
}

TEST(NormalizeDecimalStringTest, HandlesMultipleDecimalPoints) {
    std::string input = "123.450.00";
    EXPECT_EQ(ccapi::UtilString::normalizeDecimalString(input), "123.450");  // Should not modify since it's an invalid number
}

// test function normalizeDecimalString
TEST(NormalizeDecimalStringTest, ReturnsOriginalIfNoDecimalPoint1) {
    const char* input = "12345";
    EXPECT_EQ(ccapi::UtilString::normalizeDecimalString(input), std::string(input));
}

TEST(NormalizeDecimalStringTest, RemovesTrailingZerosAfterDecimal1) {
    const char* input = "123.45000";
    EXPECT_EQ(ccapi::UtilString::normalizeDecimalString(input), "123.45");
}

TEST(NormalizeDecimalStringTest, RemovesTrailingDecimalPointIfNoFractionalPartRemains1) {
    const char* input = "123.00000";
    EXPECT_EQ(ccapi::UtilString::normalizeDecimalString(input), "123");
}

TEST(NormalizeDecimalStringTest, DoesNotModifyIfNoTrailingZeros1) {
    const char* input = "123.45";
    EXPECT_EQ(ccapi::UtilString::normalizeDecimalString(input), std::string(input));
}

TEST(NormalizeDecimalStringTest, HandlesStringWithOnlyDecimalPoint1) {
    const char* input = ".00000";
    EXPECT_EQ(ccapi::UtilString::normalizeDecimalString(input), "");
}

TEST(NormalizeDecimalStringTest, HandlesEmptyString1) {
    const char* input = "";
    EXPECT_EQ(ccapi::UtilString::normalizeDecimalString(input), "");
}

TEST(NormalizeDecimalStringTest, HandlesMultipleDecimalPoints1) {
    const char* input = "123.450.00";
    EXPECT_EQ(ccapi::UtilString::normalizeDecimalString(input), "123.450");  // Should not modify since it's an invalid number
}

// test function leftPadTo
TEST(LeftPadToTest, PadsToLengthWithPaddingChar) {
    EXPECT_EQ(ccapi::UtilString::leftPadTo("123", 5, '0'), "00123");
    EXPECT_EQ(ccapi::UtilString::leftPadTo("abc", 6, '*'), "***abc");
}

TEST(LeftPadToTest, ReturnsOriginalIfLengthIsSufficient) {
    EXPECT_EQ(ccapi::UtilString::leftPadTo("123", 3, '0'), "123");
    EXPECT_EQ(ccapi::UtilString::leftPadTo("abcdef", 5, '*'), "abcdef");
}

TEST(LeftPadToTest, PadsWithSpacesByDefault) {
    EXPECT_EQ(ccapi::UtilString::leftPadTo("xyz", 5, ' '), "  xyz");
}

// test function rightPadTo
TEST(RightPadToTest, PadsToLengthWithPaddingChar) {
    EXPECT_EQ(ccapi::UtilString::rightPadTo("123", 5, '0'), "12300");
    EXPECT_EQ(ccapi::UtilString::rightPadTo("abc", 6, '*'), "abc***");
}

TEST(RightPadToTest, ReturnsOriginalIfLengthIsSufficient) {
    EXPECT_EQ(ccapi::UtilString::rightPadTo("123", 3, '0'), "123");
    EXPECT_EQ(ccapi::UtilString::rightPadTo("abcdef", 5, '*'), "abcdef");
}

TEST(RightPadToTest, PadsWithSpacesByDefault) {
    EXPECT_EQ(ccapi::UtilString::rightPadTo("xyz", 5, ' '), "xyz  ");
}

// test function generateUuidV4
TEST(GenerateUuidV4Test, GeneratesValidUuidV4Format) {
    std::string uuid = ccapi::UtilString::generateUuidV4();

    // 正则表达式匹配 UUID v4 的格式
    std::regex uuid_regex("^[0-9a-f]{8}-[0-9a-f]{4}-4[0-9a-f]{3}-[89ab][0-9a-f]{3}-[0-9a-f]{12}$");

    EXPECT_TRUE(std::regex_match(uuid, uuid_regex));
}

TEST(GenerateUuidV4Test, GeneratesUniqueUuids) {
    std::set<std::string> uuids;
    const int NUM_UUids = 1000;  // 生成的 UUID 数量

    for (int i = 0; i < NUM_UUids; ++i) {
        uuids.insert(ccapi::UtilString::generateUuidV4());
    }

    // 检查生成的 UUID 数量是否等于插入的数量
    int uuids_size = static_cast<int>(uuids.size());
    EXPECT_EQ(uuids_size, NUM_UUids);
}

// test function generateRandomString
TEST(GenerateRandomStringTest, GeneratesCorrectLengthString) {
    const size_t length = 10;
    std::string randomStr = ccapi::UtilString::generateRandomString(length);
    EXPECT_EQ(randomStr.length(), length);
}

TEST(GenerateRandomStringTest, GeneratesStringWithValidCharacters) {
    const size_t length = 100; // 测试长度
    std::string randomStr = ccapi::UtilString::generateRandomString(length);

    // 定义允许的字符集
    const std::unordered_set<char> allowedChars({
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
        'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
    });

    // 确保每个字符都在允许的字符集合中
    for (const char& c : randomStr) {
        EXPECT_TRUE(allowedChars.count(c) > 0) << "Invalid character found: " << c;
    }
}

// test isNumber
TEST(IsNumberTest, EmptyStringReturnsFalse) {
    EXPECT_FALSE(ccapi::UtilString::isNumber(""));
}

TEST(IsNumberTest, OnlyDigitsReturnsTrue) {
    EXPECT_TRUE(ccapi::UtilString::isNumber("1234567890"));
    EXPECT_TRUE(ccapi::UtilString::isNumber("0"));      // 单个数字
    EXPECT_TRUE(ccapi::UtilString::isNumber("123"));    // 多个数字
}

TEST(IsNumberTest, ContainsNonDigitReturnsFalse) {
    EXPECT_FALSE(ccapi::UtilString::isNumber("123a"));   // 包含字母
    EXPECT_FALSE(ccapi::UtilString::isNumber("12.34"));  // 包含小数点
    EXPECT_FALSE(ccapi::UtilString::isNumber("-123"));    // 包含负号
    EXPECT_FALSE(ccapi::UtilString::isNumber("12 34"));  // 包含空格
}

TEST(IsNumberTest, SpecialCharactersReturnsFalse) {
    EXPECT_FALSE(ccapi::UtilString::isNumber("123!"));   // 包含特殊字符
    EXPECT_FALSE(ccapi::UtilString::isNumber("abc!"));   // 完全是字母和特殊字符
}

TEST(IsNumberTest, MixedContentReturnsFalse) {
    EXPECT_FALSE(ccapi::UtilString::isNumber("123abc")); // 混合数字和字母
}

// test printDoubleScientific
TEST(PrintDoubleScientificTest, BasicNumber) {
    EXPECT_EQ(ccapi::UtilString::printDoubleScientific(123456789, 6), "1.234568e+08"); // 默认精度6
}

TEST(PrintDoubleScientificTest, NegativeNumber) {
    EXPECT_EQ(ccapi::UtilString::printDoubleScientific(-0.000123456, 6), "-1.234560e-04");
}

TEST(PrintDoubleScientificTest, Zero) {
    EXPECT_EQ(ccapi::UtilString::printDoubleScientific(0.0, 6), "0.000000e+00"); // 默认精度6
}

TEST(PrintDoubleScientificTest, CustomPrecision) {
    EXPECT_EQ(ccapi::UtilString::printDoubleScientific(123456789, 3), "1.235e+08"); // 精度3
    EXPECT_EQ(ccapi::UtilString::printDoubleScientific(123456789, 10), "1.2345678900e+08"); // 精度10
}

TEST(PrintDoubleScientificTest, VerySmallNumber) {
    EXPECT_EQ(ccapi::UtilString::printDoubleScientific(1.23456789e-10, 6), "1.234568e-10"); // 默认精度6
}

TEST(PrintDoubleScientificTest, VeryLargeNumber) {
    EXPECT_EQ(ccapi::UtilString::printDoubleScientific(1.23456789e+30, 6), "1.234568e+30"); // 默认精度6
}

TEST(PrintDoubleScientificTest, NegativeVerySmallNumber) {
    EXPECT_EQ(ccapi::UtilString::printDoubleScientific(-1.23456789e-10, 6), "-1.234568e-10"); // 默认精度6
}

TEST(PrintDoubleScientificTest, NegativeVeryLargeNumber) {
    EXPECT_EQ(ccapi::UtilString::printDoubleScientific(-1.23456789e+30, 6), "-1.234568e+30"); // 默认精度6
}

// test function endsWith
TEST(EndsWithTest, BasicMatch) {
    EXPECT_TRUE(ccapi::UtilString::endsWith("hello world", "world"));
}

TEST(EndsWithTest, BasicNoMatch) {
    EXPECT_FALSE(ccapi::UtilString::endsWith("hello world", "hello"));
}

TEST(EndsWithTest, MatchWithSameString) {
    EXPECT_TRUE(ccapi::UtilString::endsWith("test", "test"));
}

TEST(EndsWithTest, EmptyMainStr) {
    EXPECT_FALSE(ccapi::UtilString::endsWith("", "test"));
}

TEST(EndsWithTest, EmptyToMatch) {
    EXPECT_TRUE(ccapi::UtilString::endsWith("test", ""));
}

TEST(EndsWithTest, MainStrShorterThanToMatch) {
    EXPECT_FALSE(ccapi::UtilString::endsWith("short", "longer"));
}

TEST(EndsWithTest, SpecialCharacters) {
    EXPECT_TRUE(ccapi::UtilString::endsWith("!@#$%^&*()", "&*()"));
    EXPECT_FALSE(ccapi::UtilString::endsWith("!@#$%^&*()", "@#$"));
}

TEST(EndsWithTest, NumericStrings) {
    EXPECT_TRUE(ccapi::UtilString::endsWith("1234567890", "890"));
    EXPECT_FALSE(ccapi::UtilString::endsWith("1234567890", "1234"));
}

// test function replaceFirstOccurrence
TEST(ReplaceFirstOccurrenceTest, BasicReplacement) {
    std::string input = "Hello, World!";
    std::string result = ccapi::UtilString::replaceFirstOccurrence(input, "World", "Universe");
    EXPECT_EQ(result, "Hello, Universe!");
}

TEST(ReplaceFirstOccurrenceTest, NoOccurrence) {
    std::string input = "Hello, World!";
    std::string result = ccapi::UtilString::replaceFirstOccurrence(input, "Earth", "Universe");
    EXPECT_EQ(result, "Hello, World!"); // 没有发生替换
}

TEST(ReplaceFirstOccurrenceTest, ReplaceAtStart) {
    std::string input = "Hello, World!";
    std::string result = ccapi::UtilString::replaceFirstOccurrence(input, "Hello", "Hi");
    EXPECT_EQ(result, "Hi, World!");
}

TEST(ReplaceFirstOccurrenceTest, ReplaceAtEnd) {
    std::string input = "Hello, World!";
    std::string result = ccapi::UtilString::replaceFirstOccurrence(input, "World!", "Universe!");
    EXPECT_EQ(result, "Hello, Universe!");
}

TEST(ReplaceFirstOccurrenceTest, ReplaceMultipleOccurrences) {
    std::string input = "banana banana banana";
    std::string result = ccapi::UtilString::replaceFirstOccurrence(input, "banana", "apple");
    EXPECT_EQ(result, "apple banana banana"); // 只替换第一个
}

TEST(ReplaceFirstOccurrenceTest, EmptyString) {
    std::string input;
    std::string result = ccapi::UtilString::replaceFirstOccurrence(input, "nothing", "something");
    EXPECT_EQ(result, ""); // 空字符串不应变化
}

TEST(ReplaceFirstOccurrenceTest, ReplaceWithEmpty) {
    std::string input = "Hello, World!";
    std::string result = ccapi::UtilString::replaceFirstOccurrence(input, "World", "");
    EXPECT_EQ(result, "Hello, !");
}

TEST(ReplaceFirstOccurrenceTest, EmptyToReplace) {
    std::string input = "Hello, World!";
    std::string result = ccapi::UtilString::replaceFirstOccurrence(input, "", "Universe");
    EXPECT_EQ(result, "UniverseHello, World!");
}

TEST(ReplaceFirstOccurrenceTest, EntireStringReplacement) {
    std::string input = "Hello";
    std::string result = ccapi::UtilString::replaceFirstOccurrence(input, "Hello", "Hi");
    EXPECT_EQ(result, "Hi");
}

// test function roundInputBySignificantFigure
TEST(RoundInputBySignificantFigureTest, RoundPositiveNumberUp0) {
    EXPECT_EQ(ccapi::UtilString::roundInputBySignificantFigure(12345.6789, 4, 0), "12350");
}

TEST(RoundInputBySignificantFigureTest, RoundPositiveNumberUp1) {
    EXPECT_EQ(ccapi::UtilString::roundInputBySignificantFigure(123.456, 3, 1), "124");
}

TEST(RoundInputBySignificantFigureTest, RoundPositiveNumberDown) {
    EXPECT_EQ(ccapi::UtilString::roundInputBySignificantFigure(123.456, 3, -1), "123");
}

TEST(RoundInputBySignificantFigureTest, RoundPositiveNumberNearest) {
    EXPECT_EQ(ccapi::UtilString::roundInputBySignificantFigure(123.456, 3, 0), "123");
}

TEST(RoundInputBySignificantFigureTest, RoundNegativeNumberUp) {
    EXPECT_EQ(ccapi::UtilString::roundInputBySignificantFigure(-123.456, 3, 1), "-123");
}

TEST(RoundInputBySignificantFigureTest, RoundNegativeNumberDown) {
    EXPECT_EQ(ccapi::UtilString::roundInputBySignificantFigure(-123.456, 3, -1), "-124");
}

TEST(RoundInputBySignificantFigureTest, RoundNegativeNumberNearest) {
    EXPECT_EQ(ccapi::UtilString::roundInputBySignificantFigure(-123.456, 3, 0), "-123");
}

TEST(RoundInputBySignificantFigureTest, SmallNumber) {
    EXPECT_EQ(ccapi::UtilString::roundInputBySignificantFigure(0.00123456, 3, 1), "0.00124");
}

TEST(RoundInputBySignificantFigureTest, LargeNumber) {
    EXPECT_EQ(ccapi::UtilString::roundInputBySignificantFigure(123456789.0, 5, 0), "123460000");
}

TEST(RoundInputBySignificantFigureTest, ZeroInput) {
    EXPECT_EQ(ccapi::UtilString::roundInputBySignificantFigure(0.0, 3, 0), "0.00");
}

TEST(RoundInputBySignificantFigureTest, ZeroInput1) {
    EXPECT_EQ(ccapi::UtilString::roundInputBySignificantFigure(0.0, 3, 1), "0.00");
}

TEST(RoundInputBySignificantFigureTest, OneSignificantFigure) {
    EXPECT_EQ(ccapi::UtilString::roundInputBySignificantFigure(0.12345, 1, 0), "0.1");
    EXPECT_EQ(ccapi::UtilString::roundInputBySignificantFigure(0.12345, 1, 1), "0.2");
    EXPECT_EQ(ccapi::UtilString::roundInputBySignificantFigure(1.2345, 1, 0), "1");
    EXPECT_EQ(ccapi::UtilString::roundInputBySignificantFigure(12.345, 1, 0), "10");
}

TEST(RoundInputBySignificantFigureTest, RoundDirectionZero) {
    EXPECT_EQ(ccapi::UtilString::roundInputBySignificantFigure(0.00567, 2, 0), "0.0057");
}

TEST(RoundInputBySignificantFigureTest, NegativeSignificantFigures) {
    EXPECT_EQ(ccapi::UtilString::roundInputBySignificantFigure(123.456, 4, 0), "123.5"); // 处理负显著数字
}

// test function convertFIXTimeToISO
TEST(ConvertFIXTimeToISOTest, BasicConversion) {
    // 正确的 FIX 时间格式转换
    std::string fixTime = "20200925-15:55:28.093490622";
    std::string expectedISO = "2020-09-25T15:55:28.093490622Z";

    std::string result = ccapi::UtilTime::convertFIXTimeToISO(fixTime);
    EXPECT_EQ(result, expectedISO);
}

TEST(ConvertFIXTimeToISOTest, DifferentTimes) {
    // 测试不同的 FIX 时间字符串
    EXPECT_EQ(ccapi::UtilTime::convertFIXTimeToISO("20210101-00:00:00.000000000"), "2021-01-01T00:00:00.000000000Z");
    EXPECT_EQ(ccapi::UtilTime::convertFIXTimeToISO("19991231-23:59:59.999999999"), "1999-12-31T23:59:59.999999999Z");
    EXPECT_EQ(ccapi::UtilTime::convertFIXTimeToISO("20230515-08:30:15.123456789"), "2023-05-15T08:30:15.123456789Z");
}

TEST(ConvertFIXTimeToISOTest, ShortInput) {
    // 检查输入不符合预期长度的情况
    std::string fixTime = "20200925-15:55:28"; // 没有微秒部分
    std::string expectedISO = "2020-09-25T15:55:28Z"; // ISO 格式也省略微秒部分

    std::string result = ccapi::UtilTime::convertFIXTimeToISO(fixTime);
    EXPECT_EQ(result, expectedISO);
}

// test function ConvertTimePointToFIXTime
TEST(ConvertTimePointToFIXTimeTest, BasicConversion) {
    // 创建一个 TimePoint: 2023年9月30日 14:45:12.123
    std::tm timeinfo = {};
    timeinfo.tm_year = 2023 - 1900;
    timeinfo.tm_mon = 8;  // September
    timeinfo.tm_mday = 30;
    timeinfo.tm_hour = 14;
    timeinfo.tm_min = 45;
    timeinfo.tm_sec = 12;
    std::time_t t = timegm(&timeinfo);

    ccapi::TimePoint tp = std::chrono::system_clock::from_time_t(t) + std::chrono::milliseconds(123);

    std::string expectedFIXTime = "20230930-14:45:12.123";
    std::string result = ccapi::UtilTime::convertTimePointToFIXTime(tp);

    EXPECT_EQ(result, expectedFIXTime);
}

TEST(ConvertTimePointToFIXTimeTest, ZeroPadding) {
    // 创建一个 TimePoint: 2023年1月5日 04:09:02.007
    std::tm timeinfo = {};
    timeinfo.tm_year = 2023 - 1900;
    timeinfo.tm_mon = 0;  // January
    timeinfo.tm_mday = 5;
    timeinfo.tm_hour = 4;
    timeinfo.tm_min = 9;
    timeinfo.tm_sec = 2;
    std::time_t t = timegm(&timeinfo);

    ccapi::TimePoint tp = std::chrono::system_clock::from_time_t(t) + std::chrono::milliseconds(7);

    std::string expectedFIXTime = "20230105-04:09:02.007";
    std::string result = ccapi::UtilTime::convertTimePointToFIXTime(tp);

    EXPECT_EQ(result, expectedFIXTime);
}

TEST(ConvertTimePointToFIXTimeTest, LeapYear) {
    // 创建一个 TimePoint: 2024年2月29日 12:30:45.999 (闰年)
    std::tm timeinfo = {};
    timeinfo.tm_year = 2024 - 1900;
    timeinfo.tm_mon = 1;  // February
    timeinfo.tm_mday = 29;
    timeinfo.tm_hour = 12;
    timeinfo.tm_min = 30;
    timeinfo.tm_sec = 45;
    std::time_t t = timegm(&timeinfo);

    ccapi::TimePoint tp = std::chrono::system_clock::from_time_t(t) + std::chrono::milliseconds(999);

    std::string expectedFIXTime = "20240229-12:30:45.999";
    std::string result = ccapi::UtilTime::convertTimePointToFIXTime(tp);

    EXPECT_EQ(result, expectedFIXTime);
}

TEST(ConvertTimePointToFIXTimeTest, MillisecondEdgeCase) {
    // 创建一个 TimePoint: 2022年12月31日 23:59:59.000
    std::tm timeinfo = {};
    timeinfo.tm_year = 2022 - 1900;
    timeinfo.tm_mon = 11;  // December
    timeinfo.tm_mday = 31;
    timeinfo.tm_hour = 23;
    timeinfo.tm_min = 59;
    timeinfo.tm_sec = 59;
    std::time_t t = timegm(&timeinfo);

    ccapi::TimePoint tp = std::chrono::system_clock::from_time_t(t);

    std::string expectedFIXTime = "20221231-23:59:59.000";
    std::string result = ccapi::UtilTime::convertTimePointToFIXTime(tp);

    EXPECT_EQ(result, expectedFIXTime);
}

//// test timePointToParts
//TEST(TimePointToPartsTest, BasicTest) {
//    int year, month, day, hour, minute, second, fractionalSecond;
//
//    std::tm timeinfo = {};
//    timeinfo.tm_year = 2024 - 1900; // 2024年
//    timeinfo.tm_mon = 10 - 1;       // 10月
//    timeinfo.tm_mday = 3;           // 3日
//    timeinfo.tm_hour = 15;          // 15:00
//    timeinfo.tm_min = 30;
//    timeinfo.tm_sec = 45;
//    auto time_c = timegm(&timeinfo);
//
//    ccapi::TimePoint tp = std::chrono::system_clock::from_time_t(time_c) + std::chrono::milliseconds(123);
//
//    ccapi::UtilTime::timePointToParts(tp, year, month, day, hour, minute, second, fractionalSecond);
//
//    EXPECT_EQ(year, 2024);
//    EXPECT_EQ(month, 10);
//    EXPECT_EQ(day, 3);
//    EXPECT_EQ(hour, 15);
//    EXPECT_EQ(minute, 30);
//    EXPECT_EQ(second, 45);
//    EXPECT_EQ(fractionalSecond, 123);
//}
//
//TEST(TimePointToPartsTest, LeapYearTest) {
//    int year, month, day, hour, minute, second, fractionalSecond;
//
//    std::tm timeinfo = {};
//    timeinfo.tm_year = 2020 - 1900; // 闰年
//    timeinfo.tm_mon = 2 - 1;
//    timeinfo.tm_mday = 29;
//    timeinfo.tm_hour = 12;
//    timeinfo.tm_min = 0;
//    timeinfo.tm_sec = 0;
//    auto time_c = timegm(&timeinfo);
//
//    ccapi::TimePoint tp = std::chrono::system_clock::from_time_t(time_c) + std::chrono::milliseconds(456);
//
//    ccapi::UtilTime::timePointToParts(tp, year, month, day, hour, minute, second, fractionalSecond);
//
//    EXPECT_EQ(year, 2020);
//    EXPECT_EQ(month, 2);
//    EXPECT_EQ(day, 29);
//    EXPECT_EQ(hour, 12);
//    EXPECT_EQ(minute, 0);
//    EXPECT_EQ(second, 0);
//    EXPECT_EQ(fractionalSecond, 456);
//}
//
//TEST(TimePointToPartsTest, EndOfYearTest) {
//    int year, month, day, hour, minute, second, fractionalSecond;
//
//    std::tm timeinfo = {};
//    timeinfo.tm_year = 2023 - 1900;
//    timeinfo.tm_mon = 12 - 1;
//    timeinfo.tm_mday = 31;
//    timeinfo.tm_hour = 23;
//    timeinfo.tm_min = 59;
//    timeinfo.tm_sec = 59;
//    auto time_c = timegm(&timeinfo);
//
//    ccapi::TimePoint tp = std::chrono::system_clock::from_time_t(time_c) + std::chrono::milliseconds(999);
//
//    ccapi::UtilTime::timePointToParts(tp, year, month, day, hour, minute, second, fractionalSecond);
//
//    EXPECT_EQ(year, 2023);
//    EXPECT_EQ(month, 12);
//    EXPECT_EQ(day, 31);
//    EXPECT_EQ(hour, 23);
//    EXPECT_EQ(minute, 59);
//    EXPECT_EQ(second, 59);
//    EXPECT_EQ(fractionalSecond, 999);
//}
//
//TEST(TimePointToPartsTest, StartOfMonthTest) {
//    int year, month, day, hour, minute, second, fractionalSecond;
//
//    std::tm timeinfo = {};
//    timeinfo.tm_year = 2024 - 1900;
//    timeinfo.tm_mon = 3 - 1;
//    timeinfo.tm_mday = 1;
//    timeinfo.tm_hour = 0;
//    timeinfo.tm_min = 0;
//    timeinfo.tm_sec = 0;
//    auto time_c = timegm(&timeinfo);
//
//    ccapi::TimePoint tp = std::chrono::system_clock::from_time_t(time_c) + std::chrono::milliseconds(1);
//
//    ccapi::UtilTime::timePointToParts(tp, year, month, day, hour, minute, second, fractionalSecond);
//
//    EXPECT_EQ(year, 2024);
//    EXPECT_EQ(month, 3);
//    EXPECT_EQ(day, 1);
//    EXPECT_EQ(hour, 0);
//    EXPECT_EQ(minute, 0);
//    EXPECT_EQ(second, 0);
//    EXPECT_EQ(fractionalSecond, 1);
//}

TEST(TimePointToPartsTest, EndOfDayTest) {
    int year, month, day, hour, minute, second, fractionalSecond;

    std::tm timeinfo = {};
    timeinfo.tm_year = 2024 - 1900;
    timeinfo.tm_mon = 10 - 1;
    timeinfo.tm_mday = 2;
    timeinfo.tm_hour = 23;
    timeinfo.tm_min = 59;
    timeinfo.tm_sec = 59;
    auto time_c = timegm(&timeinfo);

    ccapi::TimePoint tp = std::chrono::system_clock::from_time_t(time_c) + std::chrono::milliseconds(500);

    ccapi::UtilTime::timePointToParts(tp, year, month, day, hour, minute, second, fractionalSecond);

    EXPECT_EQ(year, 2024);
    EXPECT_EQ(month, 10);
    EXPECT_EQ(day, 2);
    EXPECT_EQ(hour, 23);
    EXPECT_EQ(minute, 59);
    EXPECT_EQ(second, 59);
    EXPECT_EQ(fractionalSecond, 500);
}

TEST(TimePointToPartsTest, MinDateTimeTest) {
    int year, month, day, hour, minute, second, fractionalSecond;

    std::tm timeinfo = {};
    timeinfo.tm_year = 1970 - 1900;
    timeinfo.tm_mon = 1 - 1;
    timeinfo.tm_mday = 1;
    timeinfo.tm_hour = 0;
    timeinfo.tm_min = 0;
    timeinfo.tm_sec = 0;
    auto time_c = timegm(&timeinfo);

    ccapi::TimePoint tp = std::chrono::system_clock::from_time_t(time_c) + std::chrono::milliseconds(500);

    ccapi::UtilTime::timePointToParts(tp, year, month, day, hour, minute, second, fractionalSecond);

    EXPECT_EQ(year, 1970);
    EXPECT_EQ(month, 1);
    EXPECT_EQ(day, 1);
    EXPECT_EQ(hour, 0);
    EXPECT_EQ(minute, 0);
    EXPECT_EQ(second, 0);
    EXPECT_EQ(fractionalSecond, 500);
}

//// test now()
//TEST(NowFunctionTest, ReturnsCurrentTime) {
//    // 获取系统当前时间
//    auto system_now = std::chrono::system_clock::now();
//
//    // 获取 now() 函数返回的时间
//    ccapi::TimePoint func_now = ccapi::UtilTime::now();
//
//    // 检查两者时间差是否在合理范围内（如 1 秒内）
//    auto duration = std::chrono::duration_cast<std::chrono::seconds>(func_now - system_now).count();
//    EXPECT_LE(duration, 1) << "TimePoint from now() should be close to the system current time.";
//}
//
//TEST(NowFunctionTest, NotBeforeSystemTime) {
//    // 获取系统当前时间
//    auto system_now = std::chrono::system_clock::now();
//
//    // 获取 now() 函数返回的时间
//    ccapi::TimePoint func_now = ccapi::UtilTime::now();
//
//    // 检查 now() 返回的时间是否早于系统当前时间
//    EXPECT_GE(func_now.time_since_epoch().count(), system_now.time_since_epoch().count())
//                        << "TimePoint from now() should not be before system current time.";
//}
//
//TEST(NowFunctionTest, AfterEarlierTimePoint) {
//    // 获取早一点的系统时间
//    auto system_past = std::chrono::system_clock::now() - std::chrono::seconds(1);
//
//    // 获取 now() 函数返回的时间
//    ccapi::TimePoint func_now = ccapi::UtilTime::now();
//
//    // 验证 now() 的返回值应该晚于早一点的时间点
//    EXPECT_GT(func_now.time_since_epoch().count(), system_past.time_since_epoch().count())
//                        << "TimePoint from now() should be after a previous time point.";
//}
//

TEST(NowFunctionTest, ReturnsNonNullTimePoint) {
    ccapi::TimePoint func_now = ccapi::UtilTime::now();

    // 检查 now() 返回的时间点是否为非零值
    EXPECT_GT(func_now.time_since_epoch().count(), 0)
                        << "TimePoint from now() should not be a null time point.";
}

// test parse function
TEST(ParseFunctionTest, ValidDateWithoutTime) {
    std::string date_str = "2024-10-03";
    ccapi::TimePoint parsed_time = ccapi::UtilTime::parse(date_str);

    auto parsed_time_converted = std::chrono::time_point_cast<std::chrono::system_clock::duration>(parsed_time);
    std::time_t parsed_time_t = std::chrono::system_clock::to_time_t(parsed_time_converted);
    std::tm* parsed_tm = std::gmtime(&parsed_time_t);

    EXPECT_EQ(parsed_tm->tm_year, 2024 - 1900);
    EXPECT_EQ(parsed_tm->tm_mon, 9); // October (0-based)
    EXPECT_EQ(parsed_tm->tm_mday, 3);
    EXPECT_EQ(parsed_tm->tm_hour, 0);
    EXPECT_EQ(parsed_tm->tm_min, 0);
    EXPECT_EQ(parsed_tm->tm_sec, 0);
}

TEST(ParseFunctionTest, ValidDateWithTime) {
    std::string datetime_str = "2024-10-03T15:30:45";
    ccapi::TimePoint parsed_time = ccapi::UtilTime::parse(datetime_str);

    auto parsed_time_converted = std::chrono::time_point_cast<std::chrono::system_clock::duration>(parsed_time);
    std::time_t parsed_time_t = std::chrono::system_clock::to_time_t(parsed_time_converted);
    std::tm* parsed_tm = std::gmtime(&parsed_time_t);

    EXPECT_EQ(parsed_tm->tm_year, 2024 - 1900);
    EXPECT_EQ(parsed_tm->tm_mon, 9); // October (0-based)
    EXPECT_EQ(parsed_tm->tm_mday, 3);
    EXPECT_EQ(parsed_tm->tm_hour, 15);
    EXPECT_EQ(parsed_tm->tm_min, 30);
    EXPECT_EQ(parsed_tm->tm_sec, 45);
}

TEST(ParseFunctionTest, ValidDateWithNanoseconds) {
    std::string datetime_str = "2024-10-03T15:30:45.123456789Z";
    ccapi::TimePoint parsed_time = ccapi::UtilTime::parse(datetime_str);

    auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(parsed_time.time_since_epoch()).count();
    EXPECT_EQ(nanoseconds % 1000000000, 123456789);
}

TEST(ParseFunctionTest, HandlesTooLongNanoseconds) {
    std::string datetime_str = "2024-10-03T15:30:45.123456789123Z";
    EXPECT_THROW(ccapi::UtilTime::parse(datetime_str), std::invalid_argument);
}

TEST(ParseFunctionTest, HandlesInvalidDateFormat) {
    std::string invalid_date_str = "2024-13-03"; // Invalid month
    ccapi::TimePoint new_str = ccapi::UtilTime::parse(invalid_date_str);
    ccapi::TimePoint expected_time_point = ccapi::UtilTime::parse("2025-01-03 00:00:00.000000000");
    // std::cout << new_str << std::endl;
    // new_str = "2025-01-03 00:00:00.000000000"
    EXPECT_EQ(new_str, expected_time_point);
    // EXPECT_THROW(ccapi::UtilTime::parse(invalid_date_str), std::invalid_argument);
}

// test makeTimePoint
TEST(MakeTimePointTest, EpochTimePoint) {
    std::pair<long long, long long> timePair(0, 0);
    ccapi::TimePoint tp = ccapi::UtilTime::makeTimePoint(timePair);

    EXPECT_EQ(tp.time_since_epoch().count(), 0);
}

TEST(MakeTimePointTest, PositiveSecondsNoNanoseconds) {
    std::pair<long long, long long> timePair(10, 0);
    ccapi::TimePoint tp = ccapi::UtilTime::makeTimePoint(timePair);

    EXPECT_EQ(std::chrono::duration_cast<std::chrono::seconds>(tp.time_since_epoch()).count(), 10);
}

TEST(MakeTimePointTest, PositiveSecondsWithNanoseconds) {
    std::pair<long long, long long> timePair(10, 500000000); // 10.5 seconds
    ccapi::TimePoint tp = ccapi::UtilTime::makeTimePoint(timePair);

    EXPECT_EQ(std::chrono::duration_cast<std::chrono::seconds>(tp.time_since_epoch()).count(), 10);
    EXPECT_EQ(std::chrono::duration_cast<std::chrono::nanoseconds>(tp.time_since_epoch()).count(), 10500000000); // 10.5 seconds in nanoseconds
}

TEST(MakeTimePointTest, NegativeSecondsNoNanoseconds) {
    std::pair<long long, long long> timePair(-10, 0);
    ccapi::TimePoint tp = ccapi::UtilTime::makeTimePoint(timePair);

    EXPECT_EQ(std::chrono::duration_cast<std::chrono::seconds>(tp.time_since_epoch()).count(), -10);
}

TEST(MakeTimePointTest, NegativeSecondsWithNanoseconds) {
    std::pair<long long, long long> timePair(-10, 500000000); // -9.5 seconds
    ccapi::TimePoint tp = ccapi::UtilTime::makeTimePoint(timePair);

    EXPECT_EQ(std::chrono::duration_cast<std::chrono::seconds>(tp.time_since_epoch()).count(), -9);
    EXPECT_EQ(std::chrono::duration_cast<std::chrono::nanoseconds>(tp.time_since_epoch()).count(), -9500000000); // -9.5 seconds in nanoseconds
}

// test makeTimePointMilli
TEST(MakeTimePointMilliTest, ZeroTimePoint) {
    std::pair<long long, long long> timePair(0, 0);
    ccapi::TimePoint tp = ccapi::UtilTime::makeTimePointMilli(timePair);

    EXPECT_EQ(tp.time_since_epoch().count(), 0);
}

TEST(MakeTimePointMilliTest, OnlyMilliseconds) {
    std::pair<long long, long long> timePair(5000, 0); // 5000 milliseconds = 5 seconds
    ccapi::TimePoint tp = ccapi::UtilTime::makeTimePointMilli(timePair);

    EXPECT_EQ(std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch()).count(), 5000);
    EXPECT_EQ(std::chrono::duration_cast<std::chrono::seconds>(tp.time_since_epoch()).count(), 5);
}

TEST(MakeTimePointMilliTest, MillisecondsAndNanoseconds) {
    std::pair<long long, long long> timePair(1000, 500000000); // 1000 milliseconds + 0.5 seconds
    ccapi::TimePoint tp = ccapi::UtilTime::makeTimePointMilli(timePair);

    EXPECT_EQ(std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch()).count(), 1500); // 1500 milliseconds
    EXPECT_EQ(std::chrono::duration_cast<std::chrono::nanoseconds>(tp.time_since_epoch()).count(), 1500000000); // 1.5 seconds in nanoseconds
}

TEST(MakeTimePointMilliTest, NegativeMillisecondsNoNanoseconds) {
    std::pair<long long, long long> timePair(-2000, 0); // -2000 milliseconds
    ccapi::TimePoint tp = ccapi::UtilTime::makeTimePointMilli(timePair);

    EXPECT_EQ(std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch()).count(), -2000);
    EXPECT_EQ(std::chrono::duration_cast<std::chrono::seconds>(tp.time_since_epoch()).count(), -2);
}

TEST(MakeTimePointMilliTest, NegativeMillisecondsPositiveNanoseconds) {
    std::pair<long long, long long> timePair(-1000, 300000000); // -1000 milliseconds + 0.3 seconds
    ccapi::TimePoint tp = ccapi::UtilTime::makeTimePointMilli(timePair);

    EXPECT_EQ(std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch()).count(), -700); // -700 milliseconds
    EXPECT_EQ(std::chrono::duration_cast<std::chrono::nanoseconds>(tp.time_since_epoch()).count(), -700000000); // -0.7 seconds in nanoseconds
}

TEST(MakeTimePointMilliTest, LargeTimePoint) {
    std::pair<long long, long long> timePair(1000000000, 999999999); // 1000000000 milliseconds + 999999999 nanoseconds
    ccapi::TimePoint tp = ccapi::UtilTime::makeTimePointMilli(timePair);

    EXPECT_EQ(std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch()).count(), 1000000999); // 1001 seconds in milliseconds
    EXPECT_EQ(std::chrono::duration_cast<std::chrono::nanoseconds>(tp.time_since_epoch()).count(), 1000000999999999); // 1001.999999999 seconds in nanoseconds
}

// Test function divide(TimePoint)
TEST(DivideFunctionTest, BasicDivision) {
    // 1. Test case for a simple time point (1 second, 0 nanoseconds)
    ccapi::TimePoint tp = ccapi::TimePoint(std::chrono::seconds(1));
    auto result = ccapi::UtilTime::divide(tp);
    EXPECT_EQ(result.first, 1);
    EXPECT_EQ(result.second, 0);
}

TEST(DivideFunctionTest, ZeroTimePoint) {
    // 2. Test case for zero time point (0 seconds, 0 nanoseconds)
    ccapi::TimePoint tp = ccapi::TimePoint(std::chrono::seconds(0));
    auto result = ccapi::UtilTime::divide(tp);
    EXPECT_EQ(result.first, 0);
    EXPECT_EQ(result.second, 0);
}

TEST(DivideFunctionTest, NanosecondOnlyTimePoint) {
    // 3. Test case for time point with only nanoseconds (0 seconds, 100 nanoseconds)
    ccapi::TimePoint tp = ccapi::TimePoint(std::chrono::nanoseconds(100));
    auto result = ccapi::UtilTime::divide(tp);
    EXPECT_EQ(result.first, 0);
    EXPECT_EQ(result.second, 100);
}

TEST(DivideFunctionTest, MixedTimePoint) {
    // 4. Test case for a mixed time point (5 seconds, 500 nanoseconds)
    ccapi::TimePoint tp = ccapi::TimePoint(std::chrono::seconds(5)) + std::chrono::nanoseconds(500);
    auto result = ccapi::UtilTime::divide(tp);
    EXPECT_EQ(result.first, 5);
    EXPECT_EQ(result.second, 500);
}

TEST(DivideFunctionTest, LargeTimePoint) {
    // 5. Test case for a large time point (1000 seconds, 1 billion nanoseconds = 1 second)
    ccapi::TimePoint tp = ccapi::TimePoint(std::chrono::seconds(1000)) + std::chrono::nanoseconds(1000000000);
    auto result = ccapi::UtilTime::divide(tp);
    EXPECT_EQ(result.first, 1001); // 1000 seconds + 1 additional second from nanoseconds
    EXPECT_EQ(result.second, 0);   // All nanoseconds converted to seconds
}

// test divide
TEST(DivideTest, NoFractionalPart) {
    std::string seconds = "123";
    auto result = ccapi::UtilTime::divide(seconds);

    // 检查整数部分是否正确
    EXPECT_EQ(result.first, 123);
    // 检查小数部分是否为0
    EXPECT_EQ(result.second, 0);
}

TEST(DivideTest, WithFractionalPart) {
    std::string seconds = "123.456";
    auto result = ccapi::UtilTime::divide(seconds);

    // 检查整数部分是否正确
    EXPECT_EQ(result.first, 123);
    // 检查小数部分是否正确
    EXPECT_EQ(result.second, 456000000);  // 小数部分应 补 齐9位小数
}

TEST(DivideTest, FractionalPartWithTrailingZeros) {
    std::string seconds = "123.456000";
    auto result = ccapi::UtilTime::divide(seconds);

    // 检查整数部分是否正确
    EXPECT_EQ(result.first, 123);
    // 检查小数部分是否正确，去掉了末尾的零
    EXPECT_EQ(result.second, 456000000);
}

TEST(DivideTest, NoFractionAfterDot) {
    std::string seconds = "123.";
    auto result = ccapi::UtilTime::divide(seconds);

    // 检查整数部分是否正确
    EXPECT_EQ(result.first, 123);
    // 检查小数部分是否为0
    EXPECT_EQ(result.second, 0);
}

TEST(DivideTest, OnlyFractionalPart) {
    std::string seconds = "0.123456789";
    auto result = ccapi::UtilTime::divide(seconds);

    // 检查整数部分是否为0
    EXPECT_EQ(result.first, 0);
    // 检查小数部分是否正确
    EXPECT_EQ(result.second, 123456789);  // 应保留所有的小数
}

TEST(DivideTest, LongFractionalPart) {
    std::string seconds = "123.456789012345";
    auto result = ccapi::UtilTime::divide(seconds);

    // 检查整数部分是否正确
    EXPECT_EQ(result.first, 123);
    // 检查小数部分是否正确
    EXPECT_EQ(result.second, 456789012345);  // 只取前9位小数
}

// test divideMilli
TEST(DivideMilliTest, NoFractionalPart) {
    std::string milliseconds = "123";
    auto result = ccapi::UtilTime::divideMilli(milliseconds);

    // 检查整数部分是否正确
    EXPECT_EQ(result.first, 123);
    // 检查小数部分是否为0
    EXPECT_EQ(result.second, 0);
}

TEST(DivideMilliTest, WithFractionalPart) {
    std::string milliseconds = "123.456";
    auto result = ccapi::UtilTime::divideMilli(milliseconds);

    // 检查整数部分是否正确
    EXPECT_EQ(result.first, 123);
    // 检查小数部分是否正确
    EXPECT_EQ(result.second, 456000);  // 小数部分应 补 齐6位
}

TEST(DivideMilliTest, FractionalPartWithTrailingZeros) {
    std::string milliseconds = "123.456000";
    auto result = ccapi::UtilTime::divideMilli(milliseconds);

    // 检查整数部分是否正确
    EXPECT_EQ(result.first, 123);
    // 检查小数部分是否正确，去掉了末尾的零
    EXPECT_EQ(result.second, 456000);
}

TEST(DivideMilliTest, NoFractionAfterDot) {
    std::string milliseconds = "123.";
    auto result = ccapi::UtilTime::divideMilli(milliseconds);

    // 检查整数部分是否正确
    EXPECT_EQ(result.first, 123);
    // 检查小数部分是否为0
    EXPECT_EQ(result.second, 0);
}

TEST(DivideMilliTest, OnlyFractionalPart) {
    std::string milliseconds = "0.123456";
    auto result = ccapi::UtilTime::divideMilli(milliseconds);

    // 检查整数部分是否为0
    EXPECT_EQ(result.first, 0);
    // 检查小数部分是否正确
    EXPECT_EQ(result.second, 123456);  // 应保留所有的小数位
}

TEST(DivideMilliTest, LongFractionalPart) {
    std::string milliseconds = "123.456789012";
    auto result = ccapi::UtilTime::divideMilli(milliseconds);

    // 检查整数部分是否正确
    EXPECT_EQ(result.first, 123);
    // 检查小数部分是否正确
    EXPECT_EQ(result.second, 456789012);
}

// test convertMillisecondsStrToSecondsStr
TEST(ConvertMillisecondsStrToSecondsStrTest, MillisecondsLengthGreaterThanOrEqualToFour) {
    std::string milliseconds = "1234";
    std::string expectedOutput = "1.234";

    std::string result = ccapi::UtilTime::convertMillisecondsStrToSecondsStr(milliseconds);

    // 检查转换后的结果
    EXPECT_EQ(result, expectedOutput);
}

TEST(ConvertMillisecondsStrToSecondsStrTest, MillisecondsLengthLessThanFour) {
    std::string milliseconds = "123";
    std::string expectedOutput = "0.123";

    std::string result = ccapi::UtilTime::convertMillisecondsStrToSecondsStr(milliseconds);

    // 检查转换后的结果
    EXPECT_EQ(result, expectedOutput);
}

TEST(ConvertMillisecondsStrToSecondsStrTest, MillisecondsLengthWithLeadingZeros) {
    std::string milliseconds = "001";
    std::string expectedOutput = "0.001";

    std::string result = ccapi::UtilTime::convertMillisecondsStrToSecondsStr(milliseconds);

    // 检查转换后的结果
    EXPECT_EQ(result, expectedOutput);
}

TEST(ConvertMillisecondsStrToSecondsStrTest, MillisecondsLengthLessThanThreeWithLeadingZeroNormalization) {
    std::string milliseconds = "1";
    std::string expectedOutput = "0.001";

    std::string result = ccapi::UtilTime::convertMillisecondsStrToSecondsStr(milliseconds);

    // 检查转换后的结果
    EXPECT_EQ(result, expectedOutput);
}

TEST(ConvertMillisecondsStrToSecondsStrTest, MillisecondsWithOnlyZeros) {
    std::string milliseconds = "000";
    std::string expectedOutput = "0";

    std::string result = ccapi::UtilTime::convertMillisecondsStrToSecondsStr(milliseconds);

    // 检查转换后的结果
    EXPECT_EQ(result, expectedOutput);
}

TEST(ConvertMillisecondsStrToSecondsStrTest, MillisecondsZeroInput) {
    std::string milliseconds = "0";
    std::string expectedOutput = "0";

    std::string result = ccapi::UtilTime::convertMillisecondsStrToSecondsStr(milliseconds);
    // std::cout << "result = " << result << std::endl;
    // 检查转换后的结果
    EXPECT_EQ(result, expectedOutput);
}

// test divideNanoWhole
TEST(DivideNanoWholeTest, CorrectDivide) {
    std::string nanoseconds = "123456789012345678"; // 123456789秒, 012345678纳秒
    std::pair<long long, long long> expected = {123456789, 12345678}; // 秒部分，纳秒部分

    std::pair<long long, long long> result = ccapi::UtilTime::divideNanoWhole(nanoseconds);

    // 检查结果
    EXPECT_EQ(result.first, expected.first);
    EXPECT_EQ(result.second, expected.second);
}

TEST(DivideNanoWholeTest, LessThanNineDigits) {
    std::string nanoseconds = "123456"; // 没有足够的纳秒位
    // 应该抛出异常，因为我们尝试访问 nanoseconds 的非法范围
    std::pair<long long, long long> result = ccapi::UtilTime::divideNanoWhole(nanoseconds);
    std::pair<long long, long long> expected = {0, 123456};
    EXPECT_EQ(result.first, expected.first);
    EXPECT_EQ(result.second, expected.second);
    //EXPECT_THROW(ccapi::UtilTime::divideNanoWhole(nanoseconds), std::out_of_range);
}

TEST(DivideNanoWholeTest, ExactlyNineDigits) {
    std::string nanoseconds = "123456789"; // 0秒, 123456789纳秒
    std::pair<long long, long long> expected = {0, 123456789}; // 秒部分为0, 纳秒为123456789
    std::pair<long long, long long> result = ccapi::UtilTime::divideNanoWhole(nanoseconds);
    EXPECT_EQ(result.first, expected.first);
    EXPECT_EQ(result.second, expected.second);
    //EXPECT_THROW(ccapi::UtilTime::divideNanoWhole(nanoseconds), std::invalid_argument);
}

TEST(DivideNanoWholeTest, MoreThanEighteenDigits) {
    std::string nanoseconds = "1234567890123456789"; // 过长 的输入，应只拆分前18位
    std::pair<long long, long long> expected = {1234567890, 123456789}; // 秒部分和纳秒部分

    std::pair<long long, long long> result = ccapi::UtilTime::divideNanoWhole(nanoseconds);

    // 检查结果
    EXPECT_EQ(result.first, expected.first);
    EXPECT_EQ(result.second, expected.second);
}

TEST(DivideNanoWholeTest, AllZeros) {
    std::string nanoseconds = "000000000000000000"; // 全零输入
    std::pair<long long, long long> expected = {0, 0}; // 秒部分和纳秒部分均为0

    std::pair<long long, long long> result = ccapi::UtilTime::divideNanoWhole(nanoseconds);

    // 检查结果
    EXPECT_EQ(result.first, expected.first);
    EXPECT_EQ(result.second, expected.second);
}

// test getISOTimestamp
TEST(GetISOTimestampTest, BasicConversion) {
    // 创建一个 TimePoint: 2023年9月30日 14:45:12.123456789
    std::chrono::nanoseconds ns(123456789); // 123456789 纳秒
    ccapi::TimePoint tp = std::chrono::system_clock::from_time_t(1696079112) + ns; // 2023-09-30 14:45:12 UTC

    std::string expected = "2023-09-30T13:05:12.123456789Z";
    std::string result = ccapi::UtilTime::getISOTimestamp(tp);

    EXPECT_EQ(result, expected);
}

TEST(GetISOTimestampTest, WithMilliseconds) {
    // 创建一个 TimePoint: 2023年9月30日 14:45:12.123
    std::chrono::milliseconds ms(123); // 123 毫秒
    ccapi::TimePoint tp = std::chrono::system_clock::from_time_t(1696079112) + ms; // 2023-09-30 14:45:12 UTC

    std::string expected = "2023-09-30T13:05:12.123Z";
    std::string result = ccapi::UtilTime::getISOTimestamp< std::chrono::milliseconds >(tp);

    EXPECT_EQ(result, expected);
}

TEST(GetISOTimestampTest, WithMicroseconds) {
    // 创建一个 TimePoint: 2023年9月30日 14:45:12.123456
    std::chrono::microseconds us(123456); // 123456 微秒
    ccapi::TimePoint tp = std::chrono::system_clock::from_time_t(1696079112) + us; // 2023-09-30 14:45:12 UTC

    std::string expected = "2023-09-30T13:05:12.123456Z";
    std::string result = ccapi::UtilTime::getISOTimestamp< std::chrono::microseconds >(tp);

    EXPECT_EQ(result, expected);
}

TEST(GetISOTimestampTest, LeadingZeros) {
    // 创建一个 TimePoint: 2023年9月1日 03:05:09.007
    std::chrono::nanoseconds ns(7000000); // 7 毫秒
    ccapi::TimePoint tp = std::chrono::system_clock::from_time_t(1693530309) + ns; // 2023-09-01 03:05:09 UTC

    std::string expected = "2023-09-01T01:05:09.007000000Z";
    std::string result = ccapi::UtilTime::getISOTimestamp(tp);

    EXPECT_EQ(result, expected);
}

TEST(GetUnixTimestampTest, BasicTimestamps) {
    // 2023-01-01T00:00:00Z, 该时间点的 Unix 时间戳应为 1672531200
    std::tm timeinfo = {};
    timeinfo.tm_year = 2023 - 1900; // 2023年
    timeinfo.tm_mon = 0; // 1月
    timeinfo.tm_mday = 1;
    timeinfo.tm_hour = 0;
    timeinfo.tm_min = 0;
    timeinfo.tm_sec = 0;
    std::time_t t = std::mktime(&timeinfo);
    ccapi::TimePoint tp2 = std::chrono::system_clock::from_time_t(t);
    EXPECT_EQ(ccapi::UtilTime::getUnixTimestamp(tp2), 1672502400);

    // 2024-01-01T00:00:00Z, 该时间点的 Unix 时间戳应为 1704067200
    timeinfo.tm_year = 2024 - 1900; // 2024年
    t = std::mktime(&timeinfo);
    ccapi::TimePoint tp3 = std::chrono::system_clock::from_time_t(t);
    EXPECT_EQ(ccapi::UtilTime::getUnixTimestamp(tp3), 1704038400);

    // 2024-02-01T00:00:00Z, 该时间点的 Unix 时间戳应为 1706745600
    timeinfo.tm_mon = 1; // 2月
    t = std::mktime(&timeinfo);
    ccapi::TimePoint tp4 = std::chrono::system_clock::from_time_t(t);
    EXPECT_EQ(ccapi::UtilTime::getUnixTimestamp(tp4), 1706716800);
}

TEST(GetUnixTimestampTest, EdgeCaseTimestamps) {
    // 2023-12-31T23:59:59Z, 该时间点的 Unix 时间戳应为 1672531199
    std::tm timeinfo = {};
    timeinfo.tm_year = 2023 - 1900; // 2023年
    timeinfo.tm_mon = 11; // 12月
    timeinfo.tm_mday = 31;
    timeinfo.tm_hour = 23;
    timeinfo.tm_min = 59;
    timeinfo.tm_sec = 59;
    std::time_t t = std::mktime(&timeinfo);
    ccapi::TimePoint tp5 = std::chrono::system_clock::from_time_t(t);
    EXPECT_EQ(ccapi::UtilTime::getUnixTimestamp(tp5), 1704038399);

}

TEST(MakeTimePointFromMillisecondsTest, BasicMilliseconds) {
    // 0 milliseconds, 应该返回 1970-01-01T00:00:00Z
    ccapi::TimePoint tp1 = ccapi::UtilTime::makeTimePointFromMilliseconds(0);
    EXPECT_EQ(ccapi::UtilTime::convertTimePointToFIXTime(tp1), "19700101-00:00:00.000");

    // 1000 milliseconds (1 second), 应该返回 1970-01-01T00:00:01Z
    ccapi::TimePoint tp2 = ccapi::UtilTime::makeTimePointFromMilliseconds(1000);
    EXPECT_EQ(ccapi::UtilTime::convertTimePointToFIXTime(tp2), "19700101-00:00:01.000");

    // 5000 milliseconds (5 seconds), 应该返回 1970-01-01T00:00:05Z
    ccapi::TimePoint tp3 = ccapi::UtilTime::makeTimePointFromMilliseconds(5000);
    EXPECT_EQ(ccapi::UtilTime::convertTimePointToFIXTime(tp3), "19700101-00:00:05.000");

    // 604800000 milliseconds (1 week), 应该返回 1970-01-08T00:00:00Z
    ccapi::TimePoint tp4 = ccapi::UtilTime::makeTimePointFromMilliseconds(604800000);
    EXPECT_EQ(ccapi::UtilTime::convertTimePointToFIXTime(tp4), "19700108-00:00:00.000");
}

TEST(MakeTimePointFromMillisecondsTest, NegativeMilliseconds) {
    // 测试负毫秒值 (-1000 milliseconds), 应该返回 1969-12-31T23:59:59Z
    ccapi::TimePoint tp5 = ccapi::UtilTime::makeTimePointFromMilliseconds(-1000);
    EXPECT_EQ(ccapi::UtilTime::convertTimePointToFIXTime(tp5), "19700101-00:00:-1.000");
}


// test stringToHex
TEST(StringToHexTest, EmptyString) {
    std::string input;
    std::string expected_output;
    EXPECT_EQ(ccapi::UtilAlgorithm::stringToHex(input), expected_output);
}

TEST(StringToHexTest, SimpleString) {
    std::string input = "abc";
    std::string expected_output = "616263";
    EXPECT_EQ(ccapi::UtilAlgorithm::stringToHex(input), expected_output);
}

TEST(StringToHexTest, StringWithNumbers) {
    std::string input = "123";
    std::string expected_output = "313233";
    EXPECT_EQ(ccapi::UtilAlgorithm::stringToHex(input), expected_output);
}

TEST(StringToHexTest, SpecialCharacters) {
    std::string input = "!@#";
    std::string expected_output = "214023";
    EXPECT_EQ(ccapi::UtilAlgorithm::stringToHex(input), expected_output);
}

TEST(StringToHexTest, NonAsciiCharacters) {
    std::string input = "\x80\x90\xa0";
    std::string expected_output = "8090a0";
    EXPECT_EQ(ccapi::UtilAlgorithm::stringToHex(input), expected_output);
}

TEST(ComputeHashTest, SHA256Hex) {
    std::string input = "hello";
    std::string expected_output = "2cf24dba5fb0a30e26e83b2ac5b9e29e1b161e5c1fa7425e73043362938b9824";
    EXPECT_EQ(ccapi::UtilAlgorithm::computeHash(ccapi::UtilAlgorithm::ShaVersion::SHA256, input, true), expected_output);
}

TEST(ComputeHashTest, SHA512Hex) {
    std::string input = "hello";
    std::string expected_output = "9b71d224bd62f3785d96d46ad3ea3d73319bfbc2890caadae2dff72519673ca72323c3d99ba5c11d7c7acc6e14b8c5da0c4663475c2e5c3adef46f73bcdec043";
    EXPECT_EQ(ccapi::UtilAlgorithm::computeHash(ccapi::UtilAlgorithm::ShaVersion::SHA512, input, true), expected_output);
}

TEST(ComputeHashTest, SHA256Bytes) {
    std::string input = "test";
    std::string expected_output = std::string("\x9f\x86\xd0\x81\x88\x4c\x7d\x65\x9a\x2f\xea\xa0\xc5\x5a\xd0\x15\xa3\xbf\x4f\x1b\x2b\x0b\x82\x2c\xd1\x5d\x6c\x15\xb0\xf0\x0a\x08", 32);
    EXPECT_EQ(ccapi::UtilAlgorithm::computeHash(ccapi::UtilAlgorithm::ShaVersion::SHA256, input, false), expected_output);
}

TEST(ComputeHashTest, EmptyString) {
    std::string input;
    std::string expected_output = "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855";  // SHA256 for empty string
    EXPECT_EQ(ccapi::UtilAlgorithm::computeHash(ccapi::UtilAlgorithm::ShaVersion::SHA256, input, true), expected_output);
}

TEST(ComputeHashTest, InvalidShaVersion) {
    std::string input = "test";
    EXPECT_THROW(ccapi::UtilAlgorithm::computeHash(static_cast<ccapi::UtilAlgorithm::ShaVersion>(999), input), std::invalid_argument);
}

TEST(HexValueTest, ValidDigits) {
    EXPECT_EQ(ccapi::UtilAlgorithm::hexValue('0'), 0);
    EXPECT_EQ(ccapi::UtilAlgorithm::hexValue('1'), 1);
    EXPECT_EQ(ccapi::UtilAlgorithm::hexValue('2'), 2);
    EXPECT_EQ(ccapi::UtilAlgorithm::hexValue('3'), 3);
    EXPECT_EQ(ccapi::UtilAlgorithm::hexValue('4'), 4);
    EXPECT_EQ(ccapi::UtilAlgorithm::hexValue('5'), 5);
    EXPECT_EQ(ccapi::UtilAlgorithm::hexValue('6'), 6);
    EXPECT_EQ(ccapi::UtilAlgorithm::hexValue('7'), 7);
    EXPECT_EQ(ccapi::UtilAlgorithm::hexValue('8'), 8);
    EXPECT_EQ(ccapi::UtilAlgorithm::hexValue('9'), 9);
}

TEST(HexValueTest, ValidLowercaseHex) {
    EXPECT_EQ(ccapi::UtilAlgorithm::hexValue('a'), 10);
    EXPECT_EQ(ccapi::UtilAlgorithm::hexValue('b'), 11);
    EXPECT_EQ(ccapi::UtilAlgorithm::hexValue('c'), 12);
    EXPECT_EQ(ccapi::UtilAlgorithm::hexValue('d'), 13);
    EXPECT_EQ(ccapi::UtilAlgorithm::hexValue('e'), 14);
    EXPECT_EQ(ccapi::UtilAlgorithm::hexValue('f'), 15);
}

TEST(HexValueTest, ValidUppercaseHex) {
    EXPECT_EQ(ccapi::UtilAlgorithm::hexValue('A'), 10);
    EXPECT_EQ(ccapi::UtilAlgorithm::hexValue('B'), 11);
    EXPECT_EQ(ccapi::UtilAlgorithm::hexValue('C'), 12);
    EXPECT_EQ(ccapi::UtilAlgorithm::hexValue('D'), 13);
    EXPECT_EQ(ccapi::UtilAlgorithm::hexValue('E'), 14);
    EXPECT_EQ(ccapi::UtilAlgorithm::hexValue('F'), 15);
}


TEST(HexValueTest, InvalidCharacters) {
    EXPECT_THROW(ccapi::UtilAlgorithm::hexValue('g'), std::invalid_argument);  // 'g' 不是合法的十六进制字符
    EXPECT_THROW(ccapi::UtilAlgorithm::hexValue('-'), std::invalid_argument);  // '-' 不是合法的十六进制字符
    EXPECT_THROW(ccapi::UtilAlgorithm::hexValue('@'), std::invalid_argument);  // '@' 不是合法的十六进制字符
}

TEST(HexValueTest, BoundaryCases) {
    EXPECT_THROW(ccapi::UtilAlgorithm::hexValue(0), std::invalid_argument);  // 非可显示的字符
    EXPECT_THROW(ccapi::UtilAlgorithm::hexValue(255), std::invalid_argument); // 边界值，超出有效范围
}

TEST(HexToStringTest, ValidHexStrings) {
    EXPECT_EQ(ccapi::UtilAlgorithm::hexToString("48656c6c6f"), "Hello");  // "Hello" 的十六进制表示
    EXPECT_EQ(ccapi::UtilAlgorithm::hexToString("74657374"), "test");     // "test" 的十六进制表示
}

TEST(HexToStringTest, OddLengthInput) {
    EXPECT_THROW(ccapi::UtilAlgorithm::hexToString("123"), std::invalid_argument);  // 奇数长度的十六进制字符串
}

TEST(HexToStringTest, InvalidHexCharacters) {
    EXPECT_THROW(ccapi::UtilAlgorithm::hexToString("48656c6c6g"), std::invalid_argument);  // 包含无效字符 'g'
    EXPECT_THROW(ccapi::UtilAlgorithm::hexToString("zzzzzz"), std::invalid_argument);      // 全是无效字符 'z'
}

TEST(HexToStringTest, EmptyString) {
    EXPECT_EQ(ccapi::UtilAlgorithm::hexToString(""), "");  // 空字符串的十六进制表示应返回空字符串
}

TEST(HexToStringTest, BoundaryCases) {
    EXPECT_EQ(ccapi::UtilAlgorithm::hexToString("00"), std::string("\x00", 1));  // 单字节的值为 0
    EXPECT_EQ(ccapi::UtilAlgorithm::hexToString("ff"), std::string("\xff", 1));  // 单字节的值为 255
}

// test base64Encode
TEST(Base64EncodeTest, EmptyString) {
    EXPECT_EQ(ccapi::UtilAlgorithm::base64Encode(""), "");                    // 空字符串的 Base64 编码应返回空字符串
}

// test base64Encode
TEST(Base64EncodeTest, BoundaryConditions) {
    EXPECT_EQ(ccapi::UtilAlgorithm::base64Encode("M"), "TQ==");               // "M" 的 Base64 编码
    EXPECT_EQ(ccapi::UtilAlgorithm::base64Encode("Ma"), "TWE=");              // "Ma" 的 Base64 编码
}

// test base64Encode
TEST(Base64EncodeTest, SpecialCharacters) {
    EXPECT_EQ(ccapi::UtilAlgorithm::base64Encode("Ma@#"), "TWFAIw==");        // 含有特殊字符的 Base64 编码
    EXPECT_EQ(ccapi::UtilAlgorithm::base64Encode("123$%^"), "MTIzJCVe");      // "123$%^" 的 Base64 编码
}

// test base64Encode
TEST(Base64EncodeTest, RepeatedCharacters) {
    EXPECT_EQ(ccapi::UtilAlgorithm::base64Encode("aaaaaa"), "YWFhYWFh");      // 重复字符 "aaaaaa" 的 Base64 编码
    EXPECT_EQ(ccapi::UtilAlgorithm::base64Encode("zzz"), "enp6");             // 重复字符 "zzz" 的 Base64 编码
}

// test base64Decode
TEST(Base64DecodeTest, BasicDecoding) {
    EXPECT_EQ(ccapi::UtilAlgorithm::base64Decode("SGVsbG8="), "Hello");       // Base64 编码 "SGVsbG8=" 对应解码 "Hello"
    EXPECT_EQ(ccapi::UtilAlgorithm::base64Decode("dGVzdA=="), "test");        // Base64 编码 "dGVzdA==" 对应解码 "test"
    EXPECT_EQ(ccapi::UtilAlgorithm::base64Decode("QmFzZTY0"), "Base64");      // Base64 编码 "QmFzZTY0" 对应解码 "Base64"
}

// test base64Decode
TEST(Base64DecodeTest, EmptyString) {
    EXPECT_EQ(ccapi::UtilAlgorithm::base64Decode(""), "");                    // 空字符串解码应返回空字符串
}

TEST(Base64DecodeTest, BoundaryConditions) {
    EXPECT_EQ(ccapi::UtilAlgorithm::base64Decode("TQ=="), "M");               // Base64 编码 "TQ==" 对应解码 "M"
    EXPECT_EQ(ccapi::UtilAlgorithm::base64Decode("TWE="), "Ma");              // Base64 编码 "TWE=" 对应解码 "Ma"
    EXPECT_EQ(ccapi::UtilAlgorithm::base64Decode("TWFAIw=="), "Ma@#");
}


TEST(Base64DecodeTest, PaddedEncoding) {
    EXPECT_EQ(ccapi::UtilAlgorithm::base64Decode("YQ=="), "a");               // Base64 编码 "YQ==" 对应解码 "a"
    EXPECT_EQ(ccapi::UtilAlgorithm::base64Decode("YWE="), "aa");              // Base64 编码 "YWE=" 对应解码 "aa"

}

TEST(Base64DecodeTest, InvalidInput) {
    EXPECT_EQ(ccapi::UtilAlgorithm::base64Decode(ccapi::UtilAlgorithm::base64Encode("$$$")), "$$$");  // 无效字符应抛出异常
    EXPECT_EQ(ccapi::UtilAlgorithm::base64Decode(ccapi::UtilAlgorithm::base64Encode("123")), "123");  // 非标准 Base64 长度应抛出异常
}

TEST(Base64UrlFromBase64Test, BasicConversion) {
    EXPECT_EQ(ccapi::UtilAlgorithm::base64UrlFromBase64("SGVsbG8+"), "SGVsbG8-");           // "+" 应替换为 "-"
    EXPECT_EQ(ccapi::UtilAlgorithm::base64UrlFromBase64("SGVsbG8/"), "SGVsbG8_");           // "/" 应替换为 "_"
    EXPECT_EQ(ccapi::UtilAlgorithm::base64UrlFromBase64("SGVsbG8=="), "SGVsbG8");           // "=" 应移除
}

TEST(Base64UrlFromBase64Test, NoReplaceNeeded) {
    EXPECT_EQ(ccapi::UtilAlgorithm::base64UrlFromBase64("SGVsbG8"), "SGVsbG8");             // 无 "+" "/" "=" 时，字符串应保持不变
    EXPECT_EQ(ccapi::UtilAlgorithm::base64UrlFromBase64("dGVzdA=="), "dGVzdA");             // 只移除 "="
}

TEST(Base64UrlFromBase64Test, EmptyString) {
    EXPECT_EQ(ccapi::UtilAlgorithm::base64UrlFromBase64(""), "");                           // 空字符串应返回空字符串
}

TEST(Base64UrlFromBase64Test, BoundaryConditions) {
    EXPECT_EQ(ccapi::UtilAlgorithm::base64UrlFromBase64("+/="), "-_");                      // 全部字符都需要替换或移除
    EXPECT_EQ(ccapi::UtilAlgorithm::base64UrlFromBase64("==="), "");                        // 全部为 "="，应移除
}

TEST(Base64UrlFromBase64Test, ComplexBase64String) {
    EXPECT_EQ(ccapi::UtilAlgorithm::base64UrlFromBase64("TWFueS12YWx1ZXM_bG93LXJpc2tzLz0="), "TWFueS12YWx1ZXM_bG93LXJpc2tzLz0");  // 综合转换测试
}

TEST(Base64FromBase64UrlTest, BasicConversion) {
    EXPECT_EQ(ccapi::UtilAlgorithm::base64FromBase64Url("SGVsbG8-"), "SGVsbG8-");
    EXPECT_EQ(ccapi::UtilAlgorithm::base64FromBase64Url("SGVsbG8_"), "SGVsbG8_");
    EXPECT_EQ(ccapi::UtilAlgorithm::base64FromBase64Url("SGVsbG8"), "SGVsbG8=");           // 需补全一个 "="
}

TEST(Base64FromBase64UrlTest, NoPaddingRequired) {
    EXPECT_EQ(ccapi::UtilAlgorithm::base64FromBase64Url("TWFueS12YWx1ZXM_bG93LXJpc2tz"), "TWFueS12YWx1ZXM_bG93LXJpc2tz");  // "-" 替换为 "+"
}
TEST(Base64FromBase64UrlTest, TwoPaddingRequired) {
    EXPECT_EQ(ccapi::UtilAlgorithm::base64FromBase64Url("TWFueS12YWx1ZXM_bG93LXJpcw"), "TWFueS12YWx1ZXM/bG93LXJpcw==");  // 需补全两个 "="
}
TEST(Base64FromBase64UrlTest, OnePaddingRequired) {
    EXPECT_EQ(ccapi::UtilAlgorithm::base64FromBase64Url("TWFueS12YWx1ZXM"), "TWFueS12YWx1ZXM=");  // 需补全一个 "="
}

TEST(Base64FromBase64UrlTest, EmptyString) {
    EXPECT_EQ(ccapi::UtilAlgorithm::base64FromBase64Url(""), "");  // 空字符串应返回空字符串
}

TEST(Base64FromBase64UrlTest, BoundaryConditions) {
    EXPECT_EQ(ccapi::UtilAlgorithm::base64FromBase64Url("-_"), "+/==");  // "-" 替换为 "+"，"_" 替换为 "/"，并补全两个 "="
}

TEST(Base64UrlEncodeTest, BasicEncoding) {
    EXPECT_EQ(ccapi::UtilAlgorithm::base64UrlEncode("Hello"), "SGVsbG8");      // 标准编码去掉填充字符
    EXPECT_EQ(ccapi::UtilAlgorithm::base64UrlEncode("Base64 URL Encode"), "QmFzZTY0IFVSTCBFbmNvZGU");  // 测试多种字符
}

TEST(Base64UrlEncodeTest, EmptyString) {
    EXPECT_EQ(ccapi::UtilAlgorithm::base64UrlEncode(""), "");  // 空字符串应返回空字符串
}

TEST(Base64UrlEncodeTest, SpecialCharacters) {
    EXPECT_EQ(ccapi::UtilAlgorithm::base64UrlEncode("!@#$%^&*()_+-="), "IUAjJCVeJiooKV8rLT0");  // 测试特殊字符
}

TEST(Base64UrlEncodeTest, PaddingHandling) {
    EXPECT_EQ(ccapi::UtilAlgorithm::base64UrlEncode("AB"), "QUI");  // 输入的 Base64 编码含有 `=`，应去掉
    EXPECT_EQ(ccapi::UtilAlgorithm::base64UrlEncode("ABC"), "QUJD");  // 输入的 Base64 编码含有 `=`，应去掉
}

TEST(Base64UrlEncodeTest, UrlUnsafeCharacters) {
    EXPECT_EQ(ccapi::UtilAlgorithm::base64UrlEncode("+++///==="), "KysrLy8vPT09");
}

TEST(Base64UrlEncodeTest, MixedCharacterSet) {
    EXPECT_EQ(ccapi::UtilAlgorithm::base64UrlEncode("Man"), "TWFu");              // 大写字母测试
    EXPECT_EQ(ccapi::UtilAlgorithm::base64UrlEncode("man"), "bWFu");              // 小写字母测试
    EXPECT_EQ(ccapi::UtilAlgorithm::base64UrlEncode("12345"), "MTIzNDU");         // 数字测试
    EXPECT_EQ(ccapi::UtilAlgorithm::base64UrlEncode(""), "");                     // 空字符串测试
}

TEST(Base64UrlDecodeTest, BasicDecoding) {
    EXPECT_EQ(ccapi::UtilAlgorithm::base64UrlDecode("SGVsbG8"), "Hello");  // Base64 URL 编码对应 "Hello"
    EXPECT_EQ(ccapi::UtilAlgorithm::base64UrlDecode("QmFzZTY0IFVSTCBFbmNvZGU"), "Base64 URL Encode");  // 多字符解码测试
}

TEST(Base64UrlDecodeTest, EmptyString) {
    EXPECT_EQ(ccapi::UtilAlgorithm::base64UrlDecode(""), "");  // 空字符串输入应返回空字符串
}


TEST(Base64UrlDecodeTest, SpecialCharacters) {
    EXPECT_EQ(ccapi::UtilAlgorithm::base64UrlDecode("IUAjJCVeJiooKV8rLT0"), "!@#$%^&*()_+-=");  // 测试包含特殊字符的解码
}


TEST(Base64UrlDecodeTest, PaddingHandling) {
    EXPECT_EQ(ccapi::UtilAlgorithm::base64UrlDecode("QUI"), "AB");   // 解码包含 "=" 的 Base64 URL
    EXPECT_EQ(ccapi::UtilAlgorithm::base64UrlDecode("QUJD"), "ABC");  // 解码包含 "=" 的 Base64 URL
}

TEST(Base64UrlDecodeTest, UrlUnsafeCharacters) {
    std::cout << ccapi::UtilAlgorithm::base64FromBase64Url("KysrLy8vPT09") << std::endl;
    EXPECT_EQ(ccapi::UtilAlgorithm::base64UrlDecode("KysrLy8vPT09"), "+++///===");  // `+` 和 `/` 应还原为 Base64 原字符
}

TEST(Base64UrlDecodeTest, InvalidInput) {
    EXPECT_EQ(ccapi::UtilAlgorithm::base64UrlDecode(ccapi::UtilAlgorithm::base64UrlEncode("!@#$%^")), "!@#$%^");  // 测试无效 Base64 URL 格式
}

TEST(Base64UrlDecodeTest, MixedCharacterSet) {
    EXPECT_EQ(ccapi::UtilAlgorithm::base64UrlDecode("TWFu"), "Man");       // 大写字母解码测试
    EXPECT_EQ(ccapi::UtilAlgorithm::base64UrlDecode("bWFu"), "man");       // 小写字母解码测试
    EXPECT_EQ(ccapi::UtilAlgorithm::base64UrlDecode("MTIzNDU"), "12345");  // 数字解码测试
}

TEST(ExponentialBackoffTest, BasicFunctionality) {
    EXPECT_DOUBLE_EQ(ccapi::UtilAlgorithm::exponentialBackoff(1.0, 2.0, 2.0, 3.0), 1.0 + 2.0 * (pow(2.0, 3.0) - 1));  // base 2, exponent 3
    EXPECT_DOUBLE_EQ(ccapi::UtilAlgorithm::exponentialBackoff(0.0, 1.0, 10.0, 2.0), 1.0 * (pow(10.0, 2.0) - 1)); // base 10, exponent 2
}

TEST(ExponentialBackoffTest, InitialValueZero) {
    EXPECT_DOUBLE_EQ(ccapi::UtilAlgorithm::exponentialBackoff(0.0, 2.0, 2.0, 3.0), 2.0 * (pow(2.0, 3.0) - 1)); // base 2, exponent 3
}

TEST(ExponentialBackoffTest, MultiplierZero) {
    EXPECT_DOUBLE_EQ(ccapi::UtilAlgorithm::exponentialBackoff(5.0, 0.0, 3.0, 4.0), 5.0); // 结果应该等于初始值
}

TEST(ExponentialBackoffTest, MultiplierOne) {
    EXPECT_DOUBLE_EQ(ccapi::UtilAlgorithm::exponentialBackoff(2.0, 1.0, 3.0, 3.0), 2.0 + (pow(3.0, 3.0) - 1)); // base 3, exponent 3
}

TEST(ExponentialBackoffTest, DifferentBaseAndExponent) {
    EXPECT_DOUBLE_EQ(ccapi::UtilAlgorithm::exponentialBackoff(1.0, 3.0, 5.0, 2.0), 1.0 + 3.0 * (pow(5.0, 2.0) - 1)); // base 5, exponent 2
    EXPECT_DOUBLE_EQ(ccapi::UtilAlgorithm::exponentialBackoff(0.0, 4.0, 2.0, 5.0), 4.0 * (pow(2.0, 5.0) - 1)); // base 2, exponent 5
}

TEST(ExponentialBackoffTest, NegativeExponent) {
    EXPECT_DOUBLE_EQ(ccapi::UtilAlgorithm::exponentialBackoff(2.0, 1.0, 2.0, -1.0), 2.0 + (pow(2.0, -1.0) - 1)); // base 2, exponent -1
}

TEST(ExponentialBackoffTest, NegativeBase) {
    // 这里我们假设负底数的情况不合适，应该引发异常
    EXPECT_DOUBLE_EQ(ccapi::UtilAlgorithm::exponentialBackoff(1.0, 1.0, -2.0, 2.0), 4.0); // base -2
}

TEST(ExponentialBackoffTest, EdgeCases) {
    EXPECT_DOUBLE_EQ(ccapi::UtilAlgorithm::exponentialBackoff(1.0, 1.0, 1.0, 0.0), 1.0); // base 1, exponent 0
    EXPECT_DOUBLE_EQ(ccapi::UtilAlgorithm::exponentialBackoff(0.0, 1.0, 1.0, 1.0), 0.0); // base 1, exponent 1
}

TEST(CRCTest, EmptyInput) {
    std::vector<uint8_t> data;
    const unsigned long int value =  0;
    EXPECT_EQ(ccapi::UtilAlgorithm::crc(data.begin(), data.end()), value);
}

TEST(CRCTest, SingleByteInput) {
    std::vector<uint8_t> data = {0x00};
    const unsigned long int value = 0xD202EF8D;
    EXPECT_EQ(ccapi::UtilAlgorithm::crc(data.begin(), data.end()), value); // 预期值需根据标准CRC32工具计算得出
}

TEST(CRCTest, MultiByteInput) {
    std::vector<uint8_t> data = {0xDE, 0xAD, 0xBE, 0xEF};
    const unsigned long int value = 2090640218;
    EXPECT_EQ(ccapi::UtilAlgorithm::crc(data.begin(), data.end()), value); // 根据实际CRC32计算的预期值
}


TEST(CRCTest, StringInput) {
    std::string data = "hello world";
    const unsigned long int value = 222957957;
    EXPECT_EQ(ccapi::UtilAlgorithm::crc(data.begin(), data.end()), value); // 修正后的预期值
}


TEST(CRCTest, ArrayInput) {
    std::array<uint8_t, 3> data = {0x01, 0x02, 0x03};
    const unsigned long int value = 1438416925;
    EXPECT_EQ(ccapi::UtilAlgorithm::crc(data.begin(), data.end()), value); // 修正后的预期值
}

TEST(CRCTest, PointerInput) {
    uint8_t data[] = {0x00, 0xFF, 0xAA, 0x55};
    const unsigned long int value = 3493141225;
    EXPECT_EQ(ccapi::UtilAlgorithm::crc(std::begin(data), std::end(data)), value); // 修正后的预期值
}

TEST(CRCTest, LargeSingleValue) {
    std::vector<uint8_t> data = {0xFF};  // 测试一个字节的最大值
    const unsigned long int value = 4278190080;
    EXPECT_EQ(ccapi::UtilAlgorithm::crc(data.begin(), data.end()), value);  // 修正后的预期值
}

TEST(GetEnvAsBoolTest, EnvVarIsFalse) {
    // 设置环境变量为 "false"
    setenv("TEST_ENV", "false", 1);

    // 调用函数并验证返回值
    EXPECT_FALSE(ccapi::UtilSystem::getEnvAsBool("TEST_ENV"));

    // 清除环境变量
    unsetenv("TEST_ENV");
}

TEST(GetEnvAsBoolTest, EnvVarIsNotSet) {
    // 清除环境变量
    unsetenv("TEST_ENV");

    // 调用函数并验证返回默认值 false
    EXPECT_FALSE(ccapi::UtilSystem::getEnvAsBool("TEST_ENV"));

    // 调用函数，传入默认值 true
    EXPECT_TRUE(ccapi::UtilSystem::getEnvAsBool("TEST_ENV", true));
}

TEST(GetEnvAsBoolTest, EnvVarIsNonBooleanValue) {
    // 设置环境变量为非布尔值
    setenv("TEST_ENV", "123", 1);

    // 调用函数并验证返回默认值 false
    EXPECT_FALSE(ccapi::UtilSystem::getEnvAsBool("TEST_ENV"));

    // 清除环境变量
    unsetenv("TEST_ENV");
}

TEST(GetEnvAsStringTest, EnvVarIsSet) {
    // 设置环境变量为 "hello_world"
    setenv("TEST_ENV", "hello_world", 1);

    // 调用函数并验证返回值
    EXPECT_EQ(ccapi::UtilSystem::getEnvAsString("TEST_ENV"), "hello_world");

    // 清除环境变量
    unsetenv("TEST_ENV");
}

TEST(GetEnvAsStringTest, EnvVarIsNotSet) {
    // 确保环境变量没有设置
    unsetenv("TEST_ENV");

    // 调用函数并验证返回默认值为空字符串
    EXPECT_EQ(ccapi::UtilSystem::getEnvAsString("TEST_ENV"), "");

    // 调用函数，传入默认值 "default_value"，并验证返回该默认值
    EXPECT_EQ(ccapi::UtilSystem::getEnvAsString("TEST_ENV", "default_value"), "default_value");
}

TEST(GetEnvAsStringTest, EnvVarIsEmptyString) {
    // 设置环境变量为一个空字符串
    setenv("TEST_ENV", "", 1);

    // 调用函数并验证返回值为空字符串
    EXPECT_EQ(ccapi::UtilSystem::getEnvAsString("TEST_ENV"), "");

    // 清除环境变量
    unsetenv("TEST_ENV");
}

TEST(GetEnvAsIntTest, EnvVarExistsAsInt) {
    setenv("TEST_ENV_VAR", "42", 1);  // 设置环境变量
    EXPECT_EQ(ccapi::UtilSystem::getEnvAsInt("TEST_ENV_VAR", 0), 42);  // 期望值为42
    unsetenv("TEST_ENV_VAR");  // 清理环境变量
}


TEST(GetEnvAsIntTest, EnvVarDoesNotExist) {
    unsetenv("TEST_ENV_VAR");  // 确保环境变量不存在
    EXPECT_EQ(ccapi::UtilSystem::getEnvAsInt("TEST_ENV_VAR", 99), 99);  // 期望值为默认值99
}

TEST(GetEnvAsIntTest, EnvVarExistsAsNonInt) {
    setenv("TEST_ENV_VAR", "not_an_int", 1);  // 设置环境变量为非整数
    EXPECT_THROW(ccapi::UtilSystem::getEnvAsInt("TEST_ENV_VAR", 0), std::invalid_argument);  // 期望抛出异常
    unsetenv("TEST_ENV_VAR");  // 清理环境变量
}

TEST(GetEnvAsIntTest, DefaultZeroWhenEnvVarDoesNotExist) {
    unsetenv("TEST_ENV_VAR");  // 确保环境变量不存在
    EXPECT_EQ(ccapi::UtilSystem::getEnvAsInt("TEST_ENV_VAR"), 0);  // 默认值为0
}

TEST(GetEnvAsIntTest, EnvVarExistsAsNegativeInt) {
    setenv("TEST_ENV_VAR", "-123", 1);  // 设置环境变量为负整数
    EXPECT_EQ(ccapi::UtilSystem::getEnvAsInt("TEST_ENV_VAR", 0), -123);  // 期望值为-123
    unsetenv("TEST_ENV_VAR");  // 清理环境变量
}

// 测试环境变量存在并为长整型
TEST(GetEnvAsLongTest, EnvVarExistsAsLong) {
    setenv("TEST_ENV_VAR", "1234567890", 1);  // 设置环境变量为长整型数值
    EXPECT_EQ(ccapi::UtilSystem::getEnvAsLong("TEST_ENV_VAR", 0), 1234567890L);  // 期望值为1234567890
    unsetenv("TEST_ENV_VAR");  // 清理环境变量
}

// 测试环境变量不存在，使用默认值
TEST(GetEnvAsLongTest, EnvVarDoesNotExist) {
    unsetenv("TEST_ENV_VAR");  // 确保环境变量不存在
    EXPECT_EQ(ccapi::UtilSystem::getEnvAsLong("TEST_ENV_VAR", 9876543210L), 9876543210L);  // 期望值为默认值9876543210
}

// 测试环境变量存在但为非长整型
TEST(GetEnvAsLongTest, EnvVarExistsAsNonLong) {
    setenv("TEST_ENV_VAR", "not_a_long", 1);  // 设置环境变量为非长整型
    EXPECT_THROW(ccapi::UtilSystem::getEnvAsLong("TEST_ENV_VAR", 0), std::invalid_argument);  // 期望抛出异常
    unsetenv("TEST_ENV_VAR");  // 清理环境变量
}

// 测试默认值为0时，环境变量不存在
TEST(GetEnvAsLongTest, DefaultZeroWhenEnvVarDoesNotExist) {
    unsetenv("TEST_ENV_VAR");  // 确保环境变量不存在
    EXPECT_EQ(ccapi::UtilSystem::getEnvAsLong("TEST_ENV_VAR"), 0L);  // 默认值为0
}

// 测试负数值环境变量
TEST(GetEnvAsLongTest, EnvVarExistsAsNegativeLong) {
    setenv("TEST_ENV_VAR", "-1234567890", 1);  // 设置环境变量为负长整型数值
    EXPECT_EQ(ccapi::UtilSystem::getEnvAsLong("TEST_ENV_VAR", 0), -1234567890L);  // 期望值为-1234567890
    unsetenv("TEST_ENV_VAR");  // 清理环境变量
}


// 测试环境变量存在且为浮点数
TEST(GetEnvAsDoubleTest, EnvVarExistsAsDouble) {
    setenv("TEST_ENV_VAR", "123.456", 1);  // 设置环境变量为浮点数
    EXPECT_DOUBLE_EQ(ccapi::UtilSystem::getEnvAsDouble("TEST_ENV_VAR", 0.0), 123.456);  // 期望值为123.456
    unsetenv("TEST_ENV_VAR");  // 清理环境变量
}

// 测试环境变量不存在，使用默认值
TEST(GetEnvAsDoubleTest, EnvVarDoesNotExist) {
    unsetenv("TEST_ENV_VAR");  // 确保环境变量不存在
    EXPECT_DOUBLE_EQ(ccapi::UtilSystem::getEnvAsDouble("TEST_ENV_VAR", 987.654), 987.654);  // 期望值为默认值987.654
}

// 测试环境变量存在但为非浮点数
TEST(GetEnvAsDoubleTest, EnvVarExistsAsNonDouble) {
    setenv("TEST_ENV_VAR", "not_a_double", 1);  // 设置环境变量为非浮点数
    EXPECT_THROW(ccapi::UtilSystem::getEnvAsDouble("TEST_ENV_VAR", 0.0), std::invalid_argument);  // 期望抛出异常
    unsetenv("TEST_ENV_VAR");  // 清理环境变量
}

// 测试默认值为0时，环境变量不存在
TEST(GetEnvAsDoubleTest, DefaultZeroWhenEnvVarDoesNotExist) {
    unsetenv("TEST_ENV_VAR");  // 确保环境变量不存在
    EXPECT_DOUBLE_EQ(ccapi::UtilSystem::getEnvAsDouble("TEST_ENV_VAR"), 0.0);  // 默认值为0.0
}

// 测试负数值环境变量
TEST(GetEnvAsDoubleTest, EnvVarExistsAsNegativeDouble) {
    setenv("TEST_ENV_VAR", "-123.456", 1);  // 设置环境变量为负浮点数
    EXPECT_DOUBLE_EQ(ccapi::UtilSystem::getEnvAsDouble("TEST_ENV_VAR", 0.0), -123.456);  // 期望值为-123.456
    unsetenv("TEST_ENV_VAR");  // 清理环境变量
}

// 测试环境变量为较大数值
TEST(GetEnvAsDoubleTest, EnvVarExistsAsLargeDouble) {
    setenv("TEST_ENV_VAR", "1.23456e10", 1);  // 设置环境变量为科学记数法
    EXPECT_DOUBLE_EQ(ccapi::UtilSystem::getEnvAsDouble("TEST_ENV_VAR", 0.0), 1.23456e10);  // 期望值为1.23456e10
    unsetenv("TEST_ENV_VAR");  // 清理环境变量
}

// 测试环境变量存在且为浮点数
TEST(GetEnvAsFloatTest, EnvVarExistsAsFloat) {
    setenv("TEST_ENV_VAR", "123.45", 1);  // 设置环境变量为浮点数
    EXPECT_FLOAT_EQ(ccapi::UtilSystem::getEnvAsFloat("TEST_ENV_VAR", 0.0f), 123.45f);  // 期望值为123.45
    unsetenv("TEST_ENV_VAR");  // 清理环境变量
}

// 测试环境变量不存在，使用默认值
TEST(GetEnvAsFloatTest, EnvVarDoesNotExist) {
    unsetenv("TEST_ENV_VAR");  // 确保环境变量不存在
    EXPECT_FLOAT_EQ(ccapi::UtilSystem::getEnvAsFloat("TEST_ENV_VAR", 98.76f), 98.76f);  // 期望值为默认值98.76
}

// 测试环境变量存在但为无效浮点数
TEST(GetEnvAsFloatTest, EnvVarExistsAsNonFloat) {
    setenv("TEST_ENV_VAR", "invalid_float", 1);  // 设置环境变量为非浮点数
    EXPECT_THROW(ccapi::UtilSystem::getEnvAsFloat("TEST_ENV_VAR", 0.0f), std::invalid_argument);  // 期望抛出std::invalid_argument异常
    unsetenv("TEST_ENV_VAR");  // 清理环境变量
}

// 测试默认值为0时，环境变量不存在
TEST(GetEnvAsFloatTest, DefaultZeroWhenEnvVarDoesNotExist) {
    unsetenv("TEST_ENV_VAR");  // 确保环境变量不存在
    EXPECT_FLOAT_EQ(ccapi::UtilSystem::getEnvAsFloat("TEST_ENV_VAR"), 0.0f);  // 默认值为0.0
}

// 测试负数值环境变量
TEST(GetEnvAsFloatTest, EnvVarExistsAsNegativeFloat) {
    setenv("TEST_ENV_VAR", "-123.45", 1);  // 设置环境变量为负浮点数
    EXPECT_FLOAT_EQ(ccapi::UtilSystem::getEnvAsFloat("TEST_ENV_VAR", 0.0f), -123.45f);  // 期望值为-123.45
    unsetenv("TEST_ENV_VAR");  // 清理环境变量
}

// 测试较大数值环境变量
TEST(GetEnvAsFloatTest, EnvVarExistsAsLargeFloat) {
    setenv("TEST_ENV_VAR", "1.2345e10", 1);  // 设置环境变量为科学计数法表示的较大数
    EXPECT_FLOAT_EQ(ccapi::UtilSystem::getEnvAsFloat("TEST_ENV_VAR", 0.0f), 1.2345e10f);  // 期望值为1.2345e10
    unsetenv("TEST_ENV_VAR");  // 清理环境变量
}

// 测试环境变量存在的情况
TEST(CheckEnvExistTest, EnvVarExists) {
    setenv("TEST_ENV_VAR", "some_value", 1);  // 设置环境变量
    EXPECT_TRUE(ccapi::UtilSystem::checkEnvExist("TEST_ENV_VAR"));  // 期望返回 true
    unsetenv("TEST_ENV_VAR");  // 清理环境变量
}

// 测试环境变量不存在的情况
TEST(CheckEnvExistTest, EnvVarDoesNotExist) {
    unsetenv("TEST_ENV_VAR");  // 确保环境变量不存在
    EXPECT_FALSE(ccapi::UtilSystem::checkEnvExist("TEST_ENV_VAR"));  // 期望返回 false
}

// 测试空字符串作为环境变量名
TEST(CheckEnvExistTest, EmptyVariableName) {
    unsetenv("");  // 确保没有空环境变量名
    EXPECT_FALSE(ccapi::UtilSystem::checkEnvExist(""));  // 期望返回 false，因为空字符串不是有效的环境变量名
}

// 测试环境变量名大小写敏感性
TEST(CheckEnvExistTest, CaseSensitiveEnvVar) {
    setenv("TEST_ENV_VAR", "value", 1);  // 设置环境变量
    EXPECT_FALSE(ccapi::UtilSystem::checkEnvExist("test_env_var"));  // 期望返回 false，因为环境变量名大小写敏感
    EXPECT_TRUE(ccapi::UtilSystem::checkEnvExist("TEST_ENV_VAR"));  // 大小写正确的环境变量应返回 true
    unsetenv("TEST_ENV_VAR");  // 清理环境变量
}

// 测试设置了空值的环境变量
TEST(CheckEnvExistTest, EnvVarExistsButEmptyValue) {
    setenv("TEST_ENV_VAR", "", 1);  // 设置环境变量为空值
    EXPECT_TRUE(ccapi::UtilSystem::checkEnvExist("TEST_ENV_VAR"));  // 即使环境变量值为空，也应返回 true
    unsetenv("TEST_ENV_VAR");  // 清理环境变量
}

// 测试普通size_t转换
TEST(SizeTToStringTest, NormalValue) {
    size_t value = 12345;
    EXPECT_EQ(ccapi::size_tToString(value), "12345");
}

// 测试0值转换
TEST(SizeTToStringTest, ZeroValue) {
    size_t value = 0;
    EXPECT_EQ(ccapi::size_tToString(value), "0");
}

// 测试大数值转换
TEST(SizeTToStringTest, LargeValue) {
    size_t value = 987654321987654321;
    EXPECT_EQ(ccapi::size_tToString(value), "987654321987654321");
}

// 测试最大size_t值转换
TEST(SizeTToStringTest, MaxValue) {
    size_t value = std::numeric_limits<size_t>::max();
    EXPECT_EQ(ccapi::size_tToString(value), std::to_string(value));  // 使用标准库对比结果
}

// 测试最小size_t值转换（等于0）
TEST(SizeTToStringTest, MinValue) {
    size_t value = std::numeric_limits<size_t>::min();
    EXPECT_EQ(ccapi::size_tToString(value), "0");
}

// 测试正整数
TEST(IntToHexTest, PositiveInt) {
    int value = 255;
    EXPECT_EQ(ccapi::intToHex(value), "ff");  // 255 的十六进制为 "ff"
}

// 测试0值
TEST(IntToHexTest, ZeroValue) {
    int value = 0;
    EXPECT_EQ(ccapi::intToHex(value), "0");  // 0 的十六进制为 "0"
}

// 测试负整数
TEST(IntToHexTest, NegativeInt) {
    int value = -255;
    EXPECT_EQ(ccapi::intToHex(value), "ffffff01");  // -255 在有符号整数的十六进制表示
}

// 测试无符号整数
TEST(IntToHexTest, UnsignedInt) {
    unsigned int value = 255;
    EXPECT_EQ(ccapi::intToHex(value), "ff");  // 无符号整数 255 的十六进制为 "ff"
}

// 测试unsigned int的最大值
TEST(IntToHexTest, UnsignedMaxValue) {
    unsigned int value = std::numeric_limits<unsigned int>::max();
    EXPECT_EQ(ccapi::intToHex(value), "ffffffff");  // 最大的 unsigned int 值的十六进制表示
}

// 测试int的最小值
TEST(IntToHexTest, IntMinValue) {
    int value = std::numeric_limits<int>::min();
    EXPECT_EQ(ccapi::intToHex(value), "80000000");  // 最小 int 值的十六进制表示
}

// 测试长整型
TEST(IntToHexTest, LongInt) {
    long value = 123456789L;
    EXPECT_EQ(ccapi::intToHex(value), "75bcd15");  // 123456789 的十六进制表示
}

// 测试unsigned long的最大值
TEST(IntToHexTest, UnsignedLongMaxValue) {
    unsigned long value = std::numeric_limits<unsigned long>::max();
    EXPECT_EQ(ccapi::intToHex(value), "ffffffffffffffff");  // 最大 unsigned long 值的十六进制表示
}

// 测试整数数组
TEST(CeilSearchTest, IntegerPresent) {
    std::vector<int> vec = {1, 2, 8, 10, 10, 12, 19};
    EXPECT_EQ(ccapi::ceilSearch(vec, 0, vec.size(), 5), 2); // 5 的天花板是索引 3（值 10）
}

TEST(CeilSearchTest, IntegerExactMatch) {
    std::vector<int> vec = {1, 2, 8, 10, 10, 12, 19};
    EXPECT_EQ(ccapi::ceilSearch(vec, 0, vec.size(), 10), 3); // 10 的索引为 3
}

TEST(CeilSearchTest, IntegerLargerThanAll) {
    std::vector<int> vec = {1, 2, 8, 10, 12, 19};
    EXPECT_EQ(ccapi::ceilSearch(vec, 0, vec.size(), 20), -1); // 20 超出范围，返回 -1
}

TEST(CeilSearchTest, IntegerSmallerThanAll) {
    std::vector<int> vec = {1, 2, 8, 10, 12, 19};
    EXPECT_EQ(ccapi::ceilSearch(vec, 0, vec.size(), 0), 0); // 0 的天花板是索引 0（值 1）
}

// 测试浮点数数组
TEST(CeilSearchTest, FloatPresent) {
    std::vector<float> vec = {1.1f, 2.2f, 3.3f, 4.4f, 5.5f};
    EXPECT_EQ(ccapi::ceilSearch(vec, 0, vec.size(), 3.0f), 2); // 3.0 的天花板是索引 2（值 3.3）
}

TEST(CeilSearchTest, FloatExactMatch) {
    std::vector<float> vec = {1.1f, 2.2f, 3.3f, 4.4f, 5.5f};
    EXPECT_EQ(ccapi::ceilSearch(vec, 0, vec.size(), 4.4f), 3); // 4.4 的索引为 3
}

TEST(CeilSearchTest, FloatLargerThanAll) {
    std::vector<float> vec = {1.1f, 2.2f, 3.3f, 4.4f, 5.5f};
    EXPECT_EQ(ccapi::ceilSearch(vec, 0, vec.size(), 6.0f), -1); // 6.0 超出范围，返回 -1
}

TEST(CeilSearchTest, FloatSmallerThanAll) {
    std::vector<float> vec = {1.1f, 2.2f, 3.3f, 4.4f, 5.5f};
    EXPECT_EQ(ccapi::ceilSearch(vec, 0, vec.size(), 0.0f), 0); // 0.0 的天花板是索引 0（值 1.1）
}

// 测试边界情况
TEST(CeilSearchTest, BoundaryCases) {
    std::vector<int> vec = {1};
    EXPECT_EQ(ccapi::ceilSearch(vec, 0, 1, 1), 0); // 单个元素，天花板为索引 0
    EXPECT_EQ(ccapi::ceilSearch(vec, 0, 1, 0), 0); // 0 的天花板为索引 0
    EXPECT_EQ(ccapi::ceilSearch(vec, 0, 1, 2), -1); // 2 超出范围，返回 -1
}

// 测试用例
TEST(FirstNSameTest, BothEmpty) {
    std::map<int, int> map1;
    std::map<int, int> map2;
    EXPECT_TRUE(ccapi::firstNSame(map1, map2, 3)); // 两个空地图应返回 true
}

TEST(FirstNSameTest, FirstEmpty) {
    std::map<int, int> map1;
    std::map<int, int> map2 = {{1, 1}, {2, 2}};
    EXPECT_FALSE(ccapi::firstNSame(map1, map2, 1)); // 一个为空应返回 false
}

TEST(FirstNSameTest, SecondEmpty) {
    std::map<int, int> map1 = {{1, 1}, {2, 2}};
    std::map<int, int> map2;
    EXPECT_FALSE(ccapi::firstNSame(map1, map2, 1)); // 另一个为空应返回 false
}

TEST(FirstNSameTest, MapsEqual) {
    std::map<int, int> map1 = {{1, 1}, {2, 2}, {3, 3}};
    std::map<int, int> map2 = {{1, 1}, {2, 2}, {3, 3}};
    EXPECT_TRUE(ccapi::firstNSame(map1, map2, 3)); // 完全相同，返回 true
}

TEST(FirstNSameTest, FirstNEqual) {
    std::map<int, int> map1 = {{1, 1}, {2, 2}, {3, 3}};
    std::map<int, int> map2 = {{1, 1}, {2, 2}, {4, 4}};
    EXPECT_TRUE(ccapi::firstNSame(map1, map2, 2)); // 前两个相同，返回 true
}

TEST(FirstNSameTest, FirstDifferent) {
    std::map<int, int> map1 = {{1, 1}, {2, 2}, {3, 3}};
    std::map<int, int> map2 = {{1, 1}, {3, 3}, {2, 2}};
    EXPECT_TRUE(ccapi::firstNSame(map1, map2, 2)); // 第一个不相同，返回 false
}

TEST(FirstNSameTest, SecondDifferent) {
    std::map<int, int> map1 = {{1, 1}, {2, 2}, {3, 3}};
    std::map<int, int> map2 = {{1, 1}, {2, 3}, {2, 2}};
    EXPECT_FALSE(ccapi::firstNSame(map1, map2, 2)); // 第二个不同，返回 false
}

TEST(FirstNSameTest, NExceedsSize) {
    std::map<int, int> map1 = {{1, 1}, {2, 2}};
    std::map<int, int> map2 = {{1, 1}, {2, 2}};
    EXPECT_TRUE(ccapi::firstNSame(map1, map2, 5)); // n 超出大小，返回 true
}

TEST(FirstNSameTest, MapsDifferentSize) {
    std::map<int, int> map1 = {{1, 1}, {2, 2}};
    std::map<int, int> map2 = {{1, 1}, {2, 2}, {3, 3}};
    EXPECT_TRUE(ccapi::firstNSame(map1, map2, 2)); // 前两个相同，返回 true
}

// 测试用例
TEST(LastNSameTest, BothEmpty) {
    std::map<int, int> map1;
    std::map<int, int> map2;
    EXPECT_TRUE(ccapi::lastNSame(map1, map2, 3)); // 两个空 map 应返回 true
}

TEST(LastNSameTest, FirstEmpty) {
    std::map<int, int> map1;
    std::map<int, int> map2 = {{1, 1}, {2, 2}};
    EXPECT_FALSE(ccapi::lastNSame(map1, map2, 1)); // 第一个 map 为空，返回 false
}

TEST(LastNSameTest, SecondEmpty) {
    std::map<int, int> map1 = {{1, 1}, {2, 2}};
    std::map<int, int> map2;
    EXPECT_FALSE(ccapi::lastNSame(map1, map2, 1)); // 第二个 map 为空，返回 false
}

TEST(LastNSameTest, MapsEqual) {
    std::map<int, int> map1 = {{1, 1}, {2, 2}, {3, 3}};
    std::map<int, int> map2 = {{1, 1}, {2, 2}, {3, 3}};
    EXPECT_TRUE(ccapi::lastNSame(map1, map2, 3)); // 完全相同，返回 true
}

TEST(LastNSameTest, LastNEqual) {
    std::map<int, int> map1 = {{1, 1}, {2, 2}, {3, 3}};
    std::map<int, int> map2 = {{2, 2}, {3, 3}, {4, 4}};
    EXPECT_FALSE(ccapi::lastNSame(map1, map2, 2)); // 最后两个相同，返回 true
}

TEST(LastNSameTest, LastDifferent) {
    std::map<int, int> map1 = {{1, 1}, {2, 2}, {3, 3}};
    std::map<int, int> map2 = {{2, 2}, {3, 4}, {4, 4}};
    EXPECT_FALSE(ccapi::lastNSame(map1, map2, 2)); // 最后一个不同，返回 false
}

TEST(LastNSameTest, NExceedsSize) {
    std::map<int, int> map1 = {{1, 1}, {2, 2}};
    std::map<int, int> map2 = {{1, 1}, {2, 2}, {3, 3}};
    EXPECT_FALSE(ccapi::lastNSame(map1, map2, 5)); // n 超出大小，返回 true
}

TEST(LastNSameTest, MapsDifferentSize) {
    std::map<int, int> map1 = {{1, 1}, {2, 2}};
    std::map<int, int> map2 = {{1, 1}, {2, 2}, {3, 3}};
    EXPECT_FALSE(ccapi::lastNSame(map1, map2, 2)); // 最后两个相同，返回 true
}

// 测试用例
TEST(KeepFirstNTest, EmptyMap) {
    std::map<int, int> m;
    ccapi::keepFirstN(m, 3);
    EXPECT_TRUE(m.empty()); // 空 map 应保持为空
}

TEST(KeepFirstNTest, KeepLessThanSize) {
    std::map<int, int> m = {{1, 10}, {2, 20}, {3, 30}};
    std::size_t num = 2;
    ccapi::keepFirstN(m, 2);
    EXPECT_EQ(m.size(), num); // 保留前 2 个元素
    EXPECT_EQ(m[1], 10);
    EXPECT_EQ(m[2], 20);
}

TEST(KeepFirstNTest, KeepExactlySize) {
    std::map<int, int> m = {{1, 10}, {2, 20}, {3, 30}};
    ccapi::keepFirstN(m, 3);
    std::size_t num = 3;
    EXPECT_EQ(m.size(), num); // 保留前 3 个元素
}

TEST(KeepFirstNTest, ExceedSize) {
    std::map<int, int> m = {{1, 10}, {2, 20}};
    ccapi::keepFirstN(m, 5);
    std::size_t num = 2;
    EXPECT_EQ(m.size(), num); // 尝试保留更多元素，但仍应保留全部元素
}

TEST(KeepFirstNTest, SingleElement) {
    std::map<int, int> m = {{1, 10}};
    ccapi::keepFirstN(m, 1);
    std::size_t num = 1;
    EXPECT_EQ(m.size(), num); // 保留单个元素
}

TEST(KeepFirstNTest, ZeroN) {
    std::map<int, int> m = {{1, 10}, {2, 20}};
    ccapi::keepFirstN(m, 0);
    EXPECT_TRUE(m.empty()); // n 为 0，map 应变为空
}

// 测试用例
TEST(KeepLastNTest, EmptyMap) {
    std::map<int, int> m;
    ccapi::keepLastN(m, 3);
    EXPECT_TRUE(m.empty()); // 空 map 应保持为空
}

TEST(KeepLastNTest, KeepLessThanSize) {
    std::map<int, int> m = {{1, 10}, {2, 20}, {3, 30}};
    ccapi::keepLastN(m, 2);
    std::size_t num = 2;
    EXPECT_EQ(m.size(), num); // 保留后 2 个元素
    EXPECT_EQ(m[2], 20);
    EXPECT_EQ(m[3], 30);
}

TEST(KeepLastNTest, KeepExactlySize) {
    std::map<int, int> m = {{1, 10}, {2, 20}, {3, 30}};
    ccapi::keepLastN(m, 3);
    std::size_t num = 3;
    EXPECT_EQ(m.size(), num); // 保留后 3 个元素
}

TEST(KeepLastNTest, ExceedSize) {
    std::map<int, int> m = {{1, 10}, {2, 20}};
    ccapi::keepLastN(m, 5);
    std::size_t num = 2;
    EXPECT_EQ(m.size(), num); // 尝试保留更多元素，但仍应保留全部元素
}

TEST(KeepLastNTest, SingleElement) {
    std::map<int, int> m = {{1, 10}};
    ccapi::keepLastN(m, 1);
    std::size_t num = 1;
    EXPECT_EQ(m.size(), num); // 保留单个元素
}

TEST(KeepLastNTest, ZeroN) {
    std::map<int, int> m = {{1, 10}, {2, 20}};
    ccapi::keepLastN(m, 0);
    EXPECT_TRUE(m.empty()); // n 为 0，map 应变为空
}

// 测试类 1: 具有 toString 成员函数
class MyClass {
public:
    std::string toString() const {
        return "MyClass instance";
    }
};

// 测试类 2: 没有 toString 成员函数
class NoToStringClass {
public:
    // 没有 toString 成员函数
};

// 测试类 3: toString 成员函数返回类型不是 std::string
class WrongToStringReturnType {
public:
    int toString() const {
        return 42;
    }
};

// 测试用例 1: 对象具有 toString 成员函数
TEST(ToStringTest, HasToString) {
    MyClass obj;
    EXPECT_EQ(ccapi::toString(obj), "MyClass instance");
}

// // 测试用例 2: 对象没有 toString 成员函数
// TEST(ToStringTest, NoToString) {
//     NoToStringClass obj;
//     // 这里应该会导致编译错误，但我们无法在运行时测试编译错误
//     // 因此，我们只能通过注释掉这行代码来验证
//     EXPECT_EQ(ccapi::toString(obj), "");
// }
//
// // 测试用例 3: toString 成员函数返回类型不是 std::string
// TEST(ToStringTest, WrongReturnType) {
//     WrongToStringReturnType obj;
//     // 这里应该会导致编译错误，但我们无法在运行时测试编译错误
//     // 因此，我们只能通过注释掉这行代码来验证
//     EXPECT_EQ(ccapi::toString(obj), "");
// }

// 测试用例
TEST(ToStringTest, EmptyArray) {
    int arr[] = {};
    long unsigned int num = 0;
    EXPECT_EQ(ccapi::toString(arr, num), "[]");  // 空数组
}

TEST(ToStringTest, IntArray) {
    int arr[] = {1, 2, 3};
    long unsigned int num = 3;
    EXPECT_EQ(ccapi::toString(arr, num), "[1, 2, 3]");  // 整数数组
}

// TEST(ToStringTest, FloatArray) {
//     float arr[] = {1.1f, 2.2f, 3.3f};
//     long unsigned int num = 3;
//     EXPECT_EQ(ccapi::toString(arr, num), "[1.100000, 2.200000, 3.300000]");  // 浮点数数组
// }

TEST(ToStringTest, SingleElementArray) {
    int arr[] = {42};
    long unsigned int num = 1;
    EXPECT_EQ(ccapi::toString(arr, num), "[42]");  // 单元素数组
}

// TEST(ToStringTest, DoubleArray) {
//     double arr[] = {0.123, 4.567, 89.01};
//     long unsigned int num = 3;
//     EXPECT_EQ(ccapi::toString(arr, num), "[0.123000, 4.567000, 89.010000]");  // 双精度浮点数数组
// }

TEST(ToStringTest, CharArray) {
    char arr[] = {'a', 'b', 'c'};
    long unsigned int num = 3;
    EXPECT_EQ(ccapi::toString(arr, num), "[97, 98, 99]");  // 字符数组（会转换为 ASCII 值）
}

// 测试用例
TEST(ToStringTest, PairInt) {
    std::pair<int, int> p = {1, 2};
    EXPECT_EQ(ccapi::toString(p), "(1,2)");  // 测试整型 pair
}

// TEST(ToStringTest, PairFloat) {
//     std::pair<float, float> p = {1.1f, 2.2f};
//     EXPECT_EQ(ccapi::toString(p), "(1.100000,2.200000)");  // 测试浮点型 pair
// }

TEST(ToStringTest, PairString) {
    std::pair<std::string, std::string> p = {"hello", "world"};
    EXPECT_EQ(ccapi::toString(p), "(hello,world)");  // 测试字符串 pair
}

TEST(ToStringTest, PairMixedTypes) {
    std::pair<int, std::string> p = {42, "answer"};
    EXPECT_EQ(ccapi::toString(p), "(42,answer)");  // 测试混合类型 pair
}

TEST(ToStringTest, PairDoubleInt) {
    std::pair<double, int> p = {3.14159, 42};
    EXPECT_EQ(ccapi::toString(p), "(3.1415900000,42)");  // 测试双精度浮点数和整型 pair
}

// 测试用例
TEST(ToStringTest, UnorderedSetInt) {
    std::unordered_set<int> s = {1, 2, 3, 4};
    std::string result = ccapi::toString(s);
    EXPECT_TRUE(result.find('1') != std::string::npos);  // 无序集，元素顺序不确定
    EXPECT_TRUE(result.find('2') != std::string::npos);
    EXPECT_TRUE(result.find('3') != std::string::npos);
    EXPECT_TRUE(result.find('4') != std::string::npos);
    EXPECT_EQ(result.front(), '[');
    EXPECT_EQ(result.back(), ']');
}

// TEST(ToStringTest, UnorderedSetFloat) {
//     std::unordered_set<float> s = {1.1f, 2.2f, 3.3f};
//     std::string result = ccapi::toString(s);
//     EXPECT_TRUE(result.find("1.100000") != std::string::npos);  // 浮点数验证
//     EXPECT_TRUE(result.find("2.200000") != std::string::npos);
//     EXPECT_TRUE(result.find("3.300000") != std::string::npos);
// }

TEST(ToStringTest, UnorderedSetString) {
    std::unordered_set<std::string> s = {"hello", "world", "test"};
    std::string result = ccapi::toString(s);
    EXPECT_TRUE(result.find("hello") != std::string::npos);  // 字符串类型验证
    EXPECT_TRUE(result.find("world") != std::string::npos);
    EXPECT_TRUE(result.find("test") != std::string::npos);
}

TEST(ToStringTest, UnorderedSetEmpty) {
    std::unordered_set<int> s;
    EXPECT_EQ(ccapi::toString(s), "[]");  // 空集合
}

TEST(ToStringTest, UnorderedSetMixedTypes) {
    std::unordered_set<std::string> s = {"123", "456"};
    std::string result = ccapi::toString(s);
    EXPECT_TRUE(result.find("123") != std::string::npos);  // 验证混合类型或可能的复杂字符串
    EXPECT_TRUE(result.find("456") != std::string::npos);
}

// 测试用例
TEST(ToStringTest, SetInt) {
    std::set<int> s = {1, 2, 3, 4};
    std::string result = ccapi::toString(s);
    EXPECT_EQ(result, "[1, 2, 3, 4]");  // 有序集，元素顺序是确定的
}

// TEST(ToStringTest, SetFloat) {
//     std::set<float> s = {1.1f, 2.2f, 3.3f};
//     std::string result = ccapi::toString(s);
//     EXPECT_EQ(result, "[1.100000, 2.200000, 3.300000]");  // 验证浮点数
// }

TEST(ToStringTest, SetString) {
    std::set<std::string> s = {"apple", "banana", "cherry"};
    std::string result = ccapi::toString(s);
    EXPECT_EQ(result, "[apple, banana, cherry]");  // 验证字符串类型
}

TEST(ToStringTest, SetEmpty) {
    std::set<int> s;
    EXPECT_EQ(ccapi::toString(s), "[]");  // 空集合
}

TEST(ToStringTest, SetSingleElement) {
    std::set<int> s = {42};
    EXPECT_EQ(ccapi::toString(s), "[42]");  // 单元素集合
}

TEST(ToStringTest, SetMixedTypes) {
    std::set<std::string> s = {"123", "456"};
    std::string result = ccapi::toString(s);
    EXPECT_EQ(result, "[123, 456]");  // 验证复杂的字符串
}

// 测试用例
TEST(ToStringTest, MapIntToInt) {
    std::map<int, int> m = {{1, 10}, {2, 20}, {3, 30}};
    std::string result = ccapi::toString(m);
    EXPECT_EQ(result, "{1=10, 2=20, 3=30}");  // 测试整数类型的映射
}

TEST(ToStringTest, MapStringToString) {
    std::map<std::string, std::string> m = {{"apple", "fruit"}, {"carrot", "vegetable"}};
    std::string result = ccapi::toString(m);
    EXPECT_EQ(result, "{apple=fruit, carrot=vegetable}");  // 测试字符串类型的映射
}

TEST(ToStringTest, MapIntToString) {
    std::map<int, std::string> m = {{1, "one"}, {2, "two"}};
    std::string result = ccapi::toString(m);
    EXPECT_EQ(result, "{1=one, 2=two}");  // 测试整数到字符串的映射
}

TEST(ToStringTest, MapStringToInt) {
    std::map<std::string, int> m = {{"A", 65}, {"B", 66}};
    std::string result = ccapi::toString(m);
    EXPECT_EQ(result, "{A=65, B=66}");  // 测试字符串到整数的映射
}

TEST(ToStringTest, MapEmpty) {
    std::map<int, int> m;
    EXPECT_EQ(ccapi::toString(m), "{}");  // 测试空映射
}

TEST(ToStringTest, MapSingleElement) {
    std::map<int, int> m = {{42, 100}};
    EXPECT_EQ(ccapi::toString(m), "{42=100}");  // 测试单元素映射
}

TEST(ToStringTest, MapMixedTypes) {
  // 初始化数据
  std::map<std::string, float> m = {{"pi", 3.1415f}, {"e", 2.718f}};
  std::string result = ccapi::toString(m);
  // std::cout << "Serialized result: " << result << std::endl;

  // 修改后的正则表达式
  // 匹配 {key1=value1, key2=value2} 格式，支持浮点数解析
  std::regex pattern(R"(\{([^=]+)=([0-9eE.\-]+),?\s?([^=]+)=([0-9eE.\-]+)\})");
  std::smatch match;
  std::map<std::string, float> parsedMap;

  // 解析字符串
  if (std::regex_match(result, match, pattern)) {
    // 提取第一个键值对
    parsedMap[match[1].str()] = std::stof(match[2].str());
    // 提取第二个键值对
    parsedMap[match[3].str()] = std::stof(match[4].str());
  } else {
    std::cerr << "Failed to parse serialized result: " << result << std::endl;
  }

  //  // 输出解析后的结果
  //  std::cout << "parsedMap[\"pi\"] = " << parsedMap["pi"] << std::endl;
  //  std::cout << "parsedMap[\"e\"] = " << parsedMap["e"] << std::endl;

  // 使用 EXPECT_NEAR 比较，允许浮点误差
  EXPECT_NEAR(parsedMap["pi"], 3.1415f, 1e-4);
  EXPECT_NEAR(parsedMap["e"], 2.718f, 1e-4);
}


TEST(ToStringPrettyTest, MapIntToInt) {
    std::map<int, int> m = {{1, 10}, {2, 20}, {3, 30}};
    std::string result = ccapi::toStringPretty(m);
    std::string expected =
        "{\n"
        "  1 = 10,\n"
        "  2 = 20,\n"
        "  3 = 30\n"
        "}";
    EXPECT_EQ(result, expected);
}

TEST(ToStringPrettyTest, MapStringToString) {
    std::map<std::string, std::string> m = {{"apple", "fruit"}, {"carrot", "vegetable"}};
    std::string result = ccapi::toStringPretty(m);
    std::string expected =
        "{\n"
        "  apple = fruit,\n"
        "  carrot = vegetable\n"
        "}";
    EXPECT_EQ(result, expected);
}

TEST(ToStringPrettyTest, MapIntToStringWithIndentation) {
    std::map<int, std::string> m = {{1, "one"}, {2, "two"}};
    std::string result = ccapi::toStringPretty(m, 4);
    std::string expected =
        "{\n"
        "    1 = one,\n"
        "    2 = two\n"
        "}";
    EXPECT_EQ(result, expected);
}

TEST(ToStringPrettyTest, MapEmpty) {
    std::map<int, int> m;
    EXPECT_EQ(ccapi::toStringPretty(m), "{\n\n}");
}

TEST(ToStringPrettyTest, MapSingleElement) {
    std::map<int, int> m = {{42, 100}};
    std::string result = ccapi::toStringPretty(m);
    std::string expected =
        "{\n"
        "  42 = 100\n"
        "}";
    EXPECT_EQ(result, expected);
}

TEST(ToStringPrettyTest, MapNestedMap) {
    std::map<int, std::map<int, int>> m = {{1, {{10, 100}, {20, 200}}}, {2, {{30, 300}}}};
    std::string result = ccapi::toStringPretty(m);
    std::string expected =
        "{\n"
        "  1 = {\n"
        "    10 = 100,\n"
        "    20 = 200\n"
        "  },\n"
        "  2 = {\n"
        "    30 = 300\n"
        "  }\n"
        "}";
    EXPECT_EQ(result, expected);
}

TEST(ToStringPrettyTest, MapStringToStringWithCustomIndentation) {
    std::map<std::string, std::string> m = {{"apple", "fruit"}, {"banana", "fruit"}};
    std::string result = ccapi::toStringPretty(m, 3);
    std::string expected =
        "{\n"
        "   apple = fruit,\n"
        "   banana = fruit\n"
        "}";
    EXPECT_EQ(result, expected);
}

TEST(ToStringTest, UnorderedMapIntToInt) {
    std::unordered_map<int, int> m = {{1, 10}, {2, 20}, {3, 30}};
    std::string result = ccapi::toString(m);
    // 由于 unordered_map 不保证顺序，结果可能有不同顺序
    std::string expected1 = "{1=10, 2=20, 3=30}";
    std::string expected2 = "{1=10, 3=30, 2=20}";
    std::string expected3 = "{2=20, 1=10, 3=30}";
    std::string expected4 = "{2=20, 3=30, 1=10}";
    std::string expected5 = "{3=30, 1=10, 2=20}";
    std::string expected6 = "{3=30, 2=20, 1=10}";

    EXPECT_TRUE(result == expected1 || result == expected2 || result == expected3 ||
                result == expected4 || result == expected5 || result == expected6);
}

TEST(ToStringTest, UnorderedMapStringToString) {
    std::unordered_map<std::string, std::string> m = {{"apple", "fruit"}, {"carrot", "vegetable"}};
    std::string result = ccapi::toString(m);
    std::string expected1 = "{apple=fruit, carrot=vegetable}";
    std::string expected2 = "{carrot=vegetable, apple=fruit}";
    EXPECT_TRUE(result == expected1 || result == expected2);
}

TEST(ToStringTest, UnorderedMapIntToString) {
    std::unordered_map<int, std::string> m = {{1, "one"}, {2, "two"}};
    std::string result = ccapi::toString(m);
    std::string expected1 = "{1=one, 2=two}";
    std::string expected2 = "{2=two, 1=one}";
    EXPECT_TRUE(result == expected1 || result == expected2);
}

TEST(ToStringTest, UnorderedMapEmpty) {
    std::unordered_map<int, int> m;
    EXPECT_EQ(ccapi::toString(m), "{}");
}

TEST(ToStringTest, UnorderedMapSingleElement) {
    std::unordered_map<int, int> m = {{42, 100}};
    std::string result = ccapi::toString(m);
    std::string expected = "{42=100}";
    EXPECT_EQ(result, expected);
}

TEST(ToStringTest, UnorderedMapNested) {
    std::unordered_map<int, std::unordered_map<int, int>> m = {{1, {{10, 100}, {20, 200}}}, {2, {{30, 300}}}};
    std::string result = ccapi::toString(m);
    std::cout << "result = " << result << std::endl;
    std::string expected1 = "{1={10=100, 20=200}, 2={30=300}}";
    std::string expected2 = "{2={30=300}, 1={10=100, 20=200}}";
    std::string expected3 = "{2={30=300}, 1={20=200, 10=100}}";
    std::string expected4 = "{2={20=200, 10=100}, 2={30=300}}";
    EXPECT_TRUE(result == expected1 || result == expected2 || result == expected3 || result == expected4);
}

TEST(FirstNToStringTest, MapIntToInt) {
    std::map<int, int> m = {{1, 10}, {2, 20}, {3, 30}, {4, 40}, {5, 50}};
    std::string result = ccapi::firstNToString(m, 3);
    std::string expected = "{1=10, 2=20, 3=30, ...}";
    EXPECT_EQ(result, expected);
}

TEST(FirstNToStringTest, MapStringToString) {
    std::map<std::string, std::string> m = {{"apple", "fruit"}, {"carrot", "vegetable"}, {"banana", "fruit"}, {"lettuce", "vegetable"}};
    std::string result = ccapi::firstNToString(m, 2);
    std::string expected = "{apple=fruit, banana=fruit, ...}";
    EXPECT_EQ(result, expected);
}

TEST(FirstNToStringTest, MapNEqualToSize) {
    std::map<int, int> m = {{1, 10}, {2, 20}, {3, 30}};
    std::string result = ccapi::firstNToString(m, 3);
    std::string expected = "{1=10, 2=20, 3=30}";
    EXPECT_EQ(result, expected);
}

TEST(FirstNToStringTest, MapNGreaterThanSize) {
    std::map<int, int> m = {{1, 10}, {2, 20}, {3, 30}};
    std::string result = ccapi::firstNToString(m, 5);
    std::string expected = "{1=10, 2=20, 3=30}";
    EXPECT_EQ(result, expected);
}

TEST(FirstNToStringTest, MapEmpty) {
    std::map<int, int> m;
    std::string result = ccapi::firstNToString(m, 3);
    std::string expected = "{}";
    EXPECT_EQ(result, expected);
}

TEST(FirstNToStringTest, MapSingleElement) {
    std::map<int, int> m = {{42, 100}};
    std::string result = ccapi::firstNToString(m, 1);
    std::string expected = "{42=100}";
    EXPECT_EQ(result, expected);
}

TEST(LastNToStringTest, MapIntToInt) {
    std::map<int, int> m = {{1, 10}, {2, 20}, {3, 30}, {4, 40}, {5, 50}};
    std::string result = ccapi::lastNToString(m, 3);
    std::string expected = "{5=50, 4=40, 3=30, ...}";
    EXPECT_EQ(result, expected);
}

TEST(LastNToStringTest, MapStringToString) {
    std::map<std::string, std::string> m = {{"apple", "fruit"}, {"carrot", "vegetable"}, {"banana", "fruit"}, {"lettuce", "vegetable"}};
    std::string result = ccapi::lastNToString(m, 2);
    std::string expected = "{lettuce=vegetable, carrot=vegetable, ...}";
    EXPECT_EQ(result, expected);
}

TEST(LastNToStringTest, MapNEqualToSize) {
    std::map<int, int> m = {{1, 10}, {2, 20}, {3, 30}};
    std::string result = ccapi::lastNToString(m, 3);
    std::string expected = "{3=30, 2=20, 1=10}";
    EXPECT_EQ(result, expected);
}

TEST(LastNToStringTest, MapNGreaterThanSize) {
    std::map<int, int> m = {{1, 10}, {2, 20}, {3, 30}};
    std::string result = ccapi::lastNToString(m, 5);
    std::string expected = "{3=30, 2=20, 1=10}";
    EXPECT_EQ(result, expected);
}

TEST(LastNToStringTest, MapEmpty) {
    std::map<int, int> m;
    std::string result = ccapi::lastNToString(m, 3);
    std::string expected = "{}";
    EXPECT_EQ(result, expected);
}

TEST(LastNToStringTest, MapSingleElement) {
    std::map<int, int> m = {{42, 100}};
    std::string result = ccapi::lastNToString(m, 1);
    std::string expected = "{42=100}";
    EXPECT_EQ(result, expected);
}

TEST(ToStringVectorTest, VectorOfInts) {
    std::vector<int> v = {1, 2, 3, 4};
    std::string result = ccapi::toString(v);
    std::string expected = "[ 1, 2, 3, 4 ]";
    EXPECT_EQ(result, expected);
}

TEST(ToStringVectorTest, VectorOfStrings) {
    std::vector<std::string> v = {"apple", "banana", "carrot"};
    std::string result = ccapi::toString(v);
    std::string expected = "[ apple, banana, carrot ]";
    EXPECT_EQ(result, expected);
}

TEST(ToStringVectorTest, EmptyVector) {
    std::vector<int> v;
    std::string result = ccapi::toString(v);
    std::string expected = "[  ]";
    EXPECT_EQ(result, expected);
}

TEST(ToStringVectorTest, VectorOfDoubles) {
    std::vector<double> v = {1.1, 2.2, 3.3};
    std::string result = ccapi::toString(v);
    std::string expected = "[ 1.1000000000, 2.2000000000, 3.3000000000 ]";
    EXPECT_EQ(result, expected);
}

TEST(ToStringVectorTest, SingleElementVector) {
    std::vector<int> v = {42};
    std::string result = ccapi::toString(v);
    std::string expected = "[ 42 ]";
    EXPECT_EQ(result, expected);
}

TEST(ToStringVectorTest, VectorOfVectors) {
    std::vector<std::vector<int>> v = {{1, 2}, {3, 4}, {5}};
    std::string result = ccapi::toString(v);
    std::string expected = "[ [ 1, 2 ], [ 3, 4 ], [ 5 ] ]";
    EXPECT_EQ(result, expected);
}

TEST(ToStringPrettyVectorTest, VectorOfInts) {
    std::vector<int> v = {1, 2, 3};
    std::string result = ccapi::toStringPretty(v);
    std::string expected = "[\n  1,\n  2,\n  3\n]";
    EXPECT_EQ(result, expected);
}

TEST(ToStringPrettyVectorTest, VectorOfStrings) {
    std::vector<std::string> v = {"apple", "banana", "carrot"};
    std::string result = ccapi::toStringPretty(v);
    std::string expected = "[\n  apple,\n  banana,\n  carrot\n]";
    EXPECT_EQ(result, expected);
}

TEST(ToStringPrettyVectorTest, EmptyVector) {
    std::vector<int> v;
    std::string result = ccapi::toStringPretty(v);
    std::string expected = "[\n\n]";
    EXPECT_EQ(result, expected);
}

TEST(ToStringPrettyVectorTest, SingleElementVector) {
    std::vector<int> v = {42};
    std::string result = ccapi::toStringPretty(v);
    std::string expected = "[\n  42\n]";
    EXPECT_EQ(result, expected);
}

TEST(ToStringPrettyVectorTest, VectorOfVectors) {
    std::vector<std::vector<int>> v = {{1, 2}, {3}, {4, 5, 6}};
    std::string result = ccapi::toStringPretty(v);
    std::string expected = "[\n  [\n    1,\n    2\n  ],\n  [\n    3\n  ],\n  [\n    4,\n    5,\n    6\n  ]\n]";
    EXPECT_EQ(result, expected);
}

TEST(ToStringPrettyVectorTest, IndentationCheck) {
    std::vector<int> v = {1, 2, 3};
    std::string result = ccapi::toStringPretty(v, 4, 4);  // 使用 4 空格缩进
    std::string expected = "    [\n        1,\n        2,\n        3\n    ]";
    EXPECT_EQ(result, expected);
}

TEST(FirstNToStringTest, VectorOfInts) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    std::string result = ccapi::firstNToString(v, 3);
    std::string expected = "[ 1, 2, 3, ... ]";
    EXPECT_EQ(result, expected);
}

TEST(FirstNToStringTest, NGreaterThanSize) {
    std::vector<int> v = {1, 2, 3};
    std::string result = ccapi::firstNToString(v, 5);
    std::string expected = "[ 1, 2, 3 ]";
    EXPECT_EQ(result, expected);
}

TEST(FirstNToStringTest, NEqualToSize) {
    std::vector<int> v = {1, 2, 3};
    std::string result = ccapi::firstNToString(v, 3);
    std::string expected = "[ 1, 2, 3 ]";
    EXPECT_EQ(result, expected);
}

TEST(FirstNToStringTest, EmptyVector) {
    std::vector<int> v;
    std::string result = ccapi::firstNToString(v, 3);
    std::string expected = "[  ]";
    EXPECT_EQ(result, expected);
}

TEST(FirstNToStringTest, NIsZero) {
    std::vector<int> v = {1, 2, 3};
    std::string result = ccapi::firstNToString(v, 0);
    std::string expected = "[  ]";
    EXPECT_EQ(result, expected);
}

TEST(FirstNToStringTest, VectorOfStrings) {
    std::vector<std::string> v = {"apple", "banana", "carrot"};
    std::string result = ccapi::firstNToString(v, 2);
    std::string expected = "[ apple, banana,  ]";
    EXPECT_EQ(result, expected);
}

TEST(FirstNToStringTest, SingleElementVector) {
    std::vector<int> v = {42};
    std::string result = ccapi::firstNToString(v, 1);
    std::string expected = "[ 42 ]";
    EXPECT_EQ(result, expected);
}

TEST(FirstNToStringPrettyTest, VectorOfInts) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    std::string result = ccapi::firstNToStringPretty(v, 3);
    std::string expected = "[\n  1,\n  2,\n  3,\n...\n]";
    EXPECT_EQ(result, expected);
}

TEST(FirstNToStringPrettyTest, NGreaterThanSize) {
    std::vector<int> v = {1, 2, 3};
    std::string result = ccapi::firstNToStringPretty(v, 5);
    std::string expected = "[\n  1,\n  2,\n  3\n]";
    EXPECT_EQ(result, expected);
}

TEST(FirstNToStringPrettyTest, NEqualToSize) {
    std::vector<int> v = {1, 2, 3};
    std::string result = ccapi::firstNToStringPretty(v, 3);
    std::string expected = "[\n  1,\n  2,\n  3\n]";
    EXPECT_EQ(result, expected);
}

TEST(FirstNToStringPrettyTest, EmptyVector) {
    std::vector<int> v;
    std::string result = ccapi::firstNToStringPretty(v, 3);
    std::string expected = "[\n\n]";
    EXPECT_EQ(result, expected);
}

TEST(FirstNToStringPrettyTest, NIsZero) {
    std::vector<int> v = {1, 2, 3};
    std::string result = ccapi::firstNToStringPretty(v, 0);
    std::string expected = "[\n\n]";
    EXPECT_EQ(result, expected);
}

TEST(FirstNToStringPrettyTest, VectorOfStrings) {
    std::vector<std::string> v = {"apple", "banana", "carrot"};
    std::string result = ccapi::firstNToStringPretty(v, 2);
    std::string expected = "[\n  apple,\n  banana,\n\n]";
    EXPECT_EQ(result, expected);
}

TEST(FirstNToStringPrettyTest, SingleElementVector) {
    std::vector<int> v = {42};
    std::string result = ccapi::firstNToStringPretty(v, 1);
    std::string expected = "[\n  42\n]";
    EXPECT_EQ(result, expected);
}

TEST(FirstNToStringPrettyTest, Indentation) {
    std::vector<int> v = {1, 2, 3};
    std::string result = ccapi::firstNToStringPretty(v, 2, 4, 2);
    std::string expected = "  [\n      1,\n      2,\n\n  ]"; // Indented output
    EXPECT_EQ(result, expected);
}

TEST(InvertMapMultiTest, SimpleMap) {
    std::map<int, std::string> input = {{1, "a"}, {2, "b"}, {3, "a"}};
    std::map<std::string, std::vector<int>> expected = {
        {"a", {1, 3}},
        {"b", {2}}
    };
    EXPECT_EQ(ccapi::invertMapMulti(input), expected);
}

TEST(InvertMapMultiTest, SingleValueMultipleKeys) {
    std::map<int, std::string> input = {{1, "x"}, {2, "y"}, {3, "x"}};
    std::map<std::string, std::vector<int>> expected = {
        {"x", {1, 3}},
        {"y", {2}}
    };
    EXPECT_EQ(ccapi::invertMapMulti(input), expected);
}

TEST(InvertMapMultiTest, EmptyMap) {
    std::map<int, std::string> input;
    std::map<std::string, std::vector<int>> expected;
    EXPECT_EQ(ccapi::invertMapMulti(input), expected);
}

TEST(InvertMapMultiTest, NoDuplicates) {
    std::map<int, std::string> input = {{1, "a"}, {2, "b"}, {3, "c"}};
    std::map<std::string, std::vector<int>> expected = {
        {"a", {1}},
        {"b", {2}},
        {"c", {3}}
    };
    EXPECT_EQ(ccapi::invertMapMulti(input), expected);
}

TEST(InvertMapMultiTest, AllKeysSameValue) {
    std::map<int, std::string> input = {{1, "same"}, {2, "same"}, {3, "same"}};
    std::map<std::string, std::vector<int>> expected = {
        {"same", {1, 2, 3}}
    };
    EXPECT_EQ(ccapi::invertMapMulti(input), expected);
}

TEST(InvertMapMultiTest, DifferentDataTypes) {
    std::map<double, char> input = {{1.1, 'x'}, {2.2, 'y'}, {3.3, 'x'}};
    std::map<char, std::vector<double>> expected = {
        {'x', {1.1, 3.3}},
        {'y', {2.2}}
    };
    EXPECT_EQ(ccapi::invertMapMulti(input), expected);
}

TEST(InvertMapMultiTest, ComplexDataTypes) {
    std::map<std::string, std::string> input = {
        {"apple", "fruit"},
        {"carrot", "vegetable"},
        {"banana", "fruit"},
        {"celery", "vegetable"}
    };
    std::map<std::string, std::vector<std::string>> expected = {
        {"fruit", {"apple", "banana"}},
        {"vegetable", {"carrot", "celery"}}
    };
    EXPECT_EQ(ccapi::invertMapMulti(input), expected);
}

TEST(InvertMapTest, SimpleMap) {
    std::map<int, std::string> input = {{1, "a"}, {2, "b"}, {3, "c"}};
    std::map<std::string, int> expected = {
        {"a", 1},
        {"b", 2},
        {"c", 3}
    };
    EXPECT_EQ(ccapi::invertMap(input), expected);
}

TEST(InvertMapTest, EmptyMap) {
    std::map<int, std::string> input;
    std::map<std::string, int> expected;
    EXPECT_EQ(ccapi::invertMap(input), expected);
}

TEST(InvertMapTest, NoDuplicates) {
    std::map<int, std::string> input = {{1, "apple"}, {2, "banana"}, {3, "cherry"}};
    std::map<std::string, int> expected = {
        {"apple", 1},
        {"banana", 2},
        {"cherry", 3}
    };
    EXPECT_EQ(ccapi::invertMap(input), expected);
}

TEST(InvertMapTest, DuplicateValues) {
    std::map<int, std::string> input = {{1, "apple"}, {2, "banana"}, {3, "apple"}};
    std::map<std::string, int> expected = {
        {"apple", 1}, // The last inserted key will be retained
        {"banana", 2}
    };
    EXPECT_EQ(ccapi::invertMap(input), expected);
}

TEST(InvertMapTest, DifferentDataTypes) {
    std::map<double, char> input = {{1.1, 'x'}, {2.2, 'y'}, {3.3, 'z'}};
    std::map<char, double> expected = {
        {'x', 1.1},
        {'y', 2.2},
        {'z', 3.3}
    };
    EXPECT_EQ(ccapi::invertMap(input), expected);
}

TEST(InvertMapTest, ComplexDataTypes) {
    std::map<std::string, std::string> input = {
        {"apple", "fruit"},
        {"carrot", "vegetable"},
        {"banana", "fruit"}
    };
    std::map<std::string, std::string> expected = {
        {"fruit", "apple"},    // Last inserted key for "fruit" will be retained
        {"vegetable", "carrot"}
    };
    EXPECT_EQ(ccapi::invertMap(input), expected);
}

TEST(MapGetWithDefaultTest, KeyExistsInMap) {
    std::map<int, std::string> m = {{1, "one"}, {2, "two"}, {3, "three"}};
    EXPECT_EQ(ccapi::mapGetWithDefault(m, 2, std::string("default")), "two");
}

TEST(MapGetWithDefaultTest, KeyDoesNotExistInMap) {
    std::map<int, std::string> m = {{1, "one"}, {2, "two"}, {3, "three"}};
    EXPECT_EQ(ccapi::mapGetWithDefault(m, 4, std::string("default")), "default");
}

TEST(MapGetWithDefaultTest, EmptyMap) {
    std::map<int, std::string> m;
    EXPECT_EQ(ccapi::mapGetWithDefault(m, 1, std::string("default")), "default");
}

TEST(MapGetWithDefaultTest, CustomDefaultValue) {
    std::unordered_map<std::string, int> m = {{"one", 1}, {"two", 2}};
    EXPECT_EQ(ccapi::mapGetWithDefault(m, std::string("three"), 99), 99);
}

TEST(MapGetWithDefaultTest, DefaultValueIsZero) {
    std::map<int, int> m = {{1, 10}, {2, 20}};
    EXPECT_EQ(ccapi::mapGetWithDefault(m, 3), 0); // Default is zero
}

TEST(MapGetWithDefaultTest, KeyExistsWithDefaultDifferentType) {
    std::map<std::string, double> m = {{"pi", 3.14}, {"e", 2.71}};
    EXPECT_DOUBLE_EQ(ccapi::mapGetWithDefault(m, std::string("pi"), 0.0), 3.14);
}

TEST(MapGetWithDefaultTest, DefaultValueAsString) {
    std::unordered_map<int, std::string> m = {{1, "apple"}, {2, "banana"}};
    EXPECT_EQ(ccapi::mapGetWithDefault(m, 3, std::string("unknown")), std::string("unknown"));
}

TEST(MapGetWithDefaultTest, DifferentKeyTypes) {
    std::map<std::string, std::string> m = {{"apple", "red"}, {"banana", "yellow"}};
    EXPECT_EQ(ccapi::mapGetWithDefault(m, std::string("banana"), std::string("default")), std::string("yellow"));
    EXPECT_EQ(ccapi::mapGetWithDefault(m, std::string("grape"), std::string("default")), std::string("default"));
}




