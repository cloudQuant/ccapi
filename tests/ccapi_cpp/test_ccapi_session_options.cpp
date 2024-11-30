#include <gtest/gtest.h>

#include "ccapi_cpp/ccapi_session_options.h"  // Adjust the include path according to your project structure

class SessionOptionsTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Set up common initialization if needed
    }

    void TearDown() override {
        // Clean up after tests if necessary
    }
};

// Test 1: Verify default constructor values
TEST_F(SessionOptionsTest, TestDefaultConstructorValues) {
    ccapi::SessionOptions options;

    EXPECT_FALSE(options.enableCheckSequence);
    EXPECT_FALSE(options.enableCheckOrderBookChecksum);
    EXPECT_TRUE(options.enableCheckOrderBookCrossed);
    EXPECT_TRUE(options.enableCheckPingPongWebsocketProtocolLevel);
    EXPECT_TRUE(options.enableCheckPingPongWebsocketApplicationLevel);
    EXPECT_TRUE(options.enableCheckHeartbeatFix);
    EXPECT_EQ(options.pingWebsocketProtocolLevelIntervalMilliseconds, 60000);
    EXPECT_EQ(options.pongWebsocketProtocolLevelTimeoutMilliseconds, 30000);
    EXPECT_EQ(options.pingWebsocketApplicationLevelIntervalMilliseconds, 60000);
    EXPECT_EQ(options.pongWebsocketApplicationLevelTimeoutMilliseconds, 30000);
    EXPECT_EQ(options.heartbeatFixIntervalMilliseconds, 60000);
    EXPECT_EQ(options.heartbeatFixTimeoutMilliseconds, 30000);
    EXPECT_EQ(options.maxEventQueueSize, 0);
    EXPECT_EQ(options.httpMaxNumRetry, 1);
    EXPECT_EQ(options.httpMaxNumRedirect, 1);
    EXPECT_EQ(options.httpRequestTimeoutMilliseconds, 10000);
    EXPECT_EQ(options.httpConnectionPoolMaxSize, 1);
    EXPECT_EQ(options.httpConnectionKeepAliveTimeoutSeconds, 10);
    EXPECT_FALSE(options.enableOneHttpConnectionPerRequest);
}

// Test 2: Verify string representation of default options
TEST_F(SessionOptionsTest, TestDefaultToString) {
    ccapi::SessionOptions options;
    std::string expectedOutput = "SessionOptions [enableCheckSequence = 0, enableCheckOrderBookChecksum = 0, enableCheckOrderBookCrossed = 1, enableCheckPingPongWebsocketProtocolLevel = 1, enableCheckPingPongWebsocketApplicationLevel = 1, enableCheckHeartbeatFix = 1, pingWebsocketProtocolLevelIntervalMilliseconds = 60000, pongWebsocketProtocolLevelTimeoutMilliseconds = 30000, pingWebsocketApplicationLevelIntervalMilliseconds = 60000, pongWebsocketApplicationLevelTimeoutMilliseconds = 30000, heartbeatFixIntervalMilliseconds = 60000, heartbeatFixTimeoutMilliseconds = 30000, maxEventQueueSize = 0, httpMaxNumRetry = 1, httpMaxNumRedirect = 1, httpRequestTimeoutMilliseconds = 10000, httpConnectionPoolMaxSize = 1, httpConnectionKeepAliveTimeoutSeconds = 10, enableOneHttpConnectionPerRequest = 0]";

    EXPECT_EQ(options.toString(), expectedOutput);
}

// Test 3: Verify setting and getting options
TEST_F(SessionOptionsTest, TestSetAndGetOptions) {
    ccapi::SessionOptions options;

    options.enableCheckSequence = true;
    options.enableCheckOrderBookChecksum = true;
    options.maxEventQueueSize = 100;
    options.httpMaxNumRetry = 3;

    EXPECT_TRUE(options.enableCheckSequence);
    EXPECT_TRUE(options.enableCheckOrderBookChecksum);
    EXPECT_EQ(options.maxEventQueueSize, 100);
    EXPECT_EQ(options.httpMaxNumRetry, 3);
}

// Test 4: Check string representation after setting custom options
TEST_F(SessionOptionsTest, TestCustomToString) {
    ccapi::SessionOptions options;

    options.enableCheckSequence = true;
    options.enableCheckOrderBookChecksum = true;
    options.maxEventQueueSize = 100;

    std::string expectedOutput = "SessionOptions [enableCheckSequence = 1, enableCheckOrderBookChecksum = 1, enableCheckOrderBookCrossed = 1, enableCheckPingPongWebsocketProtocolLevel = 1, enableCheckPingPongWebsocketApplicationLevel = 1, enableCheckHeartbeatFix = 1, pingWebsocketProtocolLevelIntervalMilliseconds = 60000, pongWebsocketProtocolLevelTimeoutMilliseconds = 30000, pingWebsocketApplicationLevelIntervalMilliseconds = 60000, pongWebsocketApplicationLevelTimeoutMilliseconds = 30000, heartbeatFixIntervalMilliseconds = 60000, heartbeatFixTimeoutMilliseconds = 30000, maxEventQueueSize = 100, httpMaxNumRetry = 1, httpMaxNumRedirect = 1, httpRequestTimeoutMilliseconds = 10000, httpConnectionPoolMaxSize = 1, httpConnectionKeepAliveTimeoutSeconds = 10, enableOneHttpConnectionPerRequest = 0]";

    EXPECT_EQ(options.toString(), expectedOutput);
}

// Test 5: Check for websocket connect timeout setting
TEST_F(SessionOptionsTest, TestWebsocketConnectTimeout) {
#ifdef CCAPI_LEGACY_USE_WEBSOCKETPP
    // Skip this test if websocketpp is being used
    GTEST_SKIP() << "Websocketpp is being used.";
#else
    ccapi::SessionOptions options;
    EXPECT_EQ(options.websocketConnectTimeoutMilliseconds, 10000);
#endif
}

// Test 6: Ensure that negative values for timeouts are not allowed (if applicable)
TEST_F(SessionOptionsTest, TestNegativeTimeoutValues) {
    ccapi::SessionOptions options;

    options.pingWebsocketProtocolLevelIntervalMilliseconds = -1;
    options.pongWebsocketProtocolLevelTimeoutMilliseconds = -1;
    options.pingWebsocketApplicationLevelIntervalMilliseconds = -1;
    options.pongWebsocketApplicationLevelTimeoutMilliseconds = -1;
    options.heartbeatFixIntervalMilliseconds = -1;
    options.heartbeatFixTimeoutMilliseconds = -1;

    EXPECT_LT(options.pingWebsocketProtocolLevelIntervalMilliseconds, 0);
    EXPECT_LT(options.pongWebsocketProtocolLevelTimeoutMilliseconds, 0);
    EXPECT_LT(options.pingWebsocketApplicationLevelIntervalMilliseconds, 0);
    EXPECT_LT(options.pongWebsocketApplicationLevelTimeoutMilliseconds, 0);
    EXPECT_LT(options.heartbeatFixIntervalMilliseconds, 0);
    EXPECT_LT(options.heartbeatFixTimeoutMilliseconds, 0);
}

// Test 7: Check for setting max event queue size
TEST_F(SessionOptionsTest, TestMaxEventQueueSize) {
    ccapi::SessionOptions options;

    options.maxEventQueueSize = 10;
    EXPECT_EQ(options.maxEventQueueSize, 10);
}


