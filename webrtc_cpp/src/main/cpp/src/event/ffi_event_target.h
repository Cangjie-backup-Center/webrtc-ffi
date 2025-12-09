/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#ifndef WEBRTC_EVENT_EVENT_TARGET_H
#define WEBRTC_EVENT_EVENT_TARGET_H

#include <cstdint>
#include <map>
#include <queue>
#include <mutex>
#include <thread>
#include <future>
#include "ffi_exception.h"
#include "rtc_base/logging.h"

#include "event.h"
#include "event_queue.h"

namespace webrtc {

using FuncPtr = void (*)(int64_t classID, int64_t ptr);

template <typename T>
class FFIEventTarget : public EventQueue<T> {
public:
    explicit FFIEventTarget()
        : stop(false), isRunning(false)
    {
        RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
    }

    // 优雅关闭线程池
    ~FFIEventTarget() noexcept
    {
        RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
        {
            std::unique_lock<std::mutex> lock(mutex_);
            stop = true;
        }
        // 唤醒所有线程
        condition.notify_all();
        // 等待所有线程完成
        for (std::thread &worker : workers) {
            if (worker.joinable()) {
                worker.join();
            }
        }
    }
    
    void Dispatch(std::unique_ptr<Event<T>> event) {
        RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
    
        // 核心：锁覆盖所有关键操作（检查stop + 入队 + 判断isRunning + 唤醒/创建线程）
        std::unique_lock<std::mutex> lock(mutex_);
    
        // 1. 加锁后检查stop，消除竞态窗口
        if (this->stop) {
            return;
        }
    
        // 2. 入队（锁内执行，保证队列线程安全）
        this->Enqueue(std::move(event));
    
        // 3. 判断是否需要创建线程/唤醒线程（锁内原子执行）
        if (isRunning) {
            // 唤醒等待的工作线程处理新任务
            condition.notify_one();
        } else {
            // 仅在无运行线程时创建1个线程
            this->CreateThread();
        }
    
        // 锁自动释放（unique_lock析构）
    }

    void CreateThread() {
        size_t threads = 1;
        workers.reserve(threads);
        
        // 锁内先标记isRunning=true，避免其他线程重复创建
        isRunning = true; 
        workers.emplace_back([this] {
            for (;;) {
                std::unique_lock<std::mutex> lock(this->mutex_);
                this->condition.wait(lock, [this] {
                    return this->stop || !this->Empty();
                });
                if (this->stop && this->Empty()) {
                    // 退出前标记isRunning=false
                    this->isRunning = false;
                    return;
                }
                auto task = this->Dequeue();
                if (!task) {
                    this->isRunning = false;
                    break;
                }
                lock.unlock(); // 解锁后执行任务，减少锁粒度
                T* target = static_cast<T*>(this);
                task->Process(*target);
            }
        });
    }
    
    virtual void Stop() {
        std::unique_lock<std::mutex> lock(mutex_);
        stop = true;
        condition.notify_all(); // 唤醒所有线程
        // 无需在Stop中入队空事件，notify_all已足够唤醒线程检查stop
    }
    bool ShouldStop() const
    {
        return stop;
    }
    
    bool Empty()
    {
        return EventQueue<T>::Empty();
    }

private:
    std::vector<std::thread> workers;
    std::condition_variable condition;
    std::atomic<bool> stop;
    std::atomic<bool> isRunning;
    mutable std::mutex mutex_;
};

} // namespace webrtc

#endif // WEBRTC_EVENT_EVENT_TARGET_H