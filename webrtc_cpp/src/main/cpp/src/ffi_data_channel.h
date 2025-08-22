//
// Created on 2025/8/11.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef WEBRTC4CJ_FFI_DATA_CHANNEL_H
#define WEBRTC4CJ_FFI_DATA_CHANNEL_H
#include "api/data_channel_interface.h"
#include "event/ffi_event_target.h"
#include "ffi_cj_class.h"
#include "ffi_define_struct.h"
#include <cstdint>

namespace webrtc {

class ffiDataChannelObserverTemp : public FFIEventTarget<ffiDataChannelObserverTemp>,
                                   public DataChannelObserver,
                                   public CJ_CLASS_BASE::FFICangjieClassID {
public:
    explicit ffiDataChannelObserverTemp(rtc::scoped_refptr<DataChannelInterface> dataChannel);
    ~ffiDataChannelObserverTemp() override;

    rtc::scoped_refptr<DataChannelInterface> Get() const { return dataChannel_; }

// readonly
    std::string GetLabel();
    bool GetOrdered();
    int64_t GetMaxPacketLifeTime();
    int64_t GetMaxRetransmits();
    std::string GetProtocol();
    bool GetNegotiated();
    int64_t GetId();
    FFIDataChannelState GetReadyState();
    int64_t GetBufferedAmount();
    int64_t GetBufferedAmountLowThreshold();
    void SetBufferedAmountLowThreshold(int64_t value);
    FFIBinaryType GetBinaryType();
    void SetBinaryType(FFIBinaryType value);
// readonly
    
    void Send(uint8_t* data, int64_t size);
    void Send(char* data);
    void Close();
    

    void SetOnopen(void (*pe)(int64_t id, CJ_Event ptr));
    void SetOnclose(void (*pe)(int64_t id, CJ_Event ptr));
    void SetOnclosing(void (*pe)(int64_t id, CJ_Event ptr));
    void SetOnMessage(void (*pe)(int64_t id, CJ_MessageEvent ptr));

protected:
    void SetOnStateChange(void (*pe)(int64_t id, int64_t ptr));
    void OnStateChange() override;
    void OnMessage(const DataBuffer &buffer) override;
    void OnBufferedAmountChange(uint64_t sentDataSize) override;

private:
    void (*cj_func_call_Onopen_)(int64_t id, CJ_Event ptr) = nullptr;
    void (*cj_func_call_Onclose_)(int64_t id, CJ_Event ptr) = nullptr;
    void (*cj_func_call_Onclosing_)(int64_t id, CJ_Event ptr) = nullptr;
    void (*cj_func_call_OnMessage_)(int64_t id, CJ_MessageEvent ptr) = nullptr;

    rtc::scoped_refptr<DataChannelInterface> dataChannel_{};

    FFIBinaryType binaryType_ = FFIBinaryType::BLOB;
    std::atomic<uint64_t> bufferedAmountLowThreshold_{0};

    void (*cj_func_OnStateChange_)(int64_t id, int64_t ptr);
};


} // namespace webrtc

#endif // WEBRTC4CJ_FFI_DATA_CHANNEL_H
