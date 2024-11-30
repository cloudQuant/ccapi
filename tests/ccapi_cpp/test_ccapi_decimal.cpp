#include <gtest/gtest.h>

#include "../../include/ccapi_cpp/ccapi_decimal.h"

using namespace ccapi;

// 测试构造函数
TEST(DecimalTest, DefaultConstructor) {
    Decimal decimal;
    const long long unsigned int num = 0;
    EXPECT_EQ(decimal.before, num);
    EXPECT_EQ(decimal.frac, "");
    EXPECT_TRUE(decimal.sign);
}

TEST(DecimalTest, StringConstructorPositive) {
    Decimal decimal("123.456");
    const long long unsigned int num = 123;
    EXPECT_EQ(decimal.before, num);
    EXPECT_EQ(decimal.frac, "456");
    EXPECT_TRUE(decimal.sign);
}

TEST(DecimalTest, StringConstructorNegative) {
    Decimal decimal("-123.456");
    const long long unsigned int num = 123;
    EXPECT_EQ(decimal.before, num);
    EXPECT_EQ(decimal.frac, "456");
    EXPECT_FALSE(decimal.sign);
}

TEST(DecimalTest, StringConstructorScientificNotation) {
    Decimal decimal("1.23E2");
    const long long unsigned int num = 123;
    EXPECT_EQ(decimal.before, num);
    EXPECT_EQ(decimal.frac, "");
    EXPECT_TRUE(decimal.sign);
}

TEST(DecimalTest, StringConstructorWithTrailingZeros) {
    Decimal decimal("123.45000", true);
    const long long unsigned int num = 123;
    EXPECT_EQ(decimal.before, num);
    EXPECT_EQ(decimal.frac, "45000");
    EXPECT_TRUE(decimal.sign);
}

// 测试 toString() 方法
TEST(DecimalTest, ToStringPositive) {
    Decimal decimal("123.456");
    EXPECT_EQ(decimal.toString(), "123.456");
}

TEST(DecimalTest, ToStringNegative) {
    Decimal decimal("-123.456");
    EXPECT_EQ(decimal.toString(), "-123.456");
}

// 测试加法
TEST(DecimalTest, AddPositive) {
    Decimal decimal1("123.456");
    Decimal decimal2("100.544");
    Decimal result = decimal1.add(decimal2);
    EXPECT_EQ(result.toString(), "224");
}

TEST(DecimalTest, AddNegative) {
    Decimal decimal1("-123.456");
    Decimal decimal2("-100.544");
    Decimal result = decimal1.add(decimal2);
    EXPECT_EQ(result.toString(), "-224");
}

// 测试减法
TEST(DecimalTest, SubtractPositive) {
    Decimal decimal1("123.456");
    Decimal decimal2("100.544");
    Decimal result = decimal1.subtract(decimal2);
    EXPECT_EQ(result.toString(), "22.912");
}

TEST(DecimalTest, SubtractNegative) {
    Decimal decimal1("-123.456");
    Decimal decimal2("-100.544");
    Decimal result = decimal1.subtract(decimal2);
    EXPECT_EQ(result.toString(), "-22.912");
}

// 测试比较运算符
TEST(DecimalTest, LessThan) {
    Decimal decimal1("123.456");
    Decimal decimal2("200.544");
    EXPECT_TRUE(decimal1 < decimal2);
}

TEST(DecimalTest, GreaterThan) {
    Decimal decimal1("200.544");
    Decimal decimal2("123.456");
    EXPECT_TRUE(decimal1 > decimal2);
}

TEST(DecimalTest, EqualTo) {
    Decimal decimal1("123.456");
    Decimal decimal2("123.456");
    EXPECT_TRUE(decimal1 == decimal2);
}

// 测试求相反数
TEST(DecimalTest, Negate) {
    Decimal decimal("123.456");
    Decimal negated = decimal.negate();
    EXPECT_EQ(negated.toString(), "-123.456");
}

// 测试构造函数
TEST(DecimalTest, EmptyStringConstructor) {
    EXPECT_THROW(Decimal decimal(""), std::runtime_error);
}

TEST(DecimalTest, LeadingZeroes) {
    Decimal decimal("000123.456");
    const long long unsigned int num = 123;
    EXPECT_EQ(decimal.before, num);
    EXPECT_EQ(decimal.frac, "456");
    EXPECT_TRUE(decimal.sign);
}

