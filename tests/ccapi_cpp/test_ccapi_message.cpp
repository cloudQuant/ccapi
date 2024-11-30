#include "gtest/gtest.h"
#include "ccapi_cpp/ccapi_message.h"

using namespace ccapi;

class MessageTest : public ::testing::Test {
 protected:
  Message message;
};

// Test overall behavior
TEST_F(MessageTest, DefaultConstructor) {
  EXPECT_EQ(message.getType(), Message::Type::UNKNOWN);
  EXPECT_EQ(message.getRecapType(), Message::RecapType::UNKNOWN);
  EXPECT_EQ(message.getElementList().size(), 0);
  EXPECT_EQ(message.getCorrelationIdList().size(), 0);
  EXPECT_EQ(message.getSecondaryCorrelationIdMap().size(), 0);
  EXPECT_EQ(message.getTime(), TimePoint(std::chrono::seconds(0)));
  EXPECT_EQ(message.getTimeReceived(), TimePoint(std::chrono::seconds(0)));
}

// Test typeToString function
TEST_F(MessageTest, TypeToString) {
  EXPECT_EQ(Message::typeToString(Message::Type::UNKNOWN), "UNKNOWN");
  EXPECT_EQ(Message::typeToString(Message::Type::MARKET_DATA_EVENTS_MARKET_DEPTH), "MARKET_DATA_EVENTS_MARKET_DEPTH");
  EXPECT_EQ(Message::typeToString(Message::Type::AUTHORIZATION_SUCCESS), "AUTHORIZATION_SUCCESS");
}

// Test recapTypeToString function
TEST_F(MessageTest, RecapTypeToString) {
  EXPECT_EQ(Message::recapTypeToString(Message::RecapType::UNKNOWN), "UNKNOWN");
  EXPECT_EQ(Message::recapTypeToString(Message::RecapType::SOLICITED), "SOLICITED");
  EXPECT_EQ(Message::recapTypeToString(Message::RecapType::NONE), "NONE");
}

// Test set and get element list
TEST_F(MessageTest, ElementList) {
  std::vector<Element> elements = {Element(), Element()};
  message.setElementList(elements);
  EXPECT_EQ(message.getElementList().size(), 2);

  std::vector<Element> elementsNew = {Element()};
  message.setElementList(std::move(elementsNew));
  EXPECT_EQ(message.getElementList().size(), 1);
}

// Test set and get correlation ID list
TEST_F(MessageTest, CorrelationIdList) {
  std::vector<std::string> ids = {"id1", "id2"};
  message.setCorrelationIdList(ids);
  EXPECT_EQ(message.getCorrelationIdList().size(), 2);
  EXPECT_EQ(message.getCorrelationIdList()[0], "id1");
}

// Test set and get secondary correlation ID map
TEST_F(MessageTest, SecondaryCorrelationIdMap) {
  std::map<std::string, std::string> idMap = {{"key1", "value1"}, {"key2", "value2"}};
  message.setSecondaryCorrelationIdMap(idMap);
  EXPECT_EQ(message.getSecondaryCorrelationIdMap().size(), 2);
  EXPECT_EQ(message.getSecondaryCorrelationIdMap().at("key1"), "value1");
}

// Test time setters and getters
TEST_F(MessageTest, Time) {
  TimePoint newTime = std::chrono::system_clock::now();
  message.setTime(newTime);
  EXPECT_EQ(message.getTime(), newTime);
}

// Test timeReceived setters and getters
TEST_F(MessageTest, TimeReceived) {
  TimePoint newTimeReceived = std::chrono::system_clock::now();
  message.setTimeReceived(newTimeReceived);
  EXPECT_EQ(message.getTimeReceived(), newTimeReceived);
}

// Test toString
TEST_F(MessageTest, ToString) {
  message.setType(Message::Type::MARKET_DATA_EVENTS_TRADE);
  EXPECT_NE(message.toString().find("MARKET_DATA_EVENTS_TRADE"), std::string::npos);
}

// Test toStringPretty
TEST_F(MessageTest, ToStringPretty) {
  message.setType(Message::Type::MARKET_DATA_EVENTS_TRADE);
  EXPECT_NE(message.toStringPretty().find("MARKET_DATA_EVENTS_TRADE"), std::string::npos);
}
