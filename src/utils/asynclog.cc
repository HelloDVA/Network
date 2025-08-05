
#include "AsyncLogging.h"
#include "LogFile.h"
#include <chrono>
#include <assert.h>

AsyncLogging::AsyncLogging(const std::string& basename,
                          size_t rollSize,
                          int flushInterval)
    : basename_(basename),
      rollSize_(rollSize),
      flushInterval_(flushInterval),
      running_(false),
      currentBuffer_(new Buffer),
      nextBuffer_(new Buffer) {
    currentBuffer_->reserve(4 * 1024);  // 4KB
    nextBuffer_->reserve(4 * 1024);
}

void AsyncLogging::append(const char* logline, int len) {
    std::lock_guard<std::mutex> lock(mutex_);
    
    if (currentBuffer_->capacity() - currentBuffer_->size() > len) {
        currentBuffer_->insert(currentBuffer_->end(), logline, logline + len);
    } else {
        buffers_.push_back(currentBuffer_);
        currentBuffer_.reset();
        
        if (nextBuffer_) {
            currentBuffer_ = std::move(nextBuffer_);
        } else {
            currentBuffer_.reset(new Buffer);
            currentBuffer_->reserve(4 * 1024);
        }
        
        currentBuffer_->insert(currentBuffer_->end(), logline, logline + len);
        cond_.notify_one();
    }
}

void AsyncLogging::threadFunc() {
    LogFile output(basename_, rollSize_, false);
    
    BufferPtr newBuffer1(new Buffer);
    BufferPtr newBuffer2(new Buffer);
    newBuffer1->reserve(4 * 1024);
    newBuffer2->reserve(4 * 1024);
    
    BufferVector buffersToWrite;
    buffersToWrite.reserve(16);
    
    while (running_) {
        {
            std::unique_lock<std::mutex> lock(mutex_);
            if (buffers_.empty()) {
                cond_.wait_for(lock, std::chrono::seconds(flushInterval_));
            }
            
            buffers_.push_back(currentBuffer_);
            currentBuffer_ = std::move(newBuffer1);
            buffersToWrite.swap(buffers_);
            
            if (!nextBuffer_) {
                nextBuffer_ = std::move(newBuffer2);
            }
        }
        
        // 处理超大日志（避免单条日志占用过多内存）
        if (buffersToWrite.size() > 25) {
            buffersToWrite.erase(buffersToWrite.begin() + 2, buffersToWrite.end());
        }
        
        // 写入文件
        for (const auto& buffer : buffersToWrite) {
            output.append(buffer->data(), buffer->size());
        }
        
        // 重置缓冲区
        if (buffersToWrite.size() > 2) {
            buffersToWrite.resize(2);
        }
        
        if (!newBuffer1) {
            newBuffer1 = buffersToWrite.back();
            buffersToWrite.pop_back();
            newBuffer1->clear();
        }
        
        if (!newBuffer2) {
            newBuffer2 = buffersToWrite.back();
            buffersToWrite.pop_back();
            newBuffer2->clear();
        }
        
        buffersToWrite.clear();
        output.flush();
    }
    output.flush();
}