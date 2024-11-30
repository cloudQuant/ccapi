#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <memory>
#include "ccapi_cpp/ccapi_subscription.h"
#include "ccapi_cpp/ccapi_fix_connection.h"

using namespace ccapi;

// 测试用例
TEST(FixConnectionTest, ConstructorInitializesFieldsCorrectly) {
  // 准备输入数据
  std::string host = "fix.example.com";
  std::string port = "8080";
  Subscription subscription("exchange1", "BTC/USD", "MARKET_DEPTH", "", "test123");
  auto streamPtr = std::make_shared<std::ostringstream>();

  // 创建 FixConnection 实例
  FixConnection<std::ostringstream> connection(host, port, subscription, streamPtr);

  // 验证字段初始化
  EXPECT_EQ(connection.host, host);
  EXPECT_EQ(connection.port, port);
  EXPECT_EQ(connection.subscription.getCorrelationId(), "test123");
  EXPECT_EQ(connection.id, "test123");
  EXPECT_EQ(connection.url, "fix.example.com:8080");
  EXPECT_EQ(connection.status, FixConnection<std::ostringstream>::Status::UNKNOWN);
  EXPECT_EQ(connection.streamPtr, streamPtr);
}

TEST(FixConnectionTest, ToStringFormatsCorrectly) {
  // 准备输入数据
  std::string host = "fix.example.com";
  std::string port = "8080";
  Subscription subscription("exchange1", "BTC/USD", "MARKET_DEPTH", "", "test123");
  auto streamPtr = std::make_shared<std::ostringstream>();

  // 创建 FixConnection 实例
  FixConnection<std::ostringstream> connection(host, port, subscription, streamPtr);

  // 设置状态
  connection.status = FixConnection<std::ostringstream>::Status::OPEN;

  // 检查 toString 方法输出
  std::string result = connection.toString();

  // 验证 toString 输出中包含的关键信息
  EXPECT_NE(result.find("id = test123"), std::string::npos);
  EXPECT_NE(result.find("host = fix.example.com"), std::string::npos);
  EXPECT_NE(result.find("port = 8080"), std::string::npos);
  EXPECT_NE(result.find("status = OPEN"), std::string::npos);
  EXPECT_NE(result.find("subscription = Subscription [exchange = exchange1"), std::string::npos);
}

TEST(FixConnectionTest, StatusToStringHandlesAllEnums) {
  using Status = FixConnection<std::ostringstream>::Status;

  // 验证每种状态的字符串表示
  EXPECT_EQ(FixConnection<std::ostringstream>::statusToString(Status::UNKNOWN), "UNKNOWN");
  EXPECT_EQ(FixConnection<std::ostringstream>::statusToString(Status::CONNECTING), "CONNECTING");
  EXPECT_EQ(FixConnection<std::ostringstream>::statusToString(Status::OPEN), "OPEN");
  EXPECT_EQ(FixConnection<std::ostringstream>::statusToString(Status::FAILED), "FAILED");
  EXPECT_EQ(FixConnection<std::ostringstream>::statusToString(Status::CLOSING), "CLOSING");
  EXPECT_EQ(FixConnection<std::ostringstream>::statusToString(Status::CLOSED), "CLOSED");
}

TEST(FixConnectionTest, StreamPointerUsage) {
  // 准备输入数据
  std::string host = "fix.example.com";
  std::string port = "8080";
  Subscription subscription("exchange1", "BTC/USD", "MARKET_DEPTH", "", "test123");
  auto streamPtr = std::make_shared<std::ostringstream>();

  // 创建 FixConnection 实例
  FixConnection<std::ostringstream> connection(host, port, subscription, streamPtr);

  // 检查流指针
  *streamPtr << "Test output";
  EXPECT_EQ(streamPtr->str(), "Test output");
}




