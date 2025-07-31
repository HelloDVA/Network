
#include "buffer.h"


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