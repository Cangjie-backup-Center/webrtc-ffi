/**
 * Copyright (c) 2024 Archermind Technology (Nanjing) Co. Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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
//#include "napi.h"
//#include "napi/native_api.h"

#include "rtc_base/logging.h"

#include "event.h"
#include "event_queue.h"
#include "../utils/marcos.h"

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
    ~FFIEventTarget() noexcept {
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
    
    void Dispatch(std::unique_ptr<Event<T>> event){
        RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
        if(this->stop) return;
        this->Enqueue(std::move(event));
        if (isRunning) {
            condition.notify_one();
        } else {
            this->CreateThread();
        }
    }

    void CreateThread(){
        size_t threads = 1;  // 至少1个线程
        workers.reserve(threads);
        workers.emplace_back([this] {
            this->isRunning = true;
            for (;;) {
                std::unique_lock<std::mutex> lock(this->mutex_);
                // 等待任务或停止信号
                this->condition.wait(lock, [this] {
                    return this->stop || !this->Empty();
                });
                // 停止且任务队列为空时退出
                if (this->stop && this->Empty()) return;
                // 取任务
                auto task = this->Dequeue();
                if (!task) {
                    this->isRunning = false;
                    break;
                }
                // 执行任务（不在锁内执行）
                T* target = static_cast<T*>(this);
                task->Process(*target);
            }
        });
    }

    virtual void Stop(){
        stop = true;
        Dispatch(EmptyEvent<T>::Create());
    }

    bool ShouldStop() const{
        return stop;
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
