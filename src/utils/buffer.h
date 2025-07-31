
#pragma once

#include <vector>



class Buffer {
public:
    // 从文件描述符读取数据到缓冲区
    size_t ReadFd(int fd, int* savedErrno);
    
    // 缓冲区基本操作
    void Append(const char* data, size_t len);
    void Retrieve(size_t len);
    const char* Peek() const;
    size_t ReadableBytes() const;
    
private:
    std::vector<char> buffer_;
    size_t reader_index_;
    size_t writer_index_;
    
    static const size_t kCheapPrepend = 8;
    static const size_t kInitialSize = 1024;
};