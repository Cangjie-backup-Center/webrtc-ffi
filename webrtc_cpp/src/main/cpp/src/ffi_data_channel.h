/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#ifndef WEBRTC4CJ_FFI_DATA_CHANNEL_H
#define WEBRTC4CJ_FFI_DATA_CHANNEL_H
#include "api/data_channel_interface.h"
#include "event/ffi_event_target.h"
#include "ffi_cj_class.h"
#include "ffi_define_struct.h"
#include "peer_connection_factory.h"
#include <cstdint>

namespace webrtc {

class ffiDataChannel {
};

class ffiDataChannelObserverTemp : public FFIEventTarget<ffiDataChannelObserverTemp>,
                                   public DataChannelObserver,
                                   public CJ_CLASS_BASE::ffiCjClass {
public:
    explicit ffiDataChannelObserverTemp(std::shared_ptr<PeerConnectionFactoryWrapper> factory,
                                        rtc::scoped_refptr<DataChannelInterface> dataChannel);
    ~ffiDataChannelObserverTemp() override;

    rtc::scoped_refptr<DataChannelInterface> Get() const
    {
        return dataChannel_;
    }

     std::shared_ptr<PeerConnectionFactoryWrapper> GetFactory() const
     {
         return factory_;
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
    
    void Send(uint8_t* data, int64_t size);
    void Send(std::string dataStr);
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
    std::shared_ptr<PeerConnectionFactoryWrapper> factory_;
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
