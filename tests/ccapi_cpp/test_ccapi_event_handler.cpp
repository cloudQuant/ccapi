#include <gtest/gtest.h>

#include "../../include/ccapi_cpp/ccapi_event.h"
#include "../../include/ccapi_cpp/ccapi_event_handler.h"
#include "../../include/ccapi_cpp/ccapi_logger.h"
//#include "ccapi_cpp/ccapi_session.h"


/*
// 使用自定义的派生类 CustomEventHandler
class CustomEventHandlerTest : public ::testing::Test {
 protected:
  void SetUp() override {
    handler = std::make_shared<CustomEventHandler>();
    sessionPtr = nullptr;  // 假设没有实际的 Session 实例
  }

  std::shared_ptr<CustomEventHandler> handler;
  ccapi::Session* sessionPtr;  // 模拟一个空的 session
};

// 测试 processEvent 正常处理
TEST_F(CustomEventHandlerTest, ProcessEventSuccess) {
  ccapi::Event event;
  event.setType(ccapi::Event::Type::RESPONSE);

  bool result = handler->processEvent(event, sessionPtr);

  EXPECT_TRUE(result);  // 默认应该继续处理
  const auto& events = handler->getProcessedEvents();
  ASSERT_EQ(events.size(), 1);
  EXPECT_EQ(events[0].getType(), ccapi::Event::Type::RESPONSE);
}

// 测试 processEvent 停止事件处理
TEST_F(CustomEventHandlerTest, ProcessEventStopProcessing) {
  ccapi::Event event;
  event.setType(ccapi::Event::Type::SUBSCRIPTION_STATUS);

  handler->setContinueProcessing(false);  // 设置不继续处理事件
  bool result = handler->processEvent(event, sessionPtr);

  EXPECT_FALSE(result);  // 事件处理应该停止
  const auto& events = handler->getProcessedEvents();
  ASSERT_EQ(events.size(), 1);
  EXPECT_EQ(events[0].getType(), ccapi::Event::Type::SUBSCRIPTION_STATUS);
}

// 测试多个事件处理
TEST_F(CustomEventHandlerTest, ProcessMultipleEvents) {
  ccapi::Event event1, event2, event3;
  event1.setType(ccapi::Event::Type::REQUEST_STATUS);
  event2.setType(ccapi::Event::Type::RESPONSE);
  event3.setType(ccapi::Event::Type::AUTHORIZATION_STATUS);

  handler->processEvent(event1, sessionPtr);
  handler->processEvent(event2, sessionPtr);
  handler->processEvent(event3, sessionPtr);

  const auto& events = handler->getProcessedEvents();
  ASSERT_EQ(events.size(), 3);
  EXPECT_EQ(events[0].getType(), ccapi::Event::Type::REQUEST_STATUS);
  EXPECT_EQ(events[1].getType(), ccapi::Event::Type::RESPONSE);
  EXPECT_EQ(events[2].getType(), ccapi::Event::Type::AUTHORIZATION_STATUS);
}

// 测试空事件处理
TEST_F(CustomEventHandlerTest, ProcessEmptyEvent) {
  ccapi::Event emptyEvent;

  bool result = handler->processEvent(emptyEvent, sessionPtr);

  EXPECT_TRUE(result);  // 应该继续处理
  const auto& events = handler->getProcessedEvents();
  ASSERT_EQ(events.size(), 1);
  EXPECT_EQ(events[0].getType(), ccapi::Event::Type::UNKNOWN);  // 默认类型为 UNKNOWN
}

// 测试当 sessionPtr 为 nullptr 时的处理
TEST_F(CustomEventHandlerTest, ProcessEventWithNullSessionPtr) {
  ccapi::Event event;
  event.setType(ccapi::Event::Type::SESSION_STATUS);

  bool result = handler->processEvent(event, nullptr);  // sessionPtr 为 nullptr

  EXPECT_TRUE(result);  // 仍然应该继续处理
  const auto& events = handler->getProcessedEvents();
  ASSERT_EQ(events.size(), 1);
  EXPECT_EQ(events[0].getType(), ccapi::Event::Type::SESSION_STATUS);
}

// 测试连续处理多个事件后停止处理
TEST_F(CustomEventHandlerTest, ProcessEventsThenStopProcessing) {
  ccapi::Event event1, event2, event3;
  event1.setType(ccapi::Event::Type::SUBSCRIPTION_DATA);
  event2.setType(ccapi::Event::Type::RESPONSE);
  event3.setType(ccapi::Event::Type::FIX_STATUS);

  handler->processEvent(event1, sessionPtr);
  handler->setContinueProcessing(false);  // 在处理第二个事件时停止
  bool result = handler->processEvent(event2, sessionPtr);

  EXPECT_FALSE(result);  // 不应该继续处理事件
  const auto& events = handler->getProcessedEvents();
  ASSERT_EQ(events.size(), 2);
  EXPECT_EQ(events[0].getType(), ccapi::Event::Type::SUBSCRIPTION_DATA);
  EXPECT_EQ(events[1].getType(), ccapi::Event::Type::RESPONSE);
}

// 测试 processEvent 的返回值，当没有 session 时继续处理
TEST_F(CustomEventHandlerTest, ContinueProcessingWithNullSession) {
  ccapi::Event event;
  event.setType(ccapi::Event::Type::FIX);

  bool result = handler->processEvent(event, nullptr);  // sessionPtr 为 nullptr

  EXPECT_TRUE(result);  // 仍然应该继续处理
}

// 测试 processEvent 的返回值，当 session 存在时继续处理
TEST_F(CustomEventHandlerTest, ContinueProcessingWithSession) {
  ccapi::Event event;
  event.setType(ccapi::Event::Type::FIX);

  // 创建一个模拟的 session 实例（此处为 nullptr 示例）
  ccapi::Session* mockSession = nullptr;

  bool result = handler->processEvent(event, mockSession);

  EXPECT_TRUE(result);  // 应该继续处理
}
*/