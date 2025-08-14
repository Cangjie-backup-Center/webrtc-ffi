//
// Created on 2025/8/14.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef WEBRTC4CJ_FFI_RTP_RECEIVER_H
#define WEBRTC4CJ_FFI_RTP_RECEIVER_H

#include "api/rtp_receiver_interface.h"
#include "api/peer_connection_interface.h"

namespace webrtc {

class PeerConnectionFactoryWrapper;
class ffiMediaStreamTrack;
class ffiDtlsTransport;

class ffiRtpReceiver {
public:
    static ffiRtpReceiver* NewInstance(
        std::shared_ptr<PeerConnectionFactoryWrapper>, rtc::scoped_refptr<PeerConnectionInterface> pc,
        rtc::scoped_refptr<RtpReceiverInterface> receiver);
    ~ffiRtpReceiver();
    rtc::scoped_refptr<RtpReceiverInterface> Get() const;
    
/*
    export interface RTCRtpReceiver {
  readonly track: MediaStreamTrack;
  readonly transport: RTCDtlsTransport | null;

  getParameters(): RTCRtpReceiveParameters;
  getStats(): Promise<RTCStatsReport>;
  getContributingSources(): RTCRtpContributingSource[];
  getSynchronizationSources(): RTCRtpSynchronizationSource[];
}
*/
    ffiMediaStreamTrack *GetTrack();
    ffiDtlsTransport *GetTransport();
    void *GetParameters();// TODO  返回值需要重新定义
    void *GetStats(); // TODO  返回值需要重新定义
    void *GetContributingSources(); // TODO  返回值需要重新定义
    void *GetSynchronizationSources(); // TODO  返回值需要重新定义
    
private:
    
    std::shared_ptr<PeerConnectionFactoryWrapper> factory_;
    rtc::scoped_refptr<PeerConnectionInterface> pc_;
    rtc::scoped_refptr<RtpReceiverInterface> rtpReceiver_;
    
};

}

#endif //WEBRTC4CJ_FFI_RTP_RECEIVER_H
