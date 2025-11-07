/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */
#define __STDC_WANT_LIB_EXT1__ 1
#include "ffi_data_channel.h"
#include "ffi_exception.h"
#include <string.h>

namespace webrtc {
    ffiDataChannelObserverTemp::ffiDataChannelObserverTemp(rtc::scoped_refptr<DataChannelInterface> dataChannel)
        : dataChannel_(std::move(dataChannel))
    {
        RTC_LOG(LS_VERBOSE) << __FUNCTION__;
        
        dataChannel_->RegisterObserver(this);
    }
    
    ffiDataChannelObserverTemp::~ffiDataChannelObserverTemp()
    {
        RTC_LOG(LS_VERBOSE) << __FUNCTION__;
    
        dataChannel_->UnregisterObserver();
    }
    

// readonly
    std::string ffiDataChannelObserverTemp::GetLabel(){
        RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
        return dataChannel_->label();
    }
    bool ffiDataChannelObserverTemp::GetOrdered(){
        RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
        return dataChannel_->ordered();
    }
    int64_t ffiDataChannelObserverTemp::GetMaxPacketLifeTime(){
        RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
        return dataChannel_->maxPacketLifeTime().value();
    }
    int64_t ffiDataChannelObserverTemp::GetMaxRetransmits(){
        RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
        return  dataChannel_->maxRetransmitsOpt().value();
    }
    std::string ffiDataChannelObserverTemp::GetProtocol(){
        RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
        return dataChannel_->protocol();
    }
    bool ffiDataChannelObserverTemp::GetNegotiated(){
        RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
        return dataChannel_->negotiated();
    }
    int64_t ffiDataChannelObserverTemp::GetId(){
        RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
        return dataChannel_->id();
    }
    FFIDataChannelState ffiDataChannelObserverTemp::GetReadyState(){
        RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
        switch (dataChannel_->state()) {
            case DataChannelInterface::kConnecting:
                return FFIDataChannelState::CONNECTING;
            case DataChannelInterface::kOpen:
                return FFIDataChannelState::OPEN;
            case DataChannelInterface::kClosing:
                return FFIDataChannelState::CLOSING;
            case DataChannelInterface::kClosed:
                return FFIDataChannelState::CLOSED;
            default:
                break;
        }
        CANGJIE_THROW("Invalid state");
    }
    int64_t ffiDataChannelObserverTemp::GetBufferedAmount(){
        RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
        return dataChannel_->buffered_amount();
    }
    int64_t ffiDataChannelObserverTemp::GetBufferedAmountLowThreshold(){
        RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
        return bufferedAmountLowThreshold_.load();
    }
    void ffiDataChannelObserverTemp::SetBufferedAmountLowThreshold(int64_t value){
        RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
        if (value < 0) {
            CANGJIE_THROW("Invalid argument");
        }
        bufferedAmountLowThreshold_.store(value);
    }
    FFIBinaryType ffiDataChannelObserverTemp::GetBinaryType(){
        RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
        return binaryType_;
    }
    void ffiDataChannelObserverTemp::SetBinaryType(FFIBinaryType value){
        RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
        binaryType_ = value;
    }
// readonly

    void ffiDataChannelObserverTemp::Send(uint8_t* data, int64_t size) {
        RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
        if (dataChannel_->state() != DataChannelInterface::kOpen) {
            CANGJIE_THROW("Datachannel state is not open");
        }
        // void* ptr = malloc(size);
        // auto retMemcpy = memcpy_s(ptr, size, data, size);
        // if (retMemcpy != 0) {
        //     CANGJIE_THROW("memcpy_s error");
        // }

        auto ptr = new uint8_t[size];
        memcpy(ptr, data, size);

        dataChannel_->SendAsync(DataBuffer(rtc::CopyOnWriteBuffer(ptr, size), true), [&](RTCError err) {
            if (!err.ok()) {
                RTC_LOG(LS_ERROR) << "send array buffer error: " << err.type() << ", " << err.message();
            }
            if (ptr != nullptr) {
                delete[] ptr;
            }
            ptr = nullptr;
        });
    }

