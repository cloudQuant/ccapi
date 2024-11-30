#include <gtest/gtest.h>

#include "../../include/ccapi_cpp/ccapi_element.h"

using namespace ccapi;

// 插入操作测试
TEST(ElementTest, InsertNameValuePair) {
    Element element;
    element.insert("key1", "value1");
    EXPECT_EQ(element.getValue("key1"), "value1");
}

TEST(ElementTest, InsertTagValuePair) {
    Element element(true);
    element.insert(1, "value1");
    EXPECT_EQ(element.getValue(1), "value1");
}

TEST(ElementTest, EmplaceNameValuePair) {
    Element element;
    std::string key = "key1";
    std::string value = "value1";
    element.emplace(key, value);
    EXPECT_EQ(element.getValue("key1"), "value1");
}

TEST(ElementTest, EmplaceTagValuePair) {
    Element element(true);
    int tag = 1;
    std::string value = "value1";
    element.emplace(tag, value);
    EXPECT_EQ(element.getValue(1), "value1");
}

// 获取值测试
TEST(ElementTest, GetValueWithDefault) {
    Element element;
    EXPECT_EQ(element.getValue("nonexistent", "default"), "default");
}

TEST(ElementTest, GetTagValueWithDefault) {
    Element element(true);
    EXPECT_EQ(element.getValue(99, "default"), "default");
}

// 判断键是否存在测试
TEST(ElementTest, HasNameKey) {
    Element element;
    element.insert("key1", "value1");
    EXPECT_TRUE(element.has("key1"));
    EXPECT_FALSE(element.has("key2"));
}

TEST(ElementTest, HasTagKey) {
    Element element(true);
    element.insert(1, "value1");
    EXPECT_TRUE(element.has(1));
    EXPECT_FALSE(element.has(2));
}

// 边界情况测试
TEST(ElementTest, InsertEmptyNameValuePair) {
    Element element;
    element.insert("", "");
    EXPECT_EQ(element.getValue(""), "");
}

TEST(ElementTest, InsertEmptyTagValuePair) {
    Element element(true);
    element.insert(0, "");
    EXPECT_EQ(element.getValue(0), "");
}

TEST(ElementTest, InsertSameNameMultipleTimes) {
    Element element;
    element.insert("key1", "value1");
    element.insert("key1", "value2");
    EXPECT_EQ(element.getValue("key1"), "value1");
}

TEST(ElementTest, InsertSameTagMultipleTimes) {
    Element element(true);
    element.insert(1, "value1");
    element.insert(1, "value2");
    EXPECT_EQ(element.getValue(1), "value1");
}

// 输出字符串测试
TEST(ElementTest, ToStringWithoutFix) {
    Element element;
    element.insert("key1", "value1");
    EXPECT_EQ(element.toString(), "Element [nameValueMap = {key1=value1}]");
}

TEST(ElementTest, ToStringWithFix) {
    Element element(true);
    element.insert(1, "value1");
    EXPECT_EQ(element.toString(), "Element [tagValueMap = {1=value1}]");
}

TEST(ElementTest, ToStringPrettyWithoutFix) {
    Element element;
    element.insert("key1", "value1");
    EXPECT_EQ(element.toStringPretty(), "Element [\n  nameValueMap = {\n    key1 = value1\n  }\n]");
}

TEST(ElementTest, ToStringPrettyWithFix) {
    Element element(true);
    element.insert(1, "value1");
    EXPECT_EQ(element.toStringPretty(), "Element [\n  tagValueMap = {\n    1 = value1\n  }\n]");
}

// Map返回值测试
TEST(ElementTest, GetNameValueMap) {
    Element element;
    element.insert("key1", "value1");
    element.insert("key2", "value2");

    auto nameValueMap = element.getNameValueMap();
    std::size_t num = 2;
    EXPECT_EQ(nameValueMap.size(), num);
    EXPECT_EQ(nameValueMap.at("key1"), "value1");
    EXPECT_EQ(nameValueMap.at("key2"), "value2");
}

TEST(ElementTest, GetTagValueMap) {
    Element element(true);
    element.insert(1, "value1");
    element.insert(2, "value2");

    auto tagValueMap = element.getTagValueMap();
    std::size_t num = 2;
    EXPECT_EQ(tagValueMap.size(), num);
    EXPECT_EQ(tagValueMap.at(1), "value1");
    EXPECT_EQ(tagValueMap.at(2), "value2");
}

//// isFix 属性测试
//TEST(ElementTest, IsFixFalse) {
//    Element element;
//    EXPECT_FALSE(element.getIsFix());
//}
//
//TEST(ElementTest, IsFixTrue) {
//    Element element(true);
//    EXPECT_TRUE(element.getIsFix());
//}

// 综合测试
TEST(ElementTest, ComplexInsertAndRetrieval) {
    Element element;
    element.insert("key1", "value1");
    element.insert(1, "value1");
    element.insert("key2", "value2");
    element.insert(2, "value2");

    EXPECT_EQ(element.getValue("key1"), "value1");
    EXPECT_EQ(element.getValue(1), "value1");
    EXPECT_EQ(element.getValue("key2"), "value2");
    EXPECT_EQ(element.getValue(2), "value2");

    EXPECT_TRUE(element.has("key1"));
    EXPECT_TRUE(element.has(1));
    EXPECT_TRUE(element.has("key2"));
    EXPECT_TRUE(element.has(2));
}

TEST(ElementTest, MultipleInsertsWithEdgeCases) {
    Element element;
    element.insert("", "emptyKey");
    element.insert("key1", "");
    element.insert(0, "zeroTag");
    element.insert(1, "");

    EXPECT_EQ(element.getValue(""), "emptyKey");
    EXPECT_EQ(element.getValue("key1"), "");
    EXPECT_EQ(element.getValue(0), "zeroTag");
    EXPECT_EQ(element.getValue(1), "");
}


