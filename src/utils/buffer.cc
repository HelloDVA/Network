
#include <algorithm>
#include <cstddef>

#include <sys/types.h>
#include <sys/uio.h>
#include <errno.h>
#include <assert.h>

#include "buffer.h"


<<<<<<< HEAD
#include <sys/uio.h>
#include <errno.h>
#include <unistd.h>

ssize_t Buffer::ReadFd(int fd, int* savedErrno) {
    // 使用栈上空间作为预备缓冲区，避免频繁分配内存
    char extrabuf[65536];
    
    struct iovec vec[2];
    const size_t writable = WritableBytes();
    
    // 第一个 iovector 指向缓冲区可写部分
    vec[0].iov_base = BeginWrite();
    vec[0].iov_len = writable;
    
    // 第二个 iovector 指向栈上预备缓冲区
    vec[1].iov_base = extrabuf;
    vec[1].iov_len = sizeof(extrabuf);
    
    // 使用 readv 一次读取，避免数据在内核和用户空间多次拷贝
    const ssize_t n = ::readv(fd, vec, 2);
    
    if (n < 0) {
        *savedErrno = errno;
    } else if (static_cast<size_t>(n) <= writable) {
        // 数据完全写入缓冲区
        writer_index_ += n;
    } else {
        // 数据部分写入缓冲区，部分写入预备缓冲区
        writer_index_ = buffer_.size();
        Append(extrabuf, n - writable);
    }
    
    return n;
}
=======
size_t Buffer::ReadFd(int fd, int* saved_errno) {
    char extrabuff[65536];
    
    const size_t writer_able = WriteableBytes();
    struct iovec vec[2];
    vec[0].iov_base = BeginWrite();
    vec[0].iov_len = writer_able;

    vec[1].iov_base = extrabuff;
    vec[1].iov_len = sizeof(extrabuff);

    const size_t n = readv(fd, vec, 2);

    if (n < 0)
        saved_errno = &errno;
    else if (n < writer_able) 
        writer_index_ += n;
    else {
        writer_index_ = buffer_.size(); 
        Append(extrabuff, n - writer_index_);
    }
    return n;
}

void Buffer::Append(const char* data, size_t len) {
    EnsureWritableBytes(len);    
    std::copy(data, data + len, BeginWrite());
    writer_index_ += len;
}

void Buffer::MakeSpace(size_t len) {
    // move data or make new space
    if (PrependableBytes() + WriteableBytes() < len + kCheapPrepend)  
        buffer_.resize(writer_index_ + len);
    else {
        size_t read_able = ReadableBytes();
        std::copy(buffer_.begin() + reader_index_, buffer_.begin() + writer_index_, buffer_.begin() + kCheapPrepend); 
        reader_index_ = kCheapPrepend;
        writer_index_ = reader_index_ + read_able;
        assert(read_able == ReadableBytes());
    }
}

void Buffer::EnsureWritableBytes(size_t len) {
    if (WriteableBytes() < len)
        MakeSpace(len);
    assert(WriteableBytes() >= len);
}

size_t Buffer::PrependableBytes() const {
    return writer_index_;
}

size_t Buffer::ReadableBytes() const {
    return writer_index_ - reader_index_;
}

size_t Buffer::WriteableBytes() const {
    return buffer_.size() - writer_index_;
}

char* Buffer::BeginWrite() {
    return buffer_.data() + writer_index_;
}

const char* Buffer::Peek() const {
    return buffer_.data() + reader_index_;    
}

void Buffer::Retrieve(size_t len) {
    assert(len <= ReadableBytes());
    if (len < ReadableBytes())
        reader_index_ += len;
    else 
        RetrieveAll();
}

void Buffer::RetrieveAll() {
    reader_index_ = kCheapPrepend;
    writer_index_ = kCheapPrepend;
}


>>>>>>> origin/main
