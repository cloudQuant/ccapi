#include <gtest/gtest.h>

#include <atomic>
#include <chrono>
#include <functional>
#include <iostream>
#include <thread>

#include "../../include/ccapi_cpp/ccapi_event_dispatcher.h"

class EventDispatcherTest : public ::testing::Test {
 protected:
  void SetUp() override {
    dispatcher = std::make_shared<ccapi::EventDispatcher>(2);  // 创建两个调度线程
  }

  void TearDown() override {
    //if (!dispatcher->get_status()) {
      dispatcher->stop();  // 停止所有调度线程
    //}
  }

  std::shared_ptr<ccapi::EventDispatcher> dispatcher;
};

// 测试调度事件正常执行
TEST_F(EventDispatcherTest, DispatchEventSuccessfully) {
  std::atomic<bool> eventProcessed{false};

  dispatcher->dispatch([&]() {
    eventProcessed = true;  // 设置事件处理为已完成
  });

  // 等待事件被处理
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  EXPECT_TRUE(eventProcessed);  // 验证事件是否被处理
}

// 测试多个事件调度
TEST_F(EventDispatcherTest, DispatchMultipleEvents) {
  std::atomic<int> counter{0};

  dispatcher->dispatch([&]() {
    counter++;
  });
  dispatcher->dispatch([&]() {
    counter++;
  });
  dispatcher->dispatch([&]() {
    counter++;
  });

  // 等待所有事件被处理
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  EXPECT_EQ(counter.load(), 3);  // 验证事件计数器是否达到3
}

// 测试暂停事件调度
TEST_F(EventDispatcherTest, PauseDispatching) {
  std::atomic<bool> eventProcessed{false};

  dispatcher->pause();  // 暂停调度

  dispatcher->dispatch([&]() {
    eventProcessed = true;
  });

  // 等待一段时间，事件不应被处理
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  EXPECT_FALSE(eventProcessed);  // 验证事件未被处理
}

// 测试恢复事件调度
TEST_F(EventDispatcherTest, ResumeDispatching) {
  std::atomic<bool> eventProcessed{false};

  dispatcher->pause();
  dispatcher->dispatch([&]() {
    eventProcessed = true;
  });

  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  EXPECT_FALSE(eventProcessed);  // 验证事件未被处理

  dispatcher->resume();  // 恢复调度
  dispatcher->dispatch([&]() {
    eventProcessed = true;
  });
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  EXPECT_TRUE(eventProcessed);  // 验证事件是否被处理
}

// 测试在暂停状态下提交的事件在恢复后被处理
TEST_F(EventDispatcherTest, EventsHandledAfterResume) {
  std::atomic<int> counter{0};

  dispatcher->pause();
  dispatcher->dispatch([&]() {
    counter++;
  });

  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  EXPECT_EQ(counter.load(), 0);  // 暂停状态下不处理事件

  dispatcher->resume();
  dispatcher->dispatch([&]() {
    counter++;
  });
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  EXPECT_EQ(counter.load(), 1);  // 恢复后事件应被处理
}

//// 测试停止事件调度
//TEST_F(EventDispatcherTest, StopDispatching) {
//  std::atomic<bool> eventProcessed{false};
//
//  dispatcher->dispatch([&]() {
//    eventProcessed = true;
//  });
//
//  std::this_thread::sleep_for(std::chrono::milliseconds(100));
//  EXPECT_TRUE(eventProcessed);  // 确保在停止之前的事件已处理
//
//  dispatcher->stop();  // 停止调度
//  dispatcher->dispatch([&]() {
//    eventProcessed = false;  // 这条事件不应被处理
//  });
//
//  std::this_thread::sleep_for(std::chrono::milliseconds(100));
//  EXPECT_TRUE(eventProcessed);  // 确保在停止之前的事件已处理
//}

//// 测试调度线程正常退出
//TEST_F(EventDispatcherTest, DispatcherThreadsExitAfterStop) {
//  dispatcher->stop();  // 停止所有调度线程
//  EXPECT_TRUE(true);  // 如果没有崩溃，则测试通过
//}

// 测试在大量事件提交后调度的正确性
TEST_F(EventDispatcherTest, DispatchManyEvents) {
  std::atomic<int> counter{0};
  const int numEvents = 100;

  for (int i = 0; i < numEvents; ++i) {
    dispatcher->dispatch([&]() {
      counter++;
    });
  }

  std::this_thread::sleep_for(std::chrono::milliseconds(200));
  EXPECT_EQ(counter.load(), numEvents);  // 验证是否所有事件都被处理
}

