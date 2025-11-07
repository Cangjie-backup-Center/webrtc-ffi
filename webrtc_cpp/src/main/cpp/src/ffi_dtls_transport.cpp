/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#include "ffi_dtls_transport.h"


namespace webrtc {

ffiIceTransport *ffiDtlsTransport::GetIceTransport() {
    CANGJIE_THROW("TODO");
} 
FFIRTCDtlsTransportState ffiDtlsTransport::GetState() {
    CANGJIE_THROW("TODO");
} 
    
void ffiDtlsTransport::OnStateChange(DtlsTransportInformation info) {

}
void ffiDtlsTransport::OnError(RTCError error) {}

}