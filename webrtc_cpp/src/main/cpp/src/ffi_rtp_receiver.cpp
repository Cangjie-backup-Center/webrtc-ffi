//
// Created on 2025/8/14.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include "ffi_rtp_receiver.h"
#include "ffi_exception.h"

namespace webrtc {

ffiRtpReceiver *ffiRtpReceiver::NewInstance(std::shared_ptr<PeerConnectionFactoryWrapper> factory,
                                            rtc::scoped_refptr<PeerConnectionInterface> pc,
                                            rtc::scoped_refptr<RtpReceiverInterface> receiver) {
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
    if (!factory || !pc || !receiver) {
        CANGJIE_THROW("Invalid argument");
    }
    ffiRtpReceiver *ffrr = new ffiRtpReceiver();
    ffrr->factory_ = factory;
    ffrr->pc_ = pc;
    ffrr->rtpReceiver_ = receiver;
    return ffrr;
}

ffiRtpReceiver::~ffiRtpReceiver(){
    
}

rtc::scoped_refptr<RtpReceiverInterface> ffiRtpReceiver::Get() const {
    return this->rtpReceiver_;
}




} // namespace webrtc
