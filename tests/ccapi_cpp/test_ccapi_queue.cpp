#include <gtest/gtest.h>

#include <condition_variable>  // 新增
#include <mutex>               // 新增

#include "ccapi_cpp/ccapi_queue.h"

// 打印 vector 元素的函数
template <typename T>
void printVector(const std::vector<T>& vec) {
    for (const auto& elem : vec) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

class QueueTest : public ::testing::Test {
protected:
    // 在每个测试之前运行
    void SetUp() override {
        // 测试用的队列，最大大小为 3
        queue = new ccapi::Queue<int>(10);
    }

    // 在每个测试之后运行
    void TearDown() override {
        delete queue;
    }

    ccapi::Queue<int>* queue{};


};

// 测试推送和弹出元素
TEST_F(QueueTest, PushAndPopElements) {
    queue->pushBack(1);
    queue->pushBack(2);
    queue->pushBack(3);

    EXPECT_EQ(queue->popBack(), 3);
    EXPECT_EQ(queue->popBack(), 2);
    EXPECT_EQ(queue->popBack(), 1);
}

// 测试队列空时弹出
TEST_F(QueueTest, PopFromEmptyQueueThrowsException) {
    EXPECT_THROW(queue->popBack(), std::runtime_error);
}

// 测试推送超出最大大小的元素
TEST_F(QueueTest, PushExceedingMaxSizeThrowsException) {
    queue->pushBack(1);
    queue->pushBack(2);
    queue->pushBack(3);
    queue->pushBack(1);
    queue->pushBack(2);
    queue->pushBack(3);
    queue->pushBack(1);
    queue->pushBack(2);
    queue->pushBack(3);
    queue->pushBack(4);
    EXPECT_THROW(queue->pushBack(4), std::runtime_error);
}

// 测试清空队列
TEST_F(QueueTest, PurgeQueue) {
    queue->pushBack(1);
    queue->pushBack(2);
    queue->pushBack(3);

    std::vector<int> purgedItems = queue->purge();
    std::size_t num = 3;
    EXPECT_EQ(purgedItems.size(), num);
    EXPECT_EQ(purgedItems[0], 1);
    EXPECT_EQ(purgedItems[1], 2);
    EXPECT_EQ(purgedItems[2], 3);
    EXPECT_TRUE(queue->empty());
}

// 测试检查队列大小
TEST_F(QueueTest, CheckSize) {
    std::size_t num = 0;
    EXPECT_EQ(queue->size(), num);
    queue->pushBack(1);
    queue->pushBack(2);
    num = 2;
    EXPECT_EQ(queue->size(), num);
}

// 测试队列是否为空
TEST_F(QueueTest, CheckIfEmpty) {
    EXPECT_TRUE(queue->empty());
    queue->pushBack(1);
    EXPECT_FALSE(queue->empty());
}

// 测试 removeAll 操作
TEST_F(QueueTest, RemoveAllItems) {
    queue->pushBack(1);
    queue->pushBack(2);

    std::vector<int> removedItems;
    queue->removeAll(removedItems);

    std::size_t num = 2;
    EXPECT_EQ(removedItems.size(), num);
    EXPECT_EQ(removedItems[0], 1);
    EXPECT_EQ(removedItems[1], 2);
    EXPECT_TRUE(queue->empty());
}

// 测试在 maxSize 为 0 时的推送
TEST_F(QueueTest, PushWhenMaxSizeIsZero) {
    delete queue;
    queue = new ccapi::Queue<int>(0); // 创建一个没有大小限制的队列
    queue->pushBack(1);  // 这应该成功
    std::size_t num = 1;
    EXPECT_EQ(queue->size(), num);
}

// 测试多线程环境下的推送和弹出（简单示例）
TEST_F(QueueTest, MultiThreadPushPop) {
    std::vector<std::thread> threads;

    // 向队列中添加元素
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back([this, i] { queue->pushBack(i); });
    }

    // 等待线程完成
    for (auto& thread : threads) {
        thread.join();
    }

    std::size_t num = 10;
    EXPECT_EQ(queue->size(), num);

    // 从队列中移除元素
    for (int i = 0; i < 10; ++i) {
        queue->popBack();
    }
    num = 0;
    EXPECT_EQ(queue->size(), num);
}

// 测试多线程环境下的推送和弹出（并发推送）
TEST_F(QueueTest, ConcurrentPush) {
    std::vector<std::thread> threads;

    // 向队列中添加元素
    for (int i = 0; i < 20; ++i) {
        threads.emplace_back([this, i] {
            try {
                queue->pushBack(i);
            } catch (const std::runtime_error& e) {
                // 处理队列满的异常
            }
        });
    }

    // 等待线程完成
    for (auto& thread : threads) {
        thread.join();
    }
    std::size_t num = 0;
    EXPECT_GE(queue->size(), num);  // 确保队列的大小大于等于0
}

