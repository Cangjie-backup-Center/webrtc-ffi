/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#ifndef WEBRTC4CJ_FFI_RTP_TRANSCEIVER_H
#define WEBRTC4CJ_FFI_RTP_TRANSCEIVER_H

#include "api/rtp_receiver_interface.h"
#include "api/peer_connection_interface.h"
#include "ffi_exception.h"
#include "ffi_rtp_sender.h"

namespace webrtc {

class PeerConnectionFactoryWrapper;

class ffiRtpTransceiver {
public:
    static ffiRtpTransceiver* NewInstance(
        std::shared_ptr<PeerConnectionFactoryWrapper> factory, 
        rtc::scoped_refptr<PeerConnectionInterface> pc,
        rtc::scoped_refptr<RtpTransceiverInterface> transceiver) {
        RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
        if (!factory || !pc || !transceiver) {
            CANGJIE_THROW("Invalid argument");
        }
        return new ffiRtpTransceiver(factory, pc, transceiver);
    } 
    
    ffiRtpTransceiver(std::shared_ptr<PeerConnectionFactoryWrapper> factory, 
        rtc::scoped_refptr<PeerConnectionInterface> pc,
        rtc::scoped_refptr<RtpTransceiverInterface> transceiver){
        RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
        factory_ = factory;
        pc_ = pc;
        rtpTransceiver_ = transceiver;
    }
    ~ffiRtpTransceiver() ;

    rtc::scoped_refptr<RtpTransceiverInterface> Get() const {
        return rtpTransceiver_;
    }
    

    std::string GetMid(); 
    ffiRtpSender GetSender(); 
    ffiRtpReceiver GetReceiver(); 
    FFIRTCRtpTransceiverDirection GetDirection(); 
    void SetDirection(FFIRTCRtpTransceiverDirection n); 
    FFIRTCRtpTransceiverDirection GetCurrentDirection(); 
    void Stop(); 
    void SetCodecPreferences(CJ_RTCRtpCodec codecs[]); 
private:
    std::shared_ptr<PeerConnectionFactoryWrapper> factory_;
    rtc::scoped_refptr<PeerConnectionInterface> pc_;
    rtc::scoped_refptr<RtpTransceiverInterface> rtpTransceiver_;
};

}
#endif //WEBRTC4CJ_FFI_RTP_TRANSCEIVER_H
