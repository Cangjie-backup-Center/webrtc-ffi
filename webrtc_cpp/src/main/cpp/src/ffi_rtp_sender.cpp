//
// Created on 2025/8/20.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include "ffi_rtp_sender.h"
#include <cstdint>


namespace webrtc {

int64_t ffiRtpSender::GetTrack() {
    RTC_LOG(LS_VERBOSE) << __FUNCTION__;

    auto track = rtpSender_->track();
    if (!track) {   
        return 0;
    }
    return (int64_t)new ffiMediaStreamTrack(factory_, track);
}
int64_t ffiRtpSender::GetTransport() {
    RTC_LOG(LS_VERBOSE) << __FUNCTION__;

    auto transport = rtpSender_->dtls_transport();
    if (!transport) {
        return 0;
    }
    return (int64_t)new ffiDtlsTransport(factory_, transport);
}
int64_t ffiRtpSender::GetDtmf(){
    RTC_LOG(LS_VERBOSE) << __FUNCTION__;

    auto sender = rtpSender_->GetDtmfSender();
    if (!sender) {
        return 0;
    }
    return (int64_t)new ffiDtmfSender(sender);
}
void ffiRtpSender::SetParameters(CJ_RTCRtpSendParameters parameters, void (*pe)(int64_t cj_id, int64_t ptr)){
    RTC_LOG(LS_VERBOSE) << __FUNCTION__;

    
}
CJ_RTCRtpSendParameters ffiRtpSender::GetParameters(){
    RTC_LOG(LS_VERBOSE) << __FUNCTION__;
    auto parm = rtpSender_->GetParameters();
    CANGJIE_THROW("TODO"); // TODO
}
void ffiRtpSender::ReplaceTrack(ffiMediaStreamTrack* track, void (*pe)(int64_t cj_id, int64_t ptr)){
//    this->Dispatch()
}
void ffiRtpSender::SetStreams(FFIMediaStream streams[]){
    
}
void ffiRtpSender::GetStats(void (*pe)(int64_t cj_id, int64_t ptr)){
    
}


}
