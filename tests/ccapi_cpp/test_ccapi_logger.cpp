#define CCAPI_ENABLE_LOG_FATAL
#define CCAPI_ENABLE_LOG_ERROR
#define CCAPI_ENABLE_LOG_WARN
#define CCAPI_ENABLE_LOG_INFO
#define CCAPI_ENABLE_LOG_DEBUG
#define CCAPI_ENABLE_LOG_TRACE

#include <gtest/gtest.h>

#include "../../include/ccapi_cpp/ccapi_logger.h"  // 包含要测试的 Logger 头文件

// 自定义 Logger，记录日志消息以便测试
class TestLogger : public ccapi::Logger {
public:
    std::string lastSeverity;
    std::string lastMessage;
    std::string lastThreadId;
    std::string lastTimeISO;
    std::string lastFileName;
    std::string lastLineNumber;

    void logMessage(const std::string& severity,
                    const std::string& threadId,
                    const std::string& timeISO,
                    const std::string& fileName,
                    const std::string& lineNumber,
                    const std::string& message) override {
        this->lastSeverity = severity;
        this->lastThreadId = threadId;
        this->lastTimeISO = timeISO;
        this->lastFileName = fileName;
        this->lastLineNumber = lineNumber;
        this->lastMessage = message;
    }
};

// 初始化静态 Logger 指针
ccapi::Logger* ccapi::Logger::logger = nullptr;

// Logger 测试基类，用于设置和清理自定义 Logger
class LoggerTest : public ::testing::Test {
protected:
    TestLogger testLogger;

    void SetUp() override {
        ccapi::Logger::logger = &testLogger;
    }

    void TearDown() override {
        ccapi::Logger::logger = nullptr;
    }
};

// 测试 FATAL 日志
TEST_F(LoggerTest, FatalLog) {
    std::string testMessage = "Test Fatal Message";

    EXPECT_THROW(CCAPI_LOGGER_FATAL(testMessage), std::runtime_error);
    EXPECT_EQ(testLogger.lastSeverity, "FATAL");
    EXPECT_EQ(testLogger.lastMessage, testMessage);
}

// 测试 ERROR 日志
TEST_F(LoggerTest, ErrorLog) {
    std::string testMessage = "Test Error Message";

    CCAPI_LOGGER_ERROR(testMessage)
    EXPECT_EQ(testLogger.lastSeverity, "ERROR");
    EXPECT_EQ(testLogger.lastMessage, testMessage);
}

// 测试 WARN 日志
TEST_F(LoggerTest, WarnLog) {
    std::string testMessage = "Test Warn Message";

    CCAPI_LOGGER_WARN(testMessage)
    EXPECT_EQ(testLogger.lastSeverity, "WARN");
    EXPECT_EQ(testLogger.lastMessage, testMessage);
}

// 测试 INFO 日志
TEST_F(LoggerTest, InfoLog) {
    std::string testMessage = "Test Info Message";

    CCAPI_LOGGER_INFO(testMessage)
    EXPECT_EQ(testLogger.lastSeverity, "INFO");
    EXPECT_EQ(testLogger.lastMessage, testMessage);
}

// 测试 DEBUG 日志
TEST_F(LoggerTest, DebugLog) {
    std::string testMessage = "Test Debug Message";

    CCAPI_LOGGER_DEBUG(testMessage)
    EXPECT_EQ(testLogger.lastSeverity, "DEBUG");
    EXPECT_EQ(testLogger.lastMessage, testMessage);
}

// 测试 TRACE 日志
TEST_F(LoggerTest, TraceLog) {
    std::string testMessage = "Test Trace Message";

    CCAPI_LOGGER_TRACE(testMessage)
    EXPECT_EQ(testLogger.lastSeverity, "TRACE");
    EXPECT_EQ(testLogger.lastMessage, testMessage);
}
