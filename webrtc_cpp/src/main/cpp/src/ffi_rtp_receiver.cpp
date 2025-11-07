/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

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
