//
// Created on 2025/8/7.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef WEBRTC4CJ_FFI_PEER_CONNECTION_H
#define WEBRTC4CJ_FFI_PEER_CONNECTION_H

#include "api/peer_connection_interface.h"
#include "ffi_define_struct.h"
#include "event/ffi_event_target.h"
#include "ffi_media_stream_track.h"
#include "ffi_rtp_receiver.h"
#include "ffi_rtp_transceiver.h"
#include <cstdint>


namespace webrtc {
class PeerConnectionFactoryWrapper;

bool CangjieToNativeConfiguration(
    const CJ_RTCConfiguration& jsConfiguration, webrtc::PeerConnectionInterface::RTCConfiguration& configuration);

bool CangjieToNativeIceServer(CJ_RTCIceServer cjrs, webrtc::PeerConnectionInterface::IceServer& iceServer); // TODO

rtc::RTCCertificate* CangjieToNativeCertificate(CJ_RTCCertificate cjrc); // TODO


class ffiPeerConnection : public FFIEventTarget<ffiPeerConnection>, public PeerConnectionObserver {
    
public:
    
    ~ffiPeerConnection() {
    }
// readonly
    bool GetCanTrickleIceCandidates();
    FFIRTCSignalingState GetSignalingState();
    FFIRTCIceGatheringState GetIceGatheringState();
    FFIRTCIceConnectionState GetIceConnectionState();
    FFIRTCPeerConnectionState GetConnectionState();
    cj_RTCSessionDescription GetLocalDescription();
    cj_RTCSessionDescription GetRemoteDescription();
    cj_RTCSessionDescription GetCurrentLocalDescription();
    cj_RTCSessionDescription GetCurrentRemoteDescription();
    cj_RTCSessionDescription GetPendingLocalDescription();
    cj_RTCSessionDescription GetPendingRemoteDescription();
    cj_RTCSctpTransport GetSctp(); // TODO
// readonly end
    
    ffiPeerConnection(CJ_RTCConfiguration config, std::shared_ptr<PeerConnectionFactoryWrapper> factory);
protected:
    void OnIceCandidate(const IceCandidateInterface* candidate) override;
    void OnIceCandidateError(
        const std::string& address, int port, const std::string& url, int errorCode,
        const std::string& errorText) override;
    void OnIceCandidatesRemoved(const std::vector<cricket::Candidate>& candidates) override;
    void OnSignalingChange(PeerConnectionInterface::SignalingState newState) override;
    void OnIceConnectionChange(PeerConnectionInterface::IceConnectionState newState) override;
    void OnStandardizedIceConnectionChange(PeerConnectionInterface::IceConnectionState newState) override;
    void OnConnectionChange(PeerConnectionInterface::PeerConnectionState newState) override;
    void OnIceConnectionReceivingChange(bool receiving) override;
    void OnIceGatheringChange(PeerConnectionInterface::IceGatheringState newState) override;
    void OnIceSelectedCandidatePairChanged(const cricket::CandidatePairChangeEvent& event) override;
    void OnAddStream(rtc::scoped_refptr<MediaStreamInterface> stream) override;
    void OnRemoveStream(rtc::scoped_refptr<MediaStreamInterface> stream) override;
    void OnDataChannel(rtc::scoped_refptr<DataChannelInterface> channel) override;
    void OnRenegotiationNeeded() override;
    void OnNegotiationNeededEvent(uint32_t eventId) override;
    void OnAddTrack(
        rtc::scoped_refptr<RtpReceiverInterface> receiver,
        const std::vector<rtc::scoped_refptr<MediaStreamInterface>>& streams) override;
    void OnTrack(rtc::scoped_refptr<RtpTransceiverInterface> transceiver) override;
    void OnRemoveTrack(rtc::scoped_refptr<RtpReceiverInterface> receiver) override;
public:
    void SetOnTrack(void (*pe)(int64_t id, CJ_RTCTrackEvent ptr)) ;
    void SetOnDataChannel(void (*pe)(int64_t id, int64_t ptr)) ;
    void SetOnSignalingChange(void (*pe)(int64_t id, CJ_Event ptr)) ;
    void SetOnRenegotiationNeeded(void (*pe)(int64_t id, CJ_Event ptr)) ;
    void SetOnIceCandidateError(void (*pe)(int64_t id, CJ_RTCPeerConnectionIceErrorEvent ptr));
    void SetOnStandardizedIceConnectionChange(void (*pe)(int64_t id, CJ_Event ptr));
    void SetOnConnectionChange(void (*pe)(int64_t id, CJ_Event ptr));
    void SetOnIceGatheringChange(void (*pe)(int64_t id, CJ_Event ptr));
    int64_t cj_class_key = 0;

private:
    std::shared_ptr<PeerConnectionFactoryWrapper> factory_;
    rtc::scoped_refptr<PeerConnectionInterface> pc_;
    
    cj_RTCSctpTransport* sctpTransportRef_ = nullptr;

    void (*cj_func_call_OnIceCandidateError_)(int64_t id, CJ_RTCPeerConnectionIceErrorEvent ptr) = nullptr;
    void (*cj_func_call_OnTrack_)(int64_t id, CJ_RTCTrackEvent ptr) = nullptr;
    void (*cj_func_call_OnSignalingChange_)(int64_t id, CJ_Event ptr) = nullptr;
    void (*cj_func_call_OnDataChannel_)(int64_t id, int64_t ptr) = nullptr;
    void (*cj_func_call_OnRenegotiationNeeded_)(int64_t id, CJ_Event ptr) = nullptr;
    void (*cj_func_call_OnStandardizedIceConnectionChange_)(int64_t id, CJ_Event ptr) = nullptr;
    void (*cj_func_call_OnConnectionChange_)(int64_t id, CJ_Event ptr) = nullptr;
    void (*cj_func_call_OnIceGatheringChange_)(int64_t id, CJ_Event ptr) = nullptr;

public:
    static int64_t GenerateCertificate(std::string keyname);
    static rtc::scoped_refptr<rtc::RTCCertificate> certificate_;
};

}

#endif //WEBRTC4CJ_FFI_PEER_CONNECTION_H
