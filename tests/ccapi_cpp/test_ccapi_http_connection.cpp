#include <gtest/gtest.h>
#include <boost/beast/core.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/asio.hpp>
#include <memory>
#include <string>
#include "ccapi_cpp/ccapi_http_connection.h"

using namespace ccapi;
namespace beast = boost::beast;

// 测试用例
TEST(HttpConnectionTest, ConstructorInitializesMembers) {
  // 准备测试数据
  std::string testHost = "example.com";
  std::string testPort = "443";

  // 创建一个模拟的 SSL stream
  auto ioContext = std::make_shared<boost::asio::io_context>();
  auto sslContext = std::make_shared<boost::asio::ssl::context>(boost::asio::ssl::context::tlsv12_client);
  auto stream = std::make_shared<beast::ssl_stream<beast::tcp_stream>>(*ioContext, *sslContext);

  // 创建 HttpConnection 实例
  HttpConnection connection(testHost, testPort, stream);

  // 验证成员变量
  EXPECT_EQ(connection.host, testHost);
  EXPECT_EQ(connection.port, testPort);
  EXPECT_EQ(connection.streamPtr, stream);
}

TEST(HttpConnectionTest, ToStringReturnsFormattedString) {
  // 准备测试数据
  std::string testHost = "example.com";
  std::string testPort = "443";

  // 创建一个模拟的 SSL stream
  auto ioContext = std::make_shared<boost::asio::io_context>();
  auto sslContext = std::make_shared<boost::asio::ssl::context>(boost::asio::ssl::context::tlsv12_client);
  auto stream = std::make_shared<beast::ssl_stream<beast::tcp_stream>>(*ioContext, *sslContext);

  // 创建 HttpConnection 实例
  HttpConnection connection(testHost, testPort, stream);

  // 检查 toString 方法
  std::string toStringOutput = connection.toString();
  EXPECT_NE(toStringOutput.find("HttpConnection [host = example.com, port = 443"), std::string::npos);
  EXPECT_NE(toStringOutput.find("lastReceiveDataTp ="), std::string::npos);
}

TEST(HttpConnectionTest, DefaultLastReceiveDataTp) {
  // 准备测试数据
  std::string testHost = "example.com";
  std::string testPort = "443";

  // 创建一个模拟的 SSL stream
  auto ioContext = std::make_shared<boost::asio::io_context>();
  auto sslContext = std::make_shared<boost::asio::ssl::context>(boost::asio::ssl::context::tlsv12_client);
  auto stream = std::make_shared<beast::ssl_stream<beast::tcp_stream>>(*ioContext, *sslContext);

  // 创建 HttpConnection 实例
  HttpConnection connection(testHost, testPort, stream);

  // 验证 lastReceiveDataTp 的默认值
  EXPECT_EQ(connection.lastReceiveDataTp.time_since_epoch().count(), 0);
}
