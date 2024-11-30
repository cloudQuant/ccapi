#include <gtest/gtest.h>

#include "../../include/ccapi_cpp/ccapi_event.h"
#include "../../include/ccapi_cpp/ccapi_message.h"  // 假设 Message 类已定义

using namespace ccapi;

// 测试事件类型转字符串
TEST(EventTest, TypeToString) {
    EXPECT_EQ(Event::typeToString(Event::Type::UNKNOWN), "UNKNOWN");
    EXPECT_EQ(Event::typeToString(Event::Type::SESSION_STATUS), "SESSION_STATUS");
    EXPECT_EQ(Event::typeToString(Event::Type::SUBSCRIPTION_STATUS), "SUBSCRIPTION_STATUS");
    EXPECT_EQ(Event::typeToString(Event::Type::REQUEST_STATUS), "REQUEST_STATUS");
    EXPECT_EQ(Event::typeToString(Event::Type::RESPONSE), "RESPONSE");
    EXPECT_EQ(Event::typeToString(Event::Type::SUBSCRIPTION_DATA), "SUBSCRIPTION_DATA");
    EXPECT_EQ(Event::typeToString(Event::Type::AUTHORIZATION_STATUS), "AUTHORIZATION_STATUS");
    EXPECT_EQ(Event::typeToString(Event::Type::FIX), "FIX");
    EXPECT_EQ(Event::typeToString(Event::Type::FIX_STATUS), "FIX_STATUS");
}

// 测试事件类型的设置与获取
TEST(EventTest, SetAndGetType) {
    Event event;
    event.setType(Event::Type::RESPONSE);
    EXPECT_EQ(event.getType(), Event::Type::RESPONSE);

    event.setType(Event::Type::SUBSCRIPTION_STATUS);
    EXPECT_EQ(event.getType(), Event::Type::SUBSCRIPTION_STATUS);
}

// 测试消息列表的设置与获取
TEST(EventTest, SetAndGetMessageList) {
    Event event;
    std::vector<Message> messageList = {Message(), Message()};
    event.setMessageList(messageList);
    std::size_t num = 2;
    EXPECT_EQ(event.getMessageList().size(), num);
}

// 测试添加单条消息
TEST(EventTest, AddMessage) {
    Event event;
    Message msg;
    event.addMessage(msg);
    std::size_t num = 1;
    EXPECT_EQ(event.getMessageList().size(), num);
}

// 测试添加消息列表
TEST(EventTest, AddMessages) {
    Event event;
    std::vector<Message> messageList = {Message(), Message()};
    event.addMessages(messageList);
    std::size_t num = 2;
    EXPECT_EQ(event.getMessageList().size(), num);
}

// 测试高效添加单条消息
TEST(EventTest, AddMessageMove) {
    Event event;
    Message msg;
    event.addMessage(msg);
    std::size_t num = 1;
    EXPECT_EQ(event.getMessageList().size(), num);
}

// 测试高效添加消息列表
TEST(EventTest, AddMessagesMove) {
    Event event;
    std::vector<Message> messageList = {Message(), Message()};
    event.addMessages(std::move(messageList));
    std::size_t num = 2;
    EXPECT_EQ(event.getMessageList().size(), num);
}

// 测试toString函数
TEST(EventTest, ToString) {
    Event event;
    event.setType(Event::Type::RESPONSE);
    EXPECT_EQ(event.toString(), "Event [type = RESPONSE, messageList = [  ]]");
}

// 测试toStringPretty函数
TEST(EventTest, ToStringPretty) {
    Event event;
    event.setType(Event::Type::RESPONSE);
    EXPECT_EQ(event.toStringPretty(), "Event [\n  type = RESPONSE,\n  messageList = [\n\n  ]\n]");
}

// 测试空消息列表的设置
TEST(EventTest, SetEmptyMessageList) {
    Event event;
    std::vector<Message> emptyList;
    event.setMessageList(emptyList);
    EXPECT_TRUE(event.getMessageList().empty());
}

// 测试空消息列表的移动设置
TEST(EventTest, SetEmptyMessageListMove) {
    Event event;
    std::vector<Message> emptyList;
    event.setMessageList(std::move(emptyList));
    EXPECT_TRUE(event.getMessageList().empty());
}

// 测试边界条件：设置大量消息
TEST(EventTest, SetLargeMessageList) {
    Event event;
    std::vector<Message> largeList(1000);
    event.setMessageList(largeList);
    std::size_t num = 1000;
    EXPECT_EQ(event.getMessageList().size(), num);
}

// 测试边界条件：增加大量消息
TEST(EventTest, AddLargeMessageList) {
    Event event;
    std::vector<Message> largeList(1000);
    event.addMessages(largeList);
    std::size_t num = 1000;
    EXPECT_EQ(event.getMessageList().size(), num);
}

// 测试边界条件：空事件类型
TEST(EventTest, DefaultType) {
    Event event;
    EXPECT_EQ(event.getType(), Event::Type::UNKNOWN);
}

// 测试边界条件：空消息列表
TEST(EventTest, DefaultMessageList) {
    Event event;
    EXPECT_TRUE(event.getMessageList().empty());
}

// 测试边界条件：连续添加消息
TEST(EventTest, AddMultipleMessages) {
    Event event;
    Message msg1, msg2, msg3;
    event.addMessage(msg1);
    event.addMessage(msg2);
    event.addMessage(msg3);
    std::size_t num = 3;
    EXPECT_EQ(event.getMessageList().size(), num);
}

// 测试边界条件：连续设置消息列表
TEST(EventTest, SetMultipleMessageLists) {
    Event event;
    std::vector<Message> list1 = {Message()};
    std::vector<Message> list2 = {Message(), Message()};
    event.setMessageList(list1);
    std::size_t num = 1;
    EXPECT_EQ(event.getMessageList().size(), num);
    event.setMessageList(list2);
    num = 2;
    EXPECT_EQ(event.getMessageList().size(), num);
}

// 测试边界条件：清空消息列表
TEST(EventTest, ClearMessageList) {
    Event event;
    std::vector<Message> list = {Message(), Message()};
    event.setMessageList(list);
    event.setMessageList({});
    EXPECT_TRUE(event.getMessageList().empty());
}

// 测试混合插入与设置消息
TEST(EventTest, MixAddAndSetMessages) {
    Event event;
    Message msg1, msg2;
    std::vector<Message> messageList = {msg1, msg2};
    event.addMessage(msg1);
    event.setMessageList(messageList);
    std::size_t num = 2;
    EXPECT_EQ(event.getMessageList().size(), num);
}

// 测试边界条件：增加空消息列表
TEST(EventTest, AddEmptyMessageList) {
    Event event;
    std::vector<Message> emptyList;
    event.addMessages(emptyList);
    EXPECT_TRUE(event.getMessageList().empty());
}

// 测试边界条件：高效增加空消息列表
TEST(EventTest, AddEmptyMessageListMove) {
    Event event;
    std::vector<Message> emptyList;
    event.addMessages(std::move(emptyList));
    EXPECT_TRUE(event.getMessageList().empty());
}

// 测试事件类型的序列化
TEST(EventTest, TypeToStringUnknown) {
    EXPECT_EQ(Event::typeToString(Event::Type::UNKNOWN), "UNKNOWN");
}

TEST(EventTest, TypeToStringSessionStatus) {
    EXPECT_EQ(Event::typeToString(Event::Type::SESSION_STATUS), "SESSION_STATUS");
}

TEST(EventTest, TypeToStringFixStatus) {
    EXPECT_EQ(Event::typeToString(Event::Type::FIX_STATUS), "FIX_STATUS");
}


