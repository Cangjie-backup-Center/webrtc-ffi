/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#ifndef WEBRTC4CJ_FFI_RTP_RECEIVER_H
#define WEBRTC4CJ_FFI_RTP_RECEIVER_H

#include "api/rtp_receiver_interface.h"
#include "api/peer_connection_interface.h"
#include "peer_connection_factory.h"
#include "ffi_media_stream_track.h"
#include "ffi_dtls_transport.h"

namespace webrtc {

class ffiRtpReceiver {
public:
    static ffiRtpReceiver* NewInstance(std::shared_ptr<PeerConnectionFactoryWrapper> factory,
        rtc::scoped_refptr<PeerConnectionInterface> pc,
        rtc::scoped_refptr<RtpReceiverInterface> receiver);
    ~ffiRtpReceiver();
    rtc::scoped_refptr<RtpReceiverInterface> Get() const;
    
    ffiMediaStreamTrack* GetTrack();
    ffiDtlsTransport* GetTransport();
    void* GetParameters();
    void* GetStats();
    void* GetContributingSources();
    void* GetSynchronizationSources();
    
private:
    std::shared_ptr<PeerConnectionFactoryWrapper> factory_;
    rtc::scoped_refptr<PeerConnectionInterface> pc_;
    rtc::scoped_refptr<RtpReceiverInterface> rtpReceiver_;
};

}
#endif // WEBRTC4CJ_FFI_RTP_RECEIVER_H
