


#include <cstddef>
#include <cstdio>
#include <memory>
#include <vector>
#include <atomic>
#include <condition_variable>
#include <string>

class EventLoop;
class EventLoopThread;

class AsyncLogger {

    public:
        AsyncLogger(const std::string& basename, 
                size_t rollSize  = 1024*1024*1024,
                int flushInterval = 3);
        ~AsyncLogger();

        void Start();
        void Stop();
        void Append(const char* data, size_t len);
        void Flush();
    
    private:
        void ThreadFunc(EventLoop* loop);
        void AppendInLoop(const char* data, size_t len);
        void RollFile();
    
    private:
        using Buffer = std::vector<char>;
        using BufferPtr = std::shared_ptr<Buffer>;
        using BufferVector = std::vector<BufferPtr>;

        const std::string basename_;
        const size_t rollSize_;
        const int flushInterval_;

        std::unique_ptr<EventLoopThread> thread_;
        EventLoop* loop_;

        std::mutex mutex_;
        std::condition_variable cond_;
        BufferPtr currentBuffer_;   // first buffer
        BufferPtr nextBuffer_;      // second buffer
        BufferVector buffers_;
        std::atomic<bool> running_;
        FILE* fp_;
};
