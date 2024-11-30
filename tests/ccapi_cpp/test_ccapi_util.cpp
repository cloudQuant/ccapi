#include <chrono>
#include <thread>

#include "../../include/ccapi_cpp/ccapi_util.h"  // 假设 ccapi_util.h 是上述头文件
#include "gtest/gtest.h"

// 测试 TimePoint 类型的基本操作
TEST(TimePointTest, Initialization) {
    // 创建一个 TimePoint 对象，表示当前时间
    ccapi::TimePoint now = std::chrono::system_clock::now();

    // 确认 TimePoint 对象被正确初始化
    ASSERT_TRUE(now.time_since_epoch().count() > 0);
}

TEST(TimePointTest, Comparison) {
    // 创建两个时间点
    ccapi::TimePoint t1 = std::chrono::system_clock::now();
    std::this_thread::sleep_for(std::chrono::milliseconds(1));  // 延迟 1 毫秒
    ccapi::TimePoint t2 = std::chrono::system_clock::now();
    // 确认 t2 大于 t1
    ASSERT_GT(t2, t1);
}

TEST(TimePointTest, Duration) {
    // 创建两个时间点
    ccapi::TimePoint t1 = std::chrono::system_clock::now();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));  // 延迟 10 毫秒
    ccapi::TimePoint t2 = std::chrono::system_clock::now();
    //std::cout << "t2 = " << t2 << std::endl;
    // 计算时间差，单位为纳秒
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
    // 确认时间差接近 10 毫秒
    ASSERT_GE(duration, 10 * 1000000);  // 10 毫秒 = 10 * 10^6 纳秒
}


