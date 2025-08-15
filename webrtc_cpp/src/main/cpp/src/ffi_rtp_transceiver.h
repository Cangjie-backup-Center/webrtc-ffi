//
// Created on 2025/8/14.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef WEBRTC4CJ_FFI_RTP_TRANSCEIVER_H
#define WEBRTC4CJ_FFI_RTP_TRANSCEIVER_H

#include "api/rtp_receiver_interface.h"
#include "api/peer_connection_interface.h"

namespace webrtc {

class PeerConnectionFactoryWrapper;

class ffiRtpTransceiver {
public:
    static ffiRtpTransceiver* NewInstance(
        std::shared_ptr<PeerConnectionFactoryWrapper> factory, 
        rtc::scoped_refptr<PeerConnectionInterface> pc,
        rtc::scoped_refptr<RtpTransceiverInterface> transceiver);  // TODO
    
    ~ffiRtpTransceiver() ;

    rtc::scoped_refptr<RtpTransceiverInterface> Get() const;
    
    /*
    // https://www.w3.org/TR/webrtc/#rtcrtptransceiver-interface
export interface RTCRtpTransceiver {
  readonly mid: string | null;
  readonly sender: RTCRtpSender;
  readonly receiver: RTCRtpReceiver;
  direction: RTCRtpTransceiverDirection;
  readonly currentDirection: RTCRtpTransceiverDirection | null;

  stop(): void;
  setCodecPreferences(codecs: RTCRtpCodec[]): void;
}

declare var RTCRtpTransceiver: {
  prototype: RTCRtpTransceiver;
  new(): RTCRtpTransceiver;
};
    */
    void *GetMid(); // TODO  返回值需要重新定义
    void *GetSender(); // TODO  返回值需要重新定义
    void *GetReceiver(); // TODO  返回值需要重新定义
    void *GetDirection(); // TODO  返回值需要重新定义
    void SetDirection(); // TODO  参数需要重新定义
    void *GetCurrentDirection(); // TODO  参数需要重新定义
    void Stop(); 
    void *SetCodecPreferences(); // TODO  参数需要重新定义
    
private:
    std::shared_ptr<PeerConnectionFactoryWrapper> factory_;
    rtc::scoped_refptr<PeerConnectionInterface> pc_;
    rtc::scoped_refptr<RtpTransceiverInterface> rtpTransceiver_;
};

}
#endif //WEBRTC4CJ_FFI_RTP_TRANSCEIVER_H