TEST(DecimalTest, TrailingZeroesInFraction) {
    Decimal decimal("123.45000");
    const long long unsigned int num = 123;
    EXPECT_EQ(decimal.before, num);
    EXPECT_EQ(decimal.frac, "45");
    EXPECT_TRUE(decimal.sign);
}

// 测试 toString() 方法
TEST(DecimalTest, ToStringWithZeroFraction) {
    Decimal decimal("123.0");
    EXPECT_EQ(decimal.toString(), "123");
}

TEST(DecimalTest, ToStringWithNegativeZero) {
    Decimal decimal("-0.0");
    EXPECT_EQ(decimal.toString(), "-0");
}

// 测试加法
TEST(DecimalTest, AddWithZero) {
    Decimal decimal1("123.456");
    Decimal decimal2("0.000");
    Decimal result = decimal1.add(decimal2);
    EXPECT_EQ(result.toString(), "123.456");
}

TEST(DecimalTest, AddMixedSigns) {
    Decimal decimal1("123.456");
    Decimal decimal2("-100.456");
    Decimal result = decimal1.add(decimal2);
    EXPECT_EQ(result.toString(), "23");
}

// 测试减法
TEST(DecimalTest, SubtractWithZero) {
    Decimal decimal1("123.456");
    Decimal decimal2("0.000");
    Decimal result = decimal1.subtract(decimal2);
    EXPECT_EQ(result.toString(), "123.456");
}

TEST(DecimalTest, SubtractNegativeResult) {
    Decimal decimal1("100.000");
    Decimal decimal2("123.456");
    Decimal result = decimal1.subtract(decimal2);
    EXPECT_EQ(result.toString(), "-23.456");
}

// 测试比较运算符
TEST(DecimalTest, LessThanNegative) {
    Decimal decimal1("-123.456");
    Decimal decimal2("-100.000");
    EXPECT_TRUE(decimal1 < decimal2);
}

TEST(DecimalTest, GreaterThanNegative) {
    Decimal decimal1("-100.000");
    Decimal decimal2("-123.456");
    EXPECT_TRUE(decimal1 > decimal2);
}

TEST(DecimalTest, LessThanZero) {
    Decimal decimal1("-1.000");
    Decimal decimal2("0.000");
    EXPECT_TRUE(decimal1 < decimal2);
}

TEST(DecimalTest, GreaterThanZero) {
    Decimal decimal1("1.000");
    Decimal decimal2("0.000");
    EXPECT_TRUE(decimal1 > decimal2);
}

// 测试求相反数
TEST(DecimalTest, NegateWithZero) {
    Decimal decimal("0.000");
    Decimal negated = decimal.negate();
    EXPECT_EQ(negated.toString(), "-0");
}

TEST(DecimalTest, NegateWithPositive) {
    Decimal decimal("123.456");
    Decimal negated = decimal.negate();
    EXPECT_EQ(negated.toString(), "-123.456");
}

TEST(DecimalTest, NegateWithNegative) {
    Decimal decimal("-123.456");
    Decimal negated = decimal.negate();
    EXPECT_EQ(negated.toString(), "123.456");
}

// 测试科学计数法
TEST(DecimalTest, ScientificNotationPositive) {
    Decimal decimal("1E3");
    const long long unsigned int num = 1000;
    EXPECT_EQ(decimal.before, num);
    EXPECT_EQ(decimal.frac, "");
    EXPECT_TRUE(decimal.sign);
}

TEST(DecimalTest, ScientificNotationNegative) {
    Decimal decimal("-1.23E2");
    const long long unsigned int num = 123;
    EXPECT_EQ(decimal.before, num);
    EXPECT_EQ(decimal.frac, "");
    EXPECT_FALSE(decimal.sign);
}

// 测试不同长度的小数
TEST(DecimalTest, AddDifferentFractionLengths) {
    Decimal decimal1("123.4");
    Decimal decimal2("0.05");
    Decimal result = decimal1.add(decimal2);
    EXPECT_EQ(result.toString(), "123.45");
}

TEST(DecimalTest, SubtractDifferentFractionLengths) {
    Decimal decimal1("123.456");
    Decimal decimal2("123.4");
    Decimal result = decimal1.subtract(decimal2);
    EXPECT_EQ(result.toString(), "0.056");
}

// 测试大数
TEST(DecimalTest, LargeNumbers) {
    Decimal decimal1("12345678912345678.12345678901234567890");
    Decimal decimal2("98765432198765432.98765432109876543210");
    Decimal result = decimal1.add(decimal2);
    EXPECT_EQ(result.toString(), "111111111111111111.111111110111111111");
}