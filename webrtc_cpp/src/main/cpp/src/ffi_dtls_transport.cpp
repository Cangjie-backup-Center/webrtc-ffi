/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#include "ffi_dtls_transport.h"

namespace webrtc {

void ffiDtlsTransport::OnStateChange(DtlsTransportInformation info)
{
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
    auto dtlsTransportState = info.state();

    if (this->ShouldStop()) {
        return;   
    }
    if (dtlsTransportState == webrtc::DtlsTransportState::kClosed) {
        this->Stop();
    }
}

void ffiDtlsTransport::OnError(RTCError error)
{
    RTC_DLOG(LS_ERROR) << __FUNCTION__ << ": " << error.message();

    if (this->ShouldStop()) {
        return;   
    }

    const char cjEventNameError[] = "error";
}

} // namespace webrtc