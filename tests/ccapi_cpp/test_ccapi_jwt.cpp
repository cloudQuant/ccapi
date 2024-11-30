#include <gtest/gtest.h>
#include "ccapi_cpp/ccapi_jwt.h"

using namespace ccapi;

// 测试用例
TEST(JwtTest, GenerateValidToken) {
  // 准备测试数据
  std::string secret = "test_secret";
  std::string payload = R"({"user":"test_user","exp":1700000000})";

  // 使用 SHA256 算法生成 JWT
  std::string token = Jwt::generate(Hmac::ShaVersion::SHA256, secret, payload);

  // 检查生成的 JWT 格式
  size_t firstDot = token.find('.');
  size_t secondDot = token.find('.', firstDot + 1);

  // 验证 JWT 格式
  EXPECT_NE(firstDot, std::string::npos);  // 必须包含第一个点
  EXPECT_NE(secondDot, std::string::npos); // 必须包含第二个点
  EXPECT_LT(firstDot, secondDot);          // 第一个点必须出现在第二个点之前

  // 验证 JWT 的头部
  std::string headerEncoded = token.substr(0, firstDot);
  std::string headerDecoded = UtilAlgorithm::base64UrlDecode(headerEncoded);
  EXPECT_EQ(headerDecoded, "{\"alg\":\"HS256\",\"typ\":\"JWT\"}");

  // 验证 JWT 的载荷
  std::string payloadEncoded = token.substr(firstDot + 1, secondDot - firstDot - 1);
  std::string payloadDecoded = UtilAlgorithm::base64UrlDecode(payloadEncoded);
  EXPECT_EQ(payloadDecoded, payload);
}

TEST(JwtTest, UnsupportedShaVersion) {
  // 准备测试数据
  std::string secret = "test_secret";
  std::string payload = "{\"user\":\"test_user\",\"exp\":1700000000}";

  // 使用不支持的 SHA 版本
  try {
    Jwt::generate(static_cast<Hmac::ShaVersion>(999), secret, payload);
    FAIL() << "Expected fatal logger call for unsupported SHA version";
  } catch (...) {
    SUCCEED();
  }
}

TEST(JwtTest, EmptySecretAndPayload) {
  // 准备测试数据
  std::string secret = "";
  std::string payload = "";

  // 使用 SHA256 算法生成 JWT
  std::string token = Jwt::generate(Hmac::ShaVersion::SHA256, secret, payload);

  // 验证生成的 JWT 格式
  size_t firstDot = token.find('.');
  size_t secondDot = token.find('.', firstDot + 1);

  EXPECT_NE(firstDot, std::string::npos);
  EXPECT_NE(secondDot, std::string::npos);
  EXPECT_LT(firstDot, secondDot);
}

TEST(JwtTest, PayloadWithSpecialCharacters) {
  // 准备包含特殊字符的载荷
  std::string secret = "test_secret";
  std::string payload = "{\"data\":\"special_characters_@!#$%^&*()\"}";

  // 使用 SHA256 算法生成 JWT
  std::string token = Jwt::generate(Hmac::ShaVersion::SHA256, secret, payload);

  // 检查生成的 JWT 格式
  size_t firstDot = token.find('.');
  size_t secondDot = token.find('.', firstDot + 1);

  EXPECT_NE(firstDot, std::string::npos);
  EXPECT_NE(secondDot, std::string::npos);

  // 验证载荷是否正确
  std::string payloadEncoded = token.substr(firstDot + 1, secondDot - firstDot - 1);
  std::string payloadDecoded = UtilAlgorithm::base64UrlDecode(payloadEncoded);
  EXPECT_EQ(payloadDecoded, payload);
}
