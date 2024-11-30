#include <chrono>
#include <thread>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include "ccapi_cpp/service/ccapi_service_context.h"
#include "gtest/gtest.h"

class ServiceContextTest : public ::testing::Test {
protected:
    void SetUp() override {
        // 在测试开始时执行的初始化工作
    }

    void TearDown() override {
        // 在每个测试结束时清理资源
    }
};

// 测试默认构造函数
TEST_F(ServiceContextTest, DefaultConstructor) {
    ccapi::ServiceContext serviceContext;
    EXPECT_NE(serviceContext.ioContextPtr, nullptr);
    EXPECT_NE(serviceContext.sslContextPtr, nullptr);
    EXPECT_NO_THROW({
                        ccapi::ServiceContext serviceContext;
                    });
}

// 测试 start() 方法是否成功启动服务
TEST_F(ServiceContextTest, StartAndStopService) {
    ccapi::ServiceContext serviceContext;

    // 在一个独立线程中启动服务
    std::thread serviceThread([&serviceContext]() {
        serviceContext.start();
    });

    // 等待一段时间后停止服务
    std::this_thread::sleep_for(std::chrono::seconds(1));  // 等待2秒以模拟服务运行
    serviceContext.stop();

    // 确保线程顺利结束
    if (serviceThread.joinable()) {
        serviceThread.join();
    }

    EXPECT_NO_THROW({
                        serviceContext.stop();
                    });
}

// 测试 stop() 方法是否成功停止服务
TEST_F(ServiceContextTest, StopService) {
    ccapi::ServiceContext serviceContext;

    // 启动服务
    std::thread serviceThread([&serviceContext]() {
        serviceContext.start();
    });

    // 确保服务启动后可以停止
    std::this_thread::sleep_for(std::chrono::seconds(1));  // 确保服务有足够的时间启动
    serviceContext.stop();

    // 等待线程结束
    if (serviceThread.joinable()) {
        serviceThread.join();
    }

    EXPECT_NO_THROW({
                        serviceContext.stop();
                    });
}

//// 测试自定义的 ioContext 构造函数
//TEST_F(ServiceContextTest, CustomIoContextConstructor) {
//    // Create a custom io_context
//    boost::asio::io_context customIoContext;
//    // Use a raw pointer to avoid ownership issues
//    ccapi::ServiceContext serviceContext(&customIoContext);
//
//    // Verify that the ioContextPtr points to the correct object
//    EXPECT_EQ(&customIoContext, serviceContext.ioContextPtr);
//}

//TEST_F(ServiceContextTest, CustomSslContextConstructor) {
//    // Create a shared_ptr for the SSL context
//    auto customSslContext = std::make_shared<boost::asio::ssl::context>(boost::asio::ssl::context::tls_client);
//
//    // Initialize the ServiceContext with a custom SSL context
//    ccapi::ServiceContext serviceContext(customSslContext.get()); // Pass raw pointer to the constructor
//
//    // Check that the SSL context pointer is pointing to the same object
//    EXPECT_EQ(customSslContext.get(), serviceContext.sslContextPtr);
//}

//TEST_F(ServiceContextTest, CustomSslContextConstructorWithRawPointer) {
//    // 创建一个裸指针的 SslContext
//    boost::asio::ssl::context customSslContext(boost::asio::ssl::context::tls_client);
//    ccapi::ServiceContext serviceContext(&customSslContext);
//    EXPECT_EQ(&customSslContext, serviceContext.sslContextPtr);
//}


