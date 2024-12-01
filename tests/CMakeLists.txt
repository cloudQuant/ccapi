cmake_minimum_required(VERSION 3.14)
set(CMAKE_TOOLCHAIN_FILE "/Users/yunjinqi/vcpkg/scripts/buildsystems/vcpkg.cmake")
# set(CMAKE_TOOLCHAIN_FILE "/home/yun/vcpkg/scripts/buildsystems/vcpkg.cmake")

project(ccapi_test)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(THREADS_PREFER_PTHREAD_FLAG ON)


find_package(cpr CONFIG REQUIRED)
find_package(Boost REQUIRED COMPONENTS asio lockfree system thread beast)
find_package(OpenSSL REQUIRED)
find_package(RapidJSON CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)
find_package(websocketpp CONFIG REQUIRED)
enable_testing()
include_directories(
        ${CMAKE_SOURCE_DIR}/../include
        ${Boost_INCLUDE_DIRS}
)
# 自动查找 tests/ 目录下的所有测试文件
file(GLOB_RECURSE TEST_SOURCES "ccapi_cpp/*.cpp")
# 如果没有找到任何测试源文件，抛出错误
if(TEST_SOURCES STREQUAL "")
    message(FATAL_ERROR "No source files found in the tests/ directory")
endif()
# 自动查找 service 目录下的所有文件
file(GLOB_RECURSE SERVICE_SOURCES "${CMAKE_SOURCE_DIR}/../include/ccapi_cpp/service/*.h" "${CMAKE_SOURCE_DIR}/../include/ccapi_cpp/service/*.cpp")

# 定义可执行文件目标并传入源文件
add_executable(${PROJECT_NAME} ${TEST_SOURCES} ${SERVICE_SOURCES})
## 定义可执行文件目标并传入源文件
#add_executable(${PROJECT_NAME} ${TEST_SOURCES}
#)
target_link_libraries(${PROJECT_NAME} PRIVATE
                                            ${Boost_LIBRARIES}
                                            GTest::gtest
                                            GTest::gtest_main
                                            GTest::gmock
                                            GTest::gmock_main
                                            cpr::cpr
                                            Boost::asio
                                            Boost::lockfree
                                            Boost::beast
                                            OpenSSL::SSL
                                            OpenSSL::Crypto
                                            rapidjson
                                            websocketpp::websocketpp
)

# gtest_discover_tests(btcpp_test)
add_test(AllTestsInMain main)




