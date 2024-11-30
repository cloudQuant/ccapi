#include <gtest/gtest.h>
#include "ccapi_cpp/ccapi_request.h"
#include <map>

using namespace ccapi;

// 测试Request类的构造函数
TEST(RequestTest, ConstructorTest) {
  // 创建一个Request对象
  Request request(Request::Operation::GET_RECENT_TRADES, "Binance", "BTC-USD");

  // 检查属性是否正确设置
  EXPECT_EQ(request.getOperation(), Request::Operation::GET_RECENT_TRADES);
  EXPECT_EQ(request.getExchange(), "Binance");
  EXPECT_EQ(request.getInstrument(), "BTC-USD");
}

// 测试operationToString方法
TEST(RequestTest, OperationToStringTest) {
  // 检查不同操作类型对应的字符串
  EXPECT_EQ(Request::operationToString(Request::Operation::CUSTOM), "CUSTOM");
  EXPECT_EQ(Request::operationToString(Request::Operation::GENERIC_PUBLIC_REQUEST), "GENERIC_PUBLIC_REQUEST");
  EXPECT_EQ(Request::operationToString(Request::Operation::CREATE_ORDER), "CREATE_ORDER");
}

// 测试getter函数
TEST(RequestTest, GetterTest) {
  Request request(Request::Operation::GET_ACCOUNTS, "Binance", "BTC-USD", "12345");

  // 检查getter函数
  EXPECT_EQ(request.getCorrelationId(), "12345");
  EXPECT_EQ(request.getExchange(), "Binance");
  EXPECT_EQ(request.getInstrument(), "BTC-USD");
  EXPECT_EQ(request.getServiceName(), "execution_management");
}

// 测试appendParam函数
TEST(RequestTest, AppendParamTest) {
  Request request;
  // 添加参数
  std::map<std::string, std::string> param = {{"key1", "value1"}, {"key2", "value2"}};
  request.appendParam(param);

  // 获取参数列表
  const auto& paramList = request.getParamList();

  // 输出paramList的大小和内容，以便调试
  std::cout << "paramList size: " << paramList.size() << std::endl;
  if (!paramList.empty()) {
    std::cout << "First param: " << std::endl;
    for (const auto& p : paramList[0]) {
      std::cout << p.first << " = " << p.second << std::endl;
    }
  }

  // 检查参数是否已被正确添加
  ASSERT_EQ(paramList.size(), 1);  // 确保只有一个元素
  auto v0 = paramList[0];
  EXPECT_EQ(v0["key1"], "value1");
  EXPECT_EQ(v0["key2"], "value2");
}

// 测试toString函数
TEST(RequestTest, ToStringTest) {
  Request request(Request::Operation::GET_RECENT_TRADES, "Binance", "BTC-USD");
  std::string result = request.toString();
  EXPECT_TRUE(result.find("exchange = Binance")!=std::string::npos);
  EXPECT_TRUE(result.find("instrument = BTC-USD")!=std::string::npos);
  EXPECT_TRUE(result.find("serviceName = market_data")!=std::string::npos);
  EXPECT_TRUE(result.find("operation = GET_RECENT_TRADES")!=std::string::npos);
  EXPECT_TRUE(result.find("timeSent = 1970-01-01T00:00:00.000000000Z")!=std::string::npos);
}

