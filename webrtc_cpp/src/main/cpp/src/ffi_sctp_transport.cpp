/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#include "ffi_sctp_transport.h"
#include "ffi_dtls_transport.h"

namespace webrtc {


int64_t ffiSctpTransport::GetMaxChannels(){
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
    auto maxChannels = sctpTransport_->Information().MaxChannels();
    return maxChannels.value();
}
int64_t ffiSctpTransport::GetMaxMessageSize() {
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
    auto maxMessageSize = sctpTransport_->Information().MaxMessageSize();
    return maxMessageSize.value();
}
FFIRTCSctpTransportState ffiSctpTransport::GetState() {
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__;

    switch (sctpTransport_->Information().state()) {
        case SctpTransportState::kConnecting:
            return FFIRTCSctpTransportState::CONNECTING;
        case SctpTransportState::kConnected:
            return FFIRTCSctpTransportState::CONNECTED;
        case SctpTransportState::kClosed:
            return FFIRTCSctpTransportState::CLOSED;
        default:
            break;
    }
    CANGJIE_THROW("Invalid state");
}
ffiDtlsTransport* ffiSctpTransport::GetTransport(){
    auto transport = sctpTransport_->Information().dtls_transport();
    return ffiDtlsTransport::NewInstance(factory_, transport) ;
}

void ffiSctpTransport::SetOnStateChange(void (*pe)(int64_t id, CJ_Event ptr)) {
    cj_func_call_OnStateChange_ = pe;
}

void ffiSctpTransport::OnStateChange(SctpTransportInformation info) {
    
    RTC_LOG(LS_VERBOSE) << __FUNCTION__;

    auto sctpTransportState = info.state();

    Dispatch(CallbackEvent<ffiSctpTransport>::Create([this, sctpTransportState](ffiSctpTransport& target) {
        RTC_DCHECK_EQ(this, &target);
        if (cj_func_call_OnStateChange_ && this->cj_class_key)
            cj_func_call_OnStateChange_(this->cj_class_key, CJ_Event{type: "statechange"});
        if (sctpTransportState == SctpTransportState::kClosed) {
            target.Stop();
        }
    }));
}

}