#include <gtest/gtest.h>
#include "ccapi_cpp/ccapi_url.h"

namespace ccapi {

// 测试构造函数解析 URL 字符串
TEST(UrlTest, ConstructorFromString) {
  Url url("https://example.com:8080/path?query=1");
  EXPECT_EQ(url.protocol, "https:");
  EXPECT_EQ(url.host, "example.com");
  EXPECT_EQ(url.port, ":8080");
  EXPECT_EQ(url.target, "/path?query=1");
}

// 测试构造函数直接初始化各字段
TEST(UrlTest, ConstructorFromFields) {
  Url url("https:", "example.com", ":8080", "/path?query=1");
  EXPECT_EQ(url.protocol, "https:");
  EXPECT_EQ(url.host, "example.com");
  EXPECT_EQ(url.port, ":8080");
  EXPECT_EQ(url.target, "/path?query=1");
}

// 测试 toString 方法
TEST(UrlTest, ToString) {
  Url url("https:", "example.com", ":8080", "/path?query=1");
  EXPECT_EQ(url.toString(), "Url [protocol = https:, host = example.com, port = :8080, target = /path?query=1]");
}

// 测试 URL 编码
TEST(UrlTest, UrlEncode) {
  std::string input = "hello world!";
  std::string expected = "hello%20world%21";
  EXPECT_EQ(Url::urlEncode(input), expected);
}

// 测试 URL 解码
TEST(UrlTest, UrlDecode) {
  std::string input = "hello%20world%21";
  std::string expected = "hello world!";
  EXPECT_EQ(Url::urlDecode(input), expected);
}

// 测试查询字符串转换为 map
TEST(UrlTest, ConvertQueryStringToMap) {
  std::string query = "key1=value1&key2=value2";
  auto result = Url::convertQueryStringToMap(query);
  EXPECT_EQ(result["key1"], "value1");
  EXPECT_EQ(result["key2"], "value2");
}

// 测试 map 转换为查询字符串
TEST(UrlTest, ConvertMapToQueryString) {
  std::map<std::string, std::string> input = {{"key1", "value1"}, {"key2", "value2"}};
  std::string expected = "key1=value1&key2=value2";
  EXPECT_EQ(Url::convertMapToQueryString(input), expected);
}

TEST(UrlTest, ConvertMapToQueryString2) {
  std::map<std::string, std::string> input = {{"key1", "value1"}, {"key2", "value2"}, {"key3","value3"}};
  std::string expected = "key1=value1&key2=value2&key3=value3";
  EXPECT_EQ(Url::convertMapToQueryString(input), expected);
}

// 测试 map 转换为表单 URL 编码
TEST(UrlTest, ConvertMapToFormUrlEncoded) {
  std::map<std::string, std::string> input = {{"key1", "value1"}, {"key2", "value2"}};
  std::string expected = "key1=value1&key2=value2";
  EXPECT_EQ(Url::convertMapToFormUrlEncoded(input), expected);
}

// 测试表单 URL 编码转换为 map
TEST(UrlTest, ConvertFormUrlEncodedToMap) {
  std::string input = "key1=value1&key2=value2";
  auto result = Url::convertFormUrlEncodedToMap(input);
  EXPECT_EQ(result["key1"], "value1");
  EXPECT_EQ(result["key2"], "value2");
}

}  // namespace ccapi
