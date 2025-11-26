/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

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
#include "ffi_dtls_transport.h"

#include <cstdint>
namespace webrtc {

class ffiRtpSender : public CJ_CLASS_BASE::ffiCjClass, public FFIEventTarget<ffiRtpSender>  {
public:
    static ffiRtpSender* NewInstance(
        std::shared_ptr<PeerConnectionFactoryWrapper> factory, rtc::scoped_refptr<PeerConnectionInterface> pc,
        rtc::scoped_refptr<RtpSenderInterface> sender)
    {
        return new ffiRtpSender(factory, pc, sender);
    }

    ffiRtpSender(std::shared_ptr<PeerConnectionFactoryWrapper> factory, rtc::scoped_refptr<PeerConnectionInterface> pc,
        rtc::scoped_refptr<RtpSenderInterface> sender)
    {
        factory_= factory;
        pc_= pc;
        rtpSender_ = sender;
    }
    
    ~ffiRtpSender() override ;
    rtc::scoped_refptr<RtpSenderInterface> Get() const
    {
        return rtpSender_;
    }
//    static GetCapabilities
protected:
    int64_t GetTrack();
    int64_t GetTransport();
    int64_t GetDtmf();
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

}

#endif // WEBRTC4CJ_FFI_RTP_SENDER_H