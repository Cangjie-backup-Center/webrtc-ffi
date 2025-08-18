//
// Created on 2025/8/18.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef WEBRTC4CJ_FFI_RTP_SENDER_H
#define WEBRTC4CJ_FFI_RTP_SENDER_H

#include "api/rtp_sender_interface.h"
#include "async_work/uv_work.h"
#include "ffi_cj_class.h"
#include "ffi_define_struct.h"
#include "ffi_dtmf_sender.h"
#include "ffi_media_stream.h"
#include "ffi_rtp_receiver.h"
#include "peer_connection_interface.h"
#include <cstdint>
namespace webrtc {

class PeerConnectionFactoryWrapper;


class ffiRtpSender : public CJ_CLASS_BASE::FFICangjieClassID {
    
public:
    static ffiRtpSender * NewInstance(
        std::shared_ptr<PeerConnectionFactoryWrapper> factory, rtc::scoped_refptr<PeerConnectionInterface> pc,
        rtc::scoped_refptr<RtpSenderInterface> sender) {
        return new ffiRtpSender(factory, pc,sender);
    }
    ffiRtpSender(std::shared_ptr<PeerConnectionFactoryWrapper> factory, rtc::scoped_refptr<PeerConnectionInterface> pc,
        rtc::scoped_refptr<RtpSenderInterface> sender) {
        factory_= factory;
        pc_= pc;
        rtpSender_ = sender;
    }
    ~ffiRtpSender() override ;
    rtc::scoped_refptr<RtpSenderInterface> Get() const {
        return rtpSender_;
    }

protected:

    ffiMediaStreamTrack GetTrack();  // 对应仓颉class
    ffiDtlsTransport GetTransport();// 对应仓颉class
    ffiDtmfSender GetDtmf();// 对应仓颉class 
    void SetParameters(CJ_RTCRtpSendParameters parameters, void (*pe)(int64_t cj_id, int64_t ptr)); // Promise
    CJ_RTCRtpSendParameters GetParameters();
    void ReplaceTrack(ffiMediaStreamTrack* track, void (*pe)(int64_t cj_id, int64_t ptr));  // Promise
    void SetStreams(FFIMediaStream streams[]);
    void GetStats(void (*pe)(int64_t cj_id, int64_t ptr)); // Promise
    
private:
    std::shared_ptr<PeerConnectionFactoryWrapper> factory_;
    rtc::scoped_refptr<PeerConnectionInterface> pc_;
    rtc::scoped_refptr<RtpSenderInterface> rtpSender_;
    
};



};


#endif //WEBRTC4CJ_FFI_RTP_SENDER_H
