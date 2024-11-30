#include <gtest/gtest.h>
#include <memory>
#include <future>
#include <string>
#include "ccapi_cpp/ccapi_http_retry.h"

using namespace ccapi;

// 测试用例
TEST(HttpRetryTest, DefaultConstructorInitializesMembers) {
  // 创建 HttpRetry 的默认实例
  HttpRetry httpRetry;

  // 验证默认构造函数是否正确初始化成员变量
  EXPECT_EQ(httpRetry.numRetry, 0);
  EXPECT_EQ(httpRetry.numRedirect, 0);
  EXPECT_EQ(httpRetry.promisePtr, nullptr);
}

TEST(HttpRetryTest, ParameterizedConstructorInitializesMembers) {
  // 创建测试数据
  int testNumRetry = 3;
  int testNumRedirect = 2;
  auto testPromisePtr = std::make_shared<std::promise<void>>();

  // 使用参数化构造函数创建 HttpRetry 实例
  HttpRetry httpRetry(testNumRetry, testNumRedirect, "", testPromisePtr);

  // 验证成员变量是否正确初始化
  EXPECT_EQ(httpRetry.numRetry, testNumRetry);
  EXPECT_EQ(httpRetry.numRedirect, testNumRedirect);
  EXPECT_EQ(httpRetry.promisePtr, testPromisePtr);
}

TEST(HttpRetryTest, ToStringReturnsFormattedString) {
  // 创建测试数据
  int testNumRetry = 1;
  int testNumRedirect = 1;
  auto testPromisePtr = std::make_shared<std::promise<void>>();

  // 使用参数化构造函数创建 HttpRetry 实例
  HttpRetry httpRetry(testNumRetry, testNumRedirect, "", testPromisePtr);

  // 检查 toString 方法的输出
  std::string toStringOutput = httpRetry.toString();
  EXPECT_NE(toStringOutput.find("numRetry = 1"), std::string::npos);
  EXPECT_NE(toStringOutput.find("numRedirect = 1"), std::string::npos);
  EXPECT_NE(toStringOutput.find("promisePtr = "), std::string::npos);
}

