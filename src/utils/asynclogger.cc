#include "../network/eventloop.h"
#include "../network/eventloopthread.h"

#include <chrono>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <memory>

#include <unistd.h>
#include <time.h>

#include "asynclogger.h"

AsyncLogger::AsyncLogger(const std::string& basename, size_t rollSize, int flushInterval)
  : basename_(basename),
    rollSize_(rollSize),
    flushInterval_(flushInterval),
    running_(false),
    thread_(nullptr),
    loop_(nullptr),
    currentBuffer_(new Buffer),
    nextBuffer_(new Buffer),
    fp_(nullptr) {
  currentBuffer_->reserve(4 * 1024);  // 4KB初始缓冲区
  nextBuffer_->reserve(4 * 1024);
}

AsyncLogger::~AsyncLogger() {
  if (running_) {
      Stop();
  }
}

void AsyncLogger::Start() {
  running_ = true;

  thread_ = std::make_unique<EventLoopThread>([this](EventLoop* loop) {
      ThreadFunc(loop);  
  }, "LoggerThread");

  loop_ = thread_->StartLoop();
}

void AsyncLogger::Stop() {
  running_ = false;
  loop_->Quit();
}

void AsyncLogger::Append(const char* data, size_t len) {
  loop_->AssertInLoopThread();
  // small data stack process 
  // big data heap process
  if (len <= 256) {
    char temp[256];
    memcpy(temp, data, len);
    loop_->RunInLoop([this, temp, len]() { 
      AppendInLoop(temp, len);
    });
  } else {
    std::string big_temp = (data); 
    loop_->RunInLoop([this, big_temp]() { 
      AppendInLoop(big_temp.data(), big_temp.size());
    });
  }
}

void AsyncLogger::AppendInLoop(const char* data, size_t len) {
  int space = currentBuffer_->capacity() - currentBuffer_->size();
  // space enough process or exchange use the second  
  if (space >= len)
    currentBuffer_->insert(currentBuffer_->end(), data, data + len);
  else {
    buffers_.push_back(currentBuffer_);
    currentBuffer_.reset();   // give out the own shared_ptr 
    
    if (nextBuffer_)
      currentBuffer_ = std::move(nextBuffer_);
    else {
      currentBuffer_.reset(new Buffer);
      currentBuffer_->reserve(4 * 1024);
    }
    
    currentBuffer_->insert(currentBuffer_->end(), data, data + len);
    cond_.notify_one();
  }
}

void AsyncLogger::ThreadFunc(EventLoop* loop) {
  loop->AssertInLoopThread();  
  
  // prepare for write data from buffer to file 
  BufferPtr new_buffer1(new Buffer);   
  BufferPtr new_buffer2(new Buffer);
  new_buffer1->reserve(4 * 1024);
  new_buffer2->reserve(4 * 1024);
  BufferVector write_buffers;
  write_buffers.reserve(16);
  time_t last_roll = time(nullptr);
  
  while (running_) {
    // get data
    {
      std::unique_lock<std::mutex> lock(mutex_);
      if (buffers_.empty()) 
        cond_.wait_for(lock, std::chrono::seconds(1));
      
      // before the write, clloect all log data
      buffers_.push_back(currentBuffer_);
      currentBuffer_ = std::move(new_buffer1);    // use prepared buffer to exchange. more faster.
      write_buffers.swap(buffers_);
    
      // check the second buffer, and add timely.
      if (!nextBuffer_)
        nextBuffer_ = std::move(new_buffer2);
    }
    
    // when the size is too big, delete them only keep two for use.
    // write down this message to log
    if (write_buffers.size() > 25) {
      char time_buf[80];
      std::time_t t = std::time(nullptr);
      std::strftime(time_buf, sizeof(time_buf), "%F %T", std::localtime(&t)); 

      char buf[256];
      snprintf(buf, sizeof buf, "Dropped log messages at %s\n",
              time_buf);
      fputs(buf, fp_);
      write_buffers.erase(write_buffers.begin() + 2, write_buffers.end());
    }
    
    // write data
    for (const auto& buffer : write_buffers) {
      if (!fp_) {
        RollFile();
        last_roll = time(nullptr);
      }
      fwrite(buffer->data(), 1, buffer->size(), fp_);

      // whether need roll log. one day or full.
      if (ftell(fp_) > rollSize_) {
        RollFile();
        last_roll = time(nullptr);
      } else if (time(nullptr) - last_roll >= 86400) {
        RollFile();
        last_roll = time(nullptr);
      }
    }

    // reset spare buffer
    if (!new_buffer1) {
      new_buffer1 = write_buffers.back();
      write_buffers.pop_back();
      new_buffer1->clear();
    }
    if (!new_buffer2) {
      new_buffer2 = write_buffers.back();
      write_buffers.pop_back();
      new_buffer2->clear();
    }

    write_buffers.clear();
    fflush(fp_);
  }
  
  // log close.
  fflush(fp_);
  if (fp_)
    fclose(fp_);
}

void AsyncLogger::RollFile() {
  time_t now = time(nullptr);
  char filename[256];
  strftime(filename, sizeof filename, "%Y%m%d-%H%M%S", localtime(&now));
  std::string log_file = basename_ + "." + filename + ".lgo";
  FILE* fp = fopen(log_file.c_str(), "ae");
  if (fp) {
    if (fp_)
      fclose(fp_);
    fp_ = fp;
  }
}

void AsyncLogger::Flush() {
  loop_->AssertInLoopThread();
  loop_->RunInLoop([this]() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (fp_) {
      fflush(fp_);
    }
  });
}

