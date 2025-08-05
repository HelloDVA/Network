
#pragma once
#include <vector>
#include <memory>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>

class AsyncLogging {
public:
    AsyncLogging(const std::string& basename, 
                size_t rollSize,
                int flushInterval = 3);
    ~AsyncLogging();

    void append(const char* logline, int len);
    void start();
    void stop();

private:
    void threadFunc();

    using Buffer = std::vector<char>;
    using BufferPtr = std::shared_ptr<Buffer>;
    using BufferVector = std::vector<BufferPtr>;

    const std::string basename_;
    const size_t rollSize_;
    const int flushInterval_;
    
    std::atomic<bool> running_;
    std::thread thread_;
    std::mutex mutex_;
    std::condition_variable cond_;
    
    BufferPtr currentBuffer_;
    BufferPtr nextBuffer_;
    BufferVector buffers_;
};