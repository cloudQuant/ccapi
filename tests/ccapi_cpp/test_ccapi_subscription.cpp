#include <gtest/gtest.h>
#include <map>
#include <string>
#include "ccapi_cpp/ccapi_subscription.h"

namespace ccapi {

// 测试默认构造函数
TEST(SubscriptionTest, DefaultConstructor) {
  Subscription subscription;
  EXPECT_EQ(subscription.getCorrelationId(), "");
  EXPECT_EQ(subscription.getExchange(), "");
  EXPECT_EQ(subscription.getInstrument(), "");
  EXPECT_EQ(subscription.getField(), "");
  EXPECT_EQ(subscription.getServiceName(), "");
}

// 测试参数化构造函数
TEST(SubscriptionTest, ParameterizedConstructor) {
  std::string exchange = "binance";
  std::string instrument = "BTC-USD";
  std::string field = "TRADE";
  std::string options = "option1=value1&option2=value2";
  std::string correlationId = "correlation123";
  std::map<std::string, std::string> credential = {{"key", "value"}};

  Subscription subscription(exchange, instrument, field, options, correlationId, credential);

  EXPECT_EQ(subscription.getExchange(), exchange);
  EXPECT_EQ(subscription.getInstrument(), instrument);
  EXPECT_EQ(subscription.getField(), field);
  EXPECT_EQ(subscription.getCorrelationId(), correlationId);
  EXPECT_EQ(subscription.getOptionMap().at("option1"), "value1");
  EXPECT_EQ(subscription.getOptionMap().at("option2"), "value2");
  EXPECT_EQ(subscription.getCredential().at("key"), "value");
}

// 测试字段和选项序列化
TEST(SubscriptionTest, SerializedOptionsAndCredential) {
  std::string options = "depth=10&interval=100";
  std::map<std::string, std::string> credential = {{"apiKey", "abcd1234"}, {"secretKey", "xyz789"}};
  Subscription subscription("binance", "ETH-USD", "TRADE", options, "", credential);
  std::string result = subscription.getSerializedOptions();
  EXPECT_TRUE(result.find(options)!=std::string::npos);
  EXPECT_EQ(subscription.getSerializedCredential(), "{apiKey=abcd1234, secretKey=xyz789}");
}

// 测试状态字符串转换
TEST(SubscriptionTest, StatusToString) {
  EXPECT_EQ(Subscription::statusToString(Subscription::Status::UNKNOWN), "UNKNOWN");
  EXPECT_EQ(Subscription::statusToString(Subscription::Status::SUBSCRIBING), "SUBSCRIBING");
  EXPECT_EQ(Subscription::statusToString(Subscription::Status::SUBSCRIBED), "SUBSCRIBED");
  EXPECT_EQ(Subscription::statusToString(Subscription::Status::UNSUBSCRIBING), "UNSUBSCRIBING");
  EXPECT_EQ(Subscription::statusToString(Subscription::Status::UNSUBSCRIBED), "UNSUBSCRIBED");
}

// 测试字符串表示
TEST(SubscriptionTest, ToString) {
  Subscription subscription("binance", "BTC-USD", "TRADE", "depth=5", "corr123", {{"key", "secret"}});
  std::string output = subscription.toString();
  std::cout << "toString output " << output << std::endl;
  EXPECT_TRUE(output.find("exchange = binance") != std::string::npos);
  EXPECT_TRUE(output.find("instrument = BTC-USD") != std::string::npos);
  EXPECT_TRUE(output.find("field = TRADE") != std::string::npos);
  EXPECT_TRUE(output.find("depth=5") != std::string::npos);
  EXPECT_TRUE(output.find("correlationId = corr123") != std::string::npos);
}

// 测试时间相关方法
TEST(SubscriptionTest, TimeSent) {
  Subscription subscription;
  auto now = std::chrono::system_clock::now();
  subscription.setTimeSent(now);

  EXPECT_EQ(subscription.getTimeSent(), now);
  EXPECT_FALSE(subscription.getTimeSentISO().empty());
}

}  // namespace ccapi