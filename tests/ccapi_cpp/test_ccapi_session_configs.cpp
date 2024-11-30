#include <gtest/gtest.h>

#include "ccapi_cpp/ccapi_session_configs.h"  // Adjust the include path according to your project structure

class SessionConfigsTest : public ::testing::Test {
protected:
    void SetUp() override {
        // You can set up common initialization here if needed
    }

    void TearDown() override {
        // Clean up after tests if necessary
    }
};

// Test 1: Verify constructor initialization with credentials
TEST_F(SessionConfigsTest, TestConstructorInitialization) {
    std::map<std::string, std::string> credentials = {{"api_key", "test_key"}, {"api_secret", "test_secret"}};
    ccapi::SessionConfigs sessionConfigs(credentials);

    EXPECT_EQ(sessionConfigs.getCredential().at("api_key"), "test_key");
    EXPECT_EQ(sessionConfigs.getCredential().at("api_secret"), "test_secret");
    EXPECT_FALSE(sessionConfigs.getExchangeFieldMap().empty());
    EXPECT_FALSE(sessionConfigs.getUrlWebsocketBase().empty());
}

// Test 2: Validate getter methods
TEST_F(SessionConfigsTest, TestGetterMethods) {
    ccapi::SessionConfigs sessionConfigs;

    EXPECT_FALSE(sessionConfigs.getExchangeFieldMap().empty());
    EXPECT_FALSE(sessionConfigs.getUrlRestBase().empty());
    EXPECT_FALSE(sessionConfigs.getUrlWebsocketBase().empty());
    std::size_t num = 2;
    EXPECT_EQ(sessionConfigs.getInitialSequenceByExchangeMap().size(), num);
    EXPECT_TRUE(sessionConfigs.getCredential().empty());
}

// Test 3: Validate setter methods
TEST_F(SessionConfigsTest, TestSetterMethods) {
    ccapi::SessionConfigs sessionConfigs;

    std::map<std::string, std::string> newWebsocketUrls = {{"binance", "wss://test.binance.com"}};
    sessionConfigs.setUrlWebsocketBase(newWebsocketUrls);
    EXPECT_EQ(sessionConfigs.getUrlWebsocketBase().at("binance"), "wss://test.binance.com");

    std::map<std::string, std::string> newRestUrls = {{"binance", "https://test.binance.com/api"}};
    sessionConfigs.setUrlRestBase(newRestUrls);
    EXPECT_EQ(sessionConfigs.getUrlRestBase().at("binance"), "https://test.binance.com/api");
}

// Test 4: Check handling of invalid credential input
TEST_F(SessionConfigsTest, TestInitCredentialInput) {
    std::map<std::string, std::string> invalidCredentials = {{"", ""}};
    ccapi::SessionConfigs sessionConfigs(invalidCredentials);

    EXPECT_TRUE(!sessionConfigs.getCredential().empty());
}

// Test 5: Edge case for empty initialization
TEST_F(SessionConfigsTest, TestEmptyInitialization) {
    ccapi::SessionConfigs sessionConfigs;

    EXPECT_TRUE(sessionConfigs.getCredential().empty());
    EXPECT_FALSE(sessionConfigs.getExchangeFieldMap().empty());
    EXPECT_FALSE(sessionConfigs.getUrlWebsocketBase().empty());
}


// Test 7: Verify URL settings
TEST_F(SessionConfigsTest, TestUrlSettings) {
    ccapi::SessionConfigs sessionConfigs;

    sessionConfigs.setUrlWebsocketBase({{"binance", "wss://binance.com/websocket"}});
    sessionConfigs.setUrlRestBase({{"binance", "https://binance.com/api"}});

    EXPECT_EQ(sessionConfigs.getUrlWebsocketBase().at("binance"), "wss://binance.com/websocket");
    EXPECT_EQ(sessionConfigs.getUrlRestBase().at("binance"), "https://binance.com/api");
}

// Test 8: Validate multiple exchanges handling
TEST_F(SessionConfigsTest, TestMultipleExchangesHandling) {
    ccapi::SessionConfigs sessionConfigs;
    std::map<std::string, std::string> exchanges = {
        {"binance", "wss://binance.com/websocket"},
        {"coinbase", "wss://coinbase.com/websocket"}
    };

    sessionConfigs.setUrlWebsocketBase(exchanges);

    EXPECT_EQ(sessionConfigs.getUrlWebsocketBase().at("binance"), "wss://binance.com/websocket");
    EXPECT_EQ(sessionConfigs.getUrlWebsocketBase().at("coinbase"), "wss://coinbase.com/websocket");
}

// Test 9: Test updating URLs multiple times
TEST_F(SessionConfigsTest, TestUpdatingUrlsMultipleTimes) {
    ccapi::SessionConfigs sessionConfigs;

    // First update
    sessionConfigs.setUrlWebsocketBase({{"binance", "wss://binance.com/websocket"}});
    EXPECT_EQ(sessionConfigs.getUrlWebsocketBase().at("binance"), "wss://binance.com/websocket");

    // Second update
    sessionConfigs.setUrlWebsocketBase({{"binance", "wss://test.binance.com/websocket"}});
    EXPECT_EQ(sessionConfigs.getUrlWebsocketBase().at("binance"), "wss://test.binance.com/websocket");
}


// Test 11: Ensure setting empty URLs does not crash
TEST_F(SessionConfigsTest, TestSetEmptyUrls) {
    ccapi::SessionConfigs sessionConfigs;

    sessionConfigs.setUrlWebsocketBase({});
    sessionConfigs.setUrlRestBase({});
    sessionConfigs.setUrlFixBase({});

    EXPECT_TRUE(sessionConfigs.getUrlWebsocketBase().empty());
    EXPECT_TRUE(sessionConfigs.getUrlRestBase().empty());
    EXPECT_TRUE(sessionConfigs.getUrlFixBase().empty());
}


