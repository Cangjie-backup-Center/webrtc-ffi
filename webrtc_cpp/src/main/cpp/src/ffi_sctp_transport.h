#ifndef WEBRTC4CJ_FFI_SCTP_TRANSPORT_H
#define WEBRTC4CJ_FFI_SCTP_TRANSPORT_H

#include "api/sctp_transport_interface.h"

#include "event/ffi_event_target.h"
#include "ffi_cj_class.h"
#include "ffi_define_struct.h"
#include "ffi_rtp_receiver.h"
#include "ffi_dtls_transport.h"
#include <cstdint>

namespace webrtc {

class ffiSctpTransport :
    public FFIEventTarget<ffiSctpTransport>,
    public SctpTransportObserverInterface,
    public CJ_CLASS_BASE::ffiCjClass {
public:
    static ffiSctpTransport* NewInstance(
        std::shared_ptr<PeerConnectionFactoryWrapper> factory, rtc::scoped_refptr<SctpTransportInterface> transport)
    {
        return  new ffiSctpTransport(factory, transport);
    }

    ~ffiSctpTransport() {
        factory_->GetNetworkThread()->BlockingCall([this] { sctpTransport_->UnregisterObserver(); });
    }

    ffiSctpTransport(std::shared_ptr<PeerConnectionFactoryWrapper> factory,
        rtc::scoped_refptr<SctpTransportInterface> transport)
    {
        factory_ = factory;
        sctpTransport_ = transport;
        factory_->GetNetworkThread()->BlockingCall([this] { sctpTransport_->RegisterObserver(this); });
    }

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
#endif // WEBRTC4CJ_FFI_SCTP_TRANSPORT_H