    void ffiDataChannelObserverTemp::Send(char* data) {
        RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
        if (dataChannel_->state() != DataChannelInterface::kOpen) {
            CANGJIE_THROW("Datachannel state is not open");
        }
        std::string str;
        str = data;
        delete data;
        data = nullptr;
        dataChannel_->SendAsync(DataBuffer(str), [&](RTCError err) {
            if (!err.ok()) {
                RTC_LOG(LS_ERROR) << "send array buffer error: " << err.type() << ", " << err.message();
            }
        });
    }
    
    void ffiDataChannelObserverTemp::Close() {
        RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
        dataChannel_->Close();
    }

    void ffiDataChannelObserverTemp::SetOnStateChange(void (*pe)(int64_t id, int64_t ptr)){
        cj_func_OnStateChange_ = pe;
    }

    void ffiDataChannelObserverTemp::SetOnopen(void (*pe)(int64_t id, CJ_Event ptr)){
        cj_func_call_Onopen_ = pe;
    }
    void ffiDataChannelObserverTemp::SetOnclose(void (*pe)(int64_t id, CJ_Event ptr)){
        cj_func_call_Onclose_ = pe;
    }
    void ffiDataChannelObserverTemp::SetOnclosing(void (*pe)(int64_t id, CJ_Event ptr)){
        cj_func_call_Onclosing_ = pe;
    }
    void ffiDataChannelObserverTemp::OnStateChange()
    {
        RTC_LOG(LS_VERBOSE) << __FUNCTION__;
    
        auto state = dataChannel_->state();
        this->Dispatch(CallbackEvent<ffiDataChannelObserverTemp>::Create(
            [this, state](ffiDataChannelObserverTemp& target) {
                RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
                if (state == DataChannelInterface::kOpen) {
                    auto curState = target.dataChannel_->state();
                    if (curState == DataChannelInterface::kClosing || curState == DataChannelInterface::kClosed) {
                        // abort, see https://www.w3.org/TR/webrtc/#announcing-a-data-channel-as-open.
                        return;
                    }
                }
                switch (state) {
                    case DataChannelInterface::kOpen: // onopen
                        if(cj_func_call_Onopen_) {
                            cj_func_call_Onopen_(cj_class_key, CJ_Event{type: "open"});
                        }
                        break;
                    case DataChannelInterface::kClosing: // onopen
                        if(cj_func_call_Onclosing_) {
                            cj_func_call_Onclosing_(cj_class_key, CJ_Event{type: "closing"});
                        }
                        break;
                    case DataChannelInterface::kClosed: // onopen
                        if(cj_func_call_Onclose_) {
                            cj_func_call_Onclose_(cj_class_key, CJ_Event{type: "close"});
                        }
                        this->Stop();
                        break;
                }
            }
        ));
    }
    
    void ffiDataChannelObserverTemp::SetOnMessage(void (*pe)(int64_t id, CJ_MessageEvent ptr)) {
        cj_func_call_OnMessage_ = pe;
    }
    void ffiDataChannelObserverTemp::OnMessage(const DataBuffer& buffer)
    {
        RTC_LOG(LS_VERBOSE) << __FUNCTION__;
        Dispatch(CallbackEvent<ffiDataChannelObserverTemp>::Create(
            [this, buffer](ffiDataChannelObserverTemp& target) {
                RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
                if (buffer.binary) {
                    auto externalData = new rtc::CopyOnWriteBuffer(buffer.data);
                    if (cj_func_call_OnMessage_) {
                        cj_func_call_OnMessage_(cj_class_key, CJ_MessageEvent{
                            type: "message",
                            data_arr: externalData->MutableData(),
                            data_arr_size: (int64_t)externalData->size(),
                            binary: true,
                            data_str: nullptr
                        });
                    }
                } else {
                    // Should be a UTF-8 string
                    if (cj_func_call_OnMessage_) {
                        cj_func_call_OnMessage_(cj_class_key, CJ_MessageEvent{
                            type: "message",
                            data_arr: nullptr,
                            data_arr_size: -1,
                            binary: false,
                            data_str: reinterpret_cast<const char*>(buffer.data.data())
                        });
                    }
                }
        }));
    }
    
    void ffiDataChannelObserverTemp::OnBufferedAmountChange(uint64_t sentDataSize)
    {
        // should not reached
        (void)sentDataSize;
        RTC_LOG(LS_VERBOSE) << __FUNCTION__;
    }
}