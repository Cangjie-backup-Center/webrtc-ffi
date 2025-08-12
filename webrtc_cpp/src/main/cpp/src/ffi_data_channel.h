//
// Created on 2025/8/11.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef WEBRTC4CJ_FFI_DATA_CHANNEL_H
#define WEBRTC4CJ_FFI_DATA_CHANNEL_H
#include <cstdint>
#include "ffi_define_struct.h"
#include "api/data_channel_interface.h"
#include "event/ffi_event_target.h"

namespace webrtc {

class ffiDataChannelObserverTemp : public FFIEventTarget<ffiDataChannelObserverTemp>, public DataChannelObserver {
public:
    explicit ffiDataChannelObserverTemp(rtc::scoped_refptr<DataChannelInterface> dataChannel);
    ~ffiDataChannelObserverTemp() override;

    rtc::scoped_refptr<DataChannelInterface> Get() const
    {
        return dataChannel_;
    }

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
    
protected:
    void SetCJClassID(int64_t id);
    void SetOnStateChange(void (*pe)(int64_t id, int64_t ptr));
    void OnStateChange() override;
    void OnMessage(const DataBuffer& buffer) override;
    void OnBufferedAmountChange(uint64_t sentDataSize) override;

private:
    rtc::scoped_refptr<DataChannelInterface> dataChannel_{};
    
    FFIBinaryType binaryType_ = FFIBinaryType::BLOB;
    std::atomic<uint64_t> bufferedAmountLowThreshold_{0};
    
    void (*cj_func_OnStateChange_)(int64_t id, int64_t ptr);
    int64_t cj_class_id_;
};


}

#endif //WEBRTC4CJ_FFI_DATA_CHANNEL_H
