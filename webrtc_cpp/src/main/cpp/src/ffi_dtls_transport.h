/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#ifndef WEBRTC4CJ_FFI_DTLS_TRANSPORT_H
#define WEBRTC4CJ_FFI_DTLS_TRANSPORT_H


#include "api/dtls_transport_interface.h"

#include "event/ffi_event_target.h"
#include "ffi_define_struct.h"
#include "peer_connection_factory.h"
#include "ffi_ice_transport.h"

#include <hilog/log.h>

namespace webrtc {

class ffiDtlsTransport : public FFIEventTarget<ffiDtlsTransport>, public DtlsTransportObserverInterface {
public:
    static ffiDtlsTransport* NewInstance(
        std::shared_ptr<PeerConnectionFactoryWrapper> factory,
        rtc::scoped_refptr<DtlsTransportInterface> dtlsTransport)
    {
        return new ffiDtlsTransport(factory, dtlsTransport);
    }
    
    ffiDtlsTransport(
        std::shared_ptr<PeerConnectionFactoryWrapper> factory,
        rtc::scoped_refptr<DtlsTransportInterface> dtlsTransport)
    {
        factory_ = factory;
        dtlsTransport_ = dtlsTransport;
        factory_->GetNetworkThread()->PostTask([this] { dtlsTransport_->RegisterObserver(this); });
    }

    ~ffiDtlsTransport() {
        OH_LOG_Print(LOG_APP, LOG_ERROR, 66666, "ohos_webrtc", "----- ffiDtlsTransport::~ffiDtlsTransport");
    }

public:
    void OnStateChange(DtlsTransportInformation info) override;
    void OnError(RTCError error) override;

private:

    std::shared_ptr<PeerConnectionFactoryWrapper> factory_;
    rtc::scoped_refptr<DtlsTransportInterface> dtlsTransport_;
};

}

#endif // WEBRTC4CJ_FFI_DTLS_TRANSPORT_H
