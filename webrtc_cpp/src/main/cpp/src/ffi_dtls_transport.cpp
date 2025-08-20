//
// Created on 2025/8/20.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include "ffi_dtls_transport.h"


namespace webrtc {

ffiIceTransport *ffiDtlsTransport::GetIceTransport() {
    CANGJIE_THROW("TODO");
} 
FFIRTCDtlsTransportState ffiDtlsTransport::GetState() {
    CANGJIE_THROW("TODO");
} 
    
void ffiDtlsTransport::OnStateChange(DtlsTransportInformation info) {}
void ffiDtlsTransport::OnError(RTCError error) {}

}