#include <gtest/gtest.h>
#include "ccapi_cpp/ccapi_ws_connection.h" // 假设头文件路径正确
#include <map>
#include <vector>

// 使用 ccapi 命名空间
using namespace ccapi;

// 测试构造函数
TEST(WsConnectionTest, Constructor) {
  std::string url = "wss://example.com";
  std::string group = "group1";
  std::vector<Subscription> subscriptions; // 假设 Subscription 类型已经实现
  std::map<std::string, std::string> credentials = {{"apiKey", "12345"}};
  std::shared_ptr<beast::websocket::stream<beast::ssl_stream<beast::tcp_stream> > > streamPtr;
  WsConnection connection(url, group, subscriptions, credentials, streamPtr);

  EXPECT_EQ(connection.getUrl(), url);
  EXPECT_EQ(connection.group, group);
  EXPECT_EQ(connection.subscriptionList.size(), subscriptions.size());
  EXPECT_EQ(connection.credential.at("apiKey"), "12345");
  EXPECT_EQ(connection.status, WsConnection::Status::UNKNOWN);
}

// 测试 toString 方法
TEST(WsConnectionTest, ToString) {
  std::string url = "wss://example.com";
  std::string group = "group1";
  std::vector<Subscription> subscriptions; // 假设 Subscription 类型已经实现
  std::map<std::string, std::string> credentials = {{"apiKey", "12345"}};
  std::shared_ptr<beast::websocket::stream<beast::ssl_stream<beast::tcp_stream> > > streamPtr;
  WsConnection connection(url, group, subscriptions, credentials, streamPtr);
  std::string expectedSubstring = "url = wss://example.com, group = group1";

  std::string connectionString = connection.toString();
  EXPECT_NE(connectionString.find(expectedSubstring), std::string::npos); // 验证输出包含预期内容
}

// 测试 setUrl 方法
TEST(WsConnectionTest, SetUrl) {
  WsConnection connection;
  connection.setUrl("wss://example.com:8080/path?query");

  EXPECT_EQ(connection.getUrl(), "wss://example.com:8080/path?query");
  EXPECT_EQ(connection.host, "example.com");
  EXPECT_EQ(connection.port, "8080");
  EXPECT_EQ(connection.path, "/path?query");
}

// 测试 appendUrlPart 方法
TEST(WsConnectionTest, AppendUrlPart) {
  WsConnection connection;
  connection.setUrl("wss://example.com");
  connection.appendUrlPart("/additional");

  EXPECT_EQ(connection.getUrl(), "wss://example.com/additional");
  EXPECT_EQ(connection.path, "/additional");
}

// 测试 statusToString 方法
TEST(WsConnectionTest, StatusToString) {
  EXPECT_EQ(WsConnection::statusToString(WsConnection::Status::UNKNOWN), "UNKNOWN");
  EXPECT_EQ(WsConnection::statusToString(WsConnection::Status::CONNECTING), "CONNECTING");
  EXPECT_EQ(WsConnection::statusToString(WsConnection::Status::OPEN), "OPEN");
  EXPECT_EQ(WsConnection::statusToString(WsConnection::Status::FAILED), "FAILED");
  EXPECT_EQ(WsConnection::statusToString(WsConnection::Status::CLOSING), "CLOSING");
  EXPECT_EQ(WsConnection::statusToString(WsConnection::Status::CLOSED), "CLOSED");
}

// 测试默认构造函数
TEST(WsConnectionTest, DefaultConstructor) {
  WsConnection connection;

  EXPECT_EQ(connection.getUrl(), "");
  EXPECT_EQ(connection.group, "");
  EXPECT_TRUE(connection.subscriptionList.empty());
  EXPECT_TRUE(connection.credential.empty());
  EXPECT_EQ(connection.status, WsConnection::Status::UNKNOWN);
  EXPECT_TRUE(connection.headers.empty());
}

