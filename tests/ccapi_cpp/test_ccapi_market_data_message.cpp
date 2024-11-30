#include <gtest/gtest.h>
#include "ccapi_cpp/ccapi_market_data_message.h"

using namespace ccapi;

// Test recapTypeToString function
TEST(MarketDataMessageTest, RecapTypeToString) {
  EXPECT_EQ(MarketDataMessage::recapTypeToString(MarketDataMessage::RecapType::UNKNOWN), "UNKNOWN");
  EXPECT_EQ(MarketDataMessage::recapTypeToString(MarketDataMessage::RecapType::NONE), "NONE");
  EXPECT_EQ(MarketDataMessage::recapTypeToString(MarketDataMessage::RecapType::SOLICITED), "SOLICITED");
}

// Test dataTypeToString function
TEST(MarketDataMessageTest, DataTypeToString) {
  EXPECT_EQ(MarketDataMessage::dataTypeToString(MarketDataMessage::DataType::BID), "BID");
  EXPECT_EQ(MarketDataMessage::dataTypeToString(MarketDataMessage::DataType::ASK), "ASK");
  EXPECT_EQ(MarketDataMessage::dataTypeToString(MarketDataMessage::DataType::TRADE), "TRADE");
  EXPECT_EQ(MarketDataMessage::dataTypeToString(MarketDataMessage::DataType::AGG_TRADE), "AGG_TRADE");
  EXPECT_EQ(MarketDataMessage::dataTypeToString(MarketDataMessage::DataType::CANDLESTICK), "CANDLESTICK");
}

// Test dataFieldTypeToString function
TEST(MarketDataMessageTest, DataFieldTypeToString) {
  EXPECT_EQ(MarketDataMessage::dataFieldTypeToString(MarketDataMessage::DataFieldType::PRICE), "PRICE");
  EXPECT_EQ(MarketDataMessage::dataFieldTypeToString(MarketDataMessage::DataFieldType::SIZE), "SIZE");
  EXPECT_EQ(MarketDataMessage::dataFieldTypeToString(MarketDataMessage::DataFieldType::TRADE_ID), "TRADE_ID");
  EXPECT_EQ(MarketDataMessage::dataFieldTypeToString(MarketDataMessage::DataFieldType::VOLUME), "VOLUME");
  EXPECT_EQ(MarketDataMessage::dataFieldTypeToString(MarketDataMessage::DataFieldType::QUOTE_VOLUME), "QUOTE_VOLUME");
}

// Test dataToString function
TEST(MarketDataMessageTest, DataToString) {
  MarketDataMessage::TypeForData data = {
      {MarketDataMessage::DataType::BID, {
                                             {{MarketDataMessage::DataFieldType::PRICE, "100.5"}, {MarketDataMessage::DataFieldType::SIZE, "10"}},
                                             {{MarketDataMessage::DataFieldType::PRICE, "101.0"}, {MarketDataMessage::DataFieldType::SIZE, "15"}}
                                         }},
      {MarketDataMessage::DataType::ASK, {
                                             {{MarketDataMessage::DataFieldType::PRICE, "102.5"}, {MarketDataMessage::DataFieldType::SIZE, "8"}}
                                         }}
  };
  std::string expected = "{BID=[ {PRICE=100.5, SIZE=10}, {PRICE=101.0, SIZE=15} ], ASK=[ {PRICE=102.5, SIZE=8} ]}";
  EXPECT_EQ(MarketDataMessage::dataToString(data), expected);
}

// Test typeToString function
TEST(MarketDataMessageTest, TypeToString) {
  EXPECT_EQ(MarketDataMessage::typeToString(MarketDataMessage::Type::UNKNOWN), "UNKNOWN");
  EXPECT_EQ(MarketDataMessage::typeToString(MarketDataMessage::Type::MARKET_DATA_EVENTS_MARKET_DEPTH), "MARKET_DATA_EVENTS_MARKET_DEPTH");
  EXPECT_EQ(MarketDataMessage::typeToString(MarketDataMessage::Type::MARKET_DATA_EVENTS_TRADE), "MARKET_DATA_EVENTS_TRADE");
}

// Test toString method
TEST(MarketDataMessageTest, ToString) {
  MarketDataMessage message;
  message.type = MarketDataMessage::Type::MARKET_DATA_EVENTS_TRADE;
  message.recapType = MarketDataMessage::RecapType::SOLICITED;
  message.tp = TimePoint(std::chrono::seconds(1633046400));
  message.exchangeSubscriptionId = "test_subscription";
  message.data = {
      {MarketDataMessage::DataType::TRADE, {
                                               {{MarketDataMessage::DataFieldType::PRICE, "50000"}, {MarketDataMessage::DataFieldType::SIZE, "0.01"}}
                                           }}
  };
  std::string expected = "MarketDataMessage [type = MARKET_DATA_EVENTS_TRADE, recapType = SOLICITED, tp = (1633046400,0), exchangeSubscriptionId = test_subscription, data = {TRADE=[ {PRICE=50000, SIZE=0.01} ]}]";
  EXPECT_EQ(message.toString(), expected);
}
