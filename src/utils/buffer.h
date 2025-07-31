
#pragma once

#include <cstddef>
#include <vector>


class Buffer {
public:
    static const size_t kCheapPrepend = 8;  // prepend size
    static const size_t kInitialSize = 1024;

    explicit Buffer()
        : buffer_(kInitialSize),
          reader_index_(kCheapPrepend),
          writer_index_(kCheapPrepend) {
    }
    ~Buffer() {}

    // 从文件描述符读取数据到缓冲区
    size_t ReadFd(int fd, int* saved_errno);
   
    void Append(const char* data, size_t len);
    void MakeSpace(size_t len);
    void EnsureWritableBytes(size_t len);

    void Retrieve(size_t len);
    void RetrieveAll();
    
    // about size
    size_t PrependableBytes() const;
    size_t ReadableBytes() const;
    size_t WriteableBytes() const;
    char* BeginWrite();
    const char* Peek() const;
    
private:
    std::vector<char> buffer_;
    size_t reader_index_;
    size_t writer_index_;
};
