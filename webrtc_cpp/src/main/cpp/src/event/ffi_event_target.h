/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#ifndef WEBRTC_EVENT_FFI_EVENT_TARGET_H
#define WEBRTC_EVENT_FFI_EVENT_TARGET_H

#include <map>
#include <any>
#include <queue>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <functional>

#include "rtc_base/logging.h"

#include "event.h"
#include "event_queue.h"
#include "../utils/marcos.h"

namespace webrtc {

template <typename T>
class FFIEventTarget : public EventQueue<T> {
public:
    explicit FFIEventTarget()
    {
        RTC_DLOG(LS_VERBOSE) << __FUNCTION__;

        // 创建工作线程
        workerThread_ = std::thread([this]() {
            this->Run();
        });
    }

    ~FFIEventTarget()
    {
        Stop();
        if (workerThread_.joinable()) {
            workerThread_.join();
        }
    }

    void Dispatch(std::unique_ptr<Event<T>> event)
    {
        RTC_DLOG(LS_VERBOSE) << __FUNCTION__;

        this->Enqueue(std::move(event));
        conditionVariable_.notify_one();
    }

    virtual void Stop()
    {
        shouldStop_ = true;
        Dispatch(EmptyEvent<T>::Create());
    }

    bool ShouldStop() const
    {
        return shouldStop_;
    }

    bool GetEventHandler(const std::string& type, std::function<void(T&, const std::vector<std::any>&)>& fn) const
    {
        UNUSED std::lock_guard<std::mutex> lock(mutex_);

        auto it = eventHandlers_.find(type);
        if (it == eventHandlers_.end()) {
            return false;
        }

        fn = it->second;
        return true;
    }

    void SetEventHandler(const std::string& type, const std::function<void(T&, const std::vector<std::any>&)>& fn)
    {
        UNUSED std::lock_guard<std::mutex> lock(mutex_);

        eventHandlers_[type] = fn;
    }

    void RemoveEventHandler(const std::string& type)
    {
        UNUSED std::lock_guard<std::mutex> lock(mutex_);

        auto it = eventHandlers_.find(type);
        if (it != eventHandlers_.end()) {
            eventHandlers_.erase(it);
        }
    }

protected:
    virtual void Run()
    {
        RTC_DLOG(LS_VERBOSE) << __FUNCTION__;

        while (!shouldStop_) {
            std::unique_lock<std::mutex> lock(conditionMutex_);
            conditionVariable_.wait(lock, [this]() {
                return !this->IsEmpty() || shouldStop_;
            });

            while (!this->IsEmpty() && !shouldStop_) {
                auto event = this->Dequeue();
                if (!event) {
                    break;
                }

                T* target = static_cast<T*>(this);
                event->Process(*target);
            }
        }

        if (shouldStop_) {
            DidStop();
        }
    }

    virtual void DidStop()
    {
        // Do nothing.
    }

protected:
    void MakeCallback(const char* name, const std::vector<std::any>& args)
    {
        RTC_DLOG(LS_VERBOSE) << __FUNCTION__ << ": " << name;

        std::function<void(T&, const std::vector<std::any>&)> func;
        GetEventHandler(name, func);
        if (!func) {
            RTC_DLOG(LS_WARNING) << "No event handler: " << name;
            return;
        }

        T* target = static_cast<T*>(this);
        func(*target, args);
    }

private:
    std::atomic<bool> shouldStop_{false};
    mutable std::mutex mutex_;
    std::map<std::string, std::function<void(T&, const std::vector<std::any>&)>> eventHandlers_;
   
    // 替换Napi的ThreadSafeFunction为C++标准库的线程和条件变量
    std::thread workerThread_;
    std::condition_variable conditionVariable_;
    std::mutex conditionMutex_;
};

} // namespace webrtc

#endif // WEBRTC_EVENT_FFI_EVENT_TARGET_H