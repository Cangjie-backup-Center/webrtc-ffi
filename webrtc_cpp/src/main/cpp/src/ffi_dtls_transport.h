//
// Created on 2025/8/14.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef WEBRTC4CJ_FFI_DTLS_TRANSPORT_H
#define WEBRTC4CJ_FFI_DTLS_TRANSPORT_H


#include "api/dtls_transport_interface.h"

#include "event/ffi_event_target.h"
#include "ffi_define_struct.h"

namespace webrtc {

class PeerConnectionFactoryWrapper;
class ffiIceTransport;

class ffiDtlsTransport : public FFIEventTarget<ffiDtlsTransport>, public DtlsTransportObserverInterface {
public:
    static ffiDtlsTransport * NewInstance(
        std::shared_ptr<PeerConnectionFactoryWrapper> factory,
        rtc::scoped_refptr<DtlsTransportInterface> dtlsTransport) {
        return new ffiDtlsTransport(factory, dtlsTransport);
    }
    
     ffiDtlsTransport(
        std::shared_ptr<PeerConnectionFactoryWrapper> factory,
        rtc::scoped_refptr<DtlsTransportInterface> dtlsTransport) {
        factory_ = factory;
        dtlsTransport_ = dtlsTransport;
    }

    ~ffiDtlsTransport();

public:
    /*
    export interface RTCDtlsTransport extends EventTarget {
  readonly iceTransport: RTCIceTransport;
  readonly state: RTCDtlsTransportState;

  onstatechange: ((this: RTCDtlsTransport, ev: Event) => any) | null;
  onerror: ((this: RTCDtlsTransport, ev: RTCErrorEvent) => any) | null;

  getRemoteCertificates(): ArrayBuffer[];
}

declare var RTCDtlsTransport: {
  prototype: RTCDtlsTransport;
  new(): RTCDtlsTransport;
};
*/
    ffiIceTransport *GetIceTransport(); // TODO  返回值需要重新定义
    FFIRTCDtlsTransportState GetState(); // TODO  返回值需要重新定义
//    void *GetEventHandler(); // TODO  返回值需要重新定义
//    void SetEventHandler(); // TODO  参数需要重新定义
//    void *GetRemoteCertificates(); // TODO  返回值需要重新定义
    
    void OnStateChange(DtlsTransportInformation info) override;
    void OnError(RTCError error) override;

private:

    std::shared_ptr<PeerConnectionFactoryWrapper> factory_;
    rtc::scoped_refptr<DtlsTransportInterface> dtlsTransport_;
};

}

#endif //WEBRTC4CJ_FFI_DTLS_TRANSPORT_H