// 测试多线程环境下的弹出
TEST_F(QueueTest, ConcurrentPop) {
    // 先添加元素
    for (int i = 0; i < 10; ++i) {
        queue->pushBack(i);
    }

    std::vector<std::thread> threads;

    // 从队列中移除元素
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back([this] {
            try {
                queue->popBack();
            } catch (const std::runtime_error& e) {
                // 处理队列空的异常
            }
        });
    }

    // 等待线程完成
    for (auto& thread : threads) {
        thread.join();
    }
    std::size_t num = 5;
    EXPECT_LE(queue->size(), num);  // 确保队列的大小小于等于5
}

// 测试多线程环境下的混合操作（同时推送和弹出）
TEST_F(QueueTest, ConcurrentPushPopMixed) {
    std::vector<std::thread> threads;

    // 向队列中添加元素的线程
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back([this, i] {
            try {
                queue->pushBack(i);
            } catch (const std::runtime_error& e) {
                // 处理队列满的异常
            }
        });
    }

    // 从队列中移除元素的线程
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back([this] {
            try {
                queue->popBack();
            } catch (const std::runtime_error& e) {
                // 处理队列空的异常
            }
        });
    }

    // 等待线程完成
    for (auto& thread : threads) {
        thread.join();
    }
    std::size_t num = 0;
    EXPECT_GE(queue->size(), num);  // 确保队列的大小大于等于0
}

// 测试多线程环境下的 purge 操作
TEST_F(QueueTest, ConcurrentPurge) {
    // 先添加元素
    for (int i = 0; i < 10; ++i) {
        queue->pushBack(i);
    }

    std::vector<std::thread> threads;
    std::mutex mtx;
    std::condition_variable cv;
    bool taskDone = false;  // 声明 taskDone
    // 执行 purge 操作的线程
    threads.emplace_back([this,&cv, &mtx, &taskDone] {
        std::size_t num = 10;
        std::lock_guard<std::mutex> lock(mtx);  // 保证 purge 操作是原子的
        auto purgedItems = queue->purge();
        printVector(purgedItems);
        EXPECT_EQ(purgedItems.size(), num);  // 确保 purge 后返回了10个元素
        taskDone = true;
        cv.notify_all();  // 通知移除操作可以继续
    });

    // 从队列中移除元素的线程
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back([this, &cv, &mtx, &taskDone] {
            try {
                std::unique_lock<std::mutex> lock(mtx);
                // 捕获 taskDone 变量
                cv.wait(lock, [&taskDone] { return taskDone; });  // 等待 purge 线程完成
                queue->popBack();
            } catch (const std::runtime_error& e) {
                // 处理队列为空的异常
                std::cout << "处理队列空的异常" << std::endl;
            }
        });
    }

    // 等待线程完成
    for (auto& thread : threads) {
        thread.join();
    }

    EXPECT_TRUE(queue->empty());  // 确保队列为空
}

// 测试多线程环境下的 removeAll 操作
TEST_F(QueueTest, ConcurrentRemoveAll) {
    // 先添加元素
    for (int i = 0; i < 10; ++i) {
        queue->pushBack(i);
    }

    // 执行 removeAll 操作的线程
    std::vector<std::thread> threads;
    std::mutex mtx;
    std::condition_variable cv;
    bool taskDone = false;  // 声明 taskDone
    threads.emplace_back([this, &cv, &mtx, &taskDone] {
        std::size_t num = 10;
        std::vector<int> removedItems;
        std::lock_guard<std::mutex> lock(mtx);  // 保证 removeAll 操作是原子的
        queue->removeAll(removedItems);
        //std::this_thread::sleep_for(std::chrono::milliseconds(500));
        printVector(removedItems);
        EXPECT_EQ(removedItems.size(), num);  // 确保 removeAll 后返回了10个元素
        taskDone = true;
        cv.notify_all();  // 通知 removeAll 可以继续
    });

    // 从队列中移除元素的线程
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back([this, &cv, &mtx, &taskDone] {
            try {
                std::unique_lock<std::mutex> lock(mtx);
                cv.wait(lock, [&taskDone] { return taskDone; });  // 等待 popBack 线程完成
                queue->popBack();
            } catch (const std::runtime_error& e) {
                // 处理队列空的异常
                std::cout << "处理队列空的异常" << std::endl;
            }
        });
    }

    // 等待线程完成
    for (auto& thread : threads) {
        thread.join();
    }

    EXPECT_TRUE(queue->empty());  // 确保队列为空
}
