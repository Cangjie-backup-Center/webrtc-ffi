//
// Created on 2025/8/18.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef WEBRTC4CJ_FFI_SCTP_TRANSPORT_H
#define WEBRTC4CJ_FFI_SCTP_TRANSPORT_H

#include "api/sctp_transport_interface.h"

#include "event/ffi_event_target.h"
#include "ffi_cj_class.h"
#include "ffi_define_struct.h"
#include "ffi_dtls_transport.h"
#include "ffi_rtp_receiver.h"
#include <cstdint>

namespace webrtc {

class PeerConnectionFactoryWrapper;

class ffiSctpTransport : public FFIEventTarget<ffiSctpTransport>, public SctpTransportObserverInterface, public CJ_CLASS_BASE::FFICangjieClassID {
public:
//    static void Init(Napi::Env env, Napi::Object exports);

    static ffiSctpTransport* NewInstance(
        std::shared_ptr<PeerConnectionFactoryWrapper> factory, rtc::scoped_refptr<SctpTransportInterface> transport) {
        return  new ffiSctpTransport(factory, transport);
    }

    ~ffiSctpTransport() {}

    ffiSctpTransport(std::shared_ptr<PeerConnectionFactoryWrapper> factory, rtc::scoped_refptr<SctpTransportInterface> transport){
        factory_ = factory;
        sctpTransport_ = transport;
    }

//    rtc::scoped_refptr<SctpTransportInterface> Get() const {
//        return sctpTransport_;
//    }

    void SetOnStateChange(void (*pe)(int64_t id, CJ_Event ptr));
    
protected:
    // JS
    int64_t GetMaxChannels();
    int64_t GetMaxMessageSize();
    FFIRTCSctpTransportState GetState();
    ffiDtlsTransport* GetTransport();


    void OnStateChange(SctpTransportInformation info) override;

private:
    void (*cj_func_call_OnStateChange_)(int64_t id, CJ_Event ptr) = nullptr;
    std::shared_ptr<PeerConnectionFactoryWrapper> factory_;
    rtc::scoped_refptr<SctpTransportInterface> sctpTransport_;
};

} // namespace webrtc
#endif //WEBRTC4CJ_FFI_SCTP_TRANSPORT_H
