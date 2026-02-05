#ifndef WEBRTC4CJ_FFI_PEER_CONNECTION_H
#define WEBRTC4CJ_FFI_PEER_CONNECTION_H

#include "api/peer_connection_interface.h"
#include "ffi_define_struct.h"
#include "event/ffi_event_target.h"
#include "ffi_media_stream_track.h"
#include "ffi_rtp_receiver.h"
#include "ffi_rtp_transceiver.h"
#include "ffi_sctp_transport.h"
#include "api/jsep.h"
#include "webrtc_func.h"
#include <cstdint>

namespace webrtc {

bool CangjieToNativeConfiguration(
    const CJ_RTCConfiguration& jsConfiguration, webrtc::PeerConnectionInterface::RTCConfiguration& configuration);

bool CangjieToNativeIceServer(CJ_RTCIceServer cjrs, webrtc::PeerConnectionInterface::IceServer& iceServer);

rtc::RTCCertificate* CangjieToNativeCertificate(CJ_RTCCertificate cjrc);

class ffiPeerConnection : public FFIEventTarget<ffiPeerConnection>, public PeerConnectionObserver,
    public CJ_CLASS_BASE::ffiCjClass {
public:
    
    ~ffiPeerConnection()
    {
    }
// readonly
    bool GetCanTrickleIceCandidates();
    FFIRTCSignalingState GetSignalingState();
    FFIRTCIceGatheringState GetIceGatheringState();
    FFIRTCIceConnectionState GetIceConnectionState();
    FFIRTCPeerConnectionState GetConnectionState();
    CJ_RTCSessionDescription GetLocalDescription();
    CJ_RTCSessionDescription GetRemoteDescription();
    CJ_RTCSessionDescription GetCurrentLocalDescription();
    CJ_RTCSessionDescription GetCurrentRemoteDescription();
    CJ_RTCSessionDescription GetPendingLocalDescription();
    CJ_RTCSessionDescription GetPendingRemoteDescription();
    int64_t GetSctp();
// readonly end
    
    void CreateOffer(bool iceRestart);
    
    ffiPeerConnection(CJ_RTCConfiguration config, std::shared_ptr<PeerConnectionFactoryWrapper> factory);
    void (*cj_func_call_CreateOffer_)(int64_t id,
        bool isSuccess, CJ_RTCSessionDescription ptr, const char* msg) = nullptr;
    void (*cj_func_call_CreateAnswer_)(int64_t id,
        bool isSuccess, CJ_RTCSessionDescription ptr, const char* msg) = nullptr;

    int64_t addTrack(ffiMediaStreamTrack* track, std::vector<webrtc::FFIMediaStream*> streamVec);

    void setLocalDescription(CJ_RTCSessionDescription description, void (*pe)(int64_t cj_id, CJ_ErrorMessage msg));
    void setRemoteDescription(CJ_RTCSessionDescription description, void (*pe)(int64_t cj_id, CJ_ErrorMessage msg));
    CJ_FFICreateSdpObserver_result createOffer(bool iceRestart);
    CJ_FFICreateSdpObserver_result createAnswer();
    int64_t createDataChannel(CHAR_PTR label, CJ_RTCDataChannelInit dataChannelDict);
    void addIceCandidate(CJ_RTCIceCandidateInit candidate);
    int64_t* getSenders();
    int64_t* getReceivers();
    int64_t* getTransceivers();
    void restartIce();
    void setConfiguration(CJ_RTCConfiguration cjConfig);
    void close();
    void setAudioRecording(bool recording);
    void setAudioPlayout(bool playout);
    void deleteCJ_RTCTrackEvent();

    static int64_t GenerateCertificate(std::string keyname);
    static rtc::scoped_refptr<rtc::RTCCertificate> certificate_;

    void SetOnTrack(void (*pe)(int64_t id, CJ_RTCTrackEvent ptr)) ;
    void SetOnDataChannel(void (*pe)(int64_t id, int64_t ptr)) ;
    void SetOnSignalingChange(void (*pe)(int64_t id, CJ_Event ptr)) ;
    void SetOnRenegotiationNeeded(void (*pe)(int64_t id, CJ_Event ptr)) ;
    void SetOnIceCandidateError(void (*pe)(int64_t id, CJ_RTCPeerConnectionIceErrorEvent ptr));
    void SetOnStandardizedIceConnectionChange(void (*pe)(int64_t id, CJ_Event ptr));
    void SetOnConnectionChange(void (*pe)(int64_t id, CJ_Event ptr));
    void SetOnIceGatheringChange(void (*pe)(int64_t id, CJ_Event ptr));
    void SetOnIceCandidate(void (*pe)(int64_t id, CJ_RTCPeerConnectionIceEvent ptr));
    void SetCallBackCreateOffer(void (*pe)(int64_t id, bool isSuccess, CJ_RTCSessionDescription ptr, const char* msg));
    void SetCallBackCreateAnswer(void (*pe)(int64_t id, bool isSuccess, CJ_RTCSessionDescription ptr, const char* msg));
    void SetAddIceCandidate(void (*pe)(int64_t id, const char* msg));
    void (*cj_func_call_addIceCandidate)(int64_t id, const char* msg) = nullptr;

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

private:
    std::shared_ptr<PeerConnectionFactoryWrapper> factory_;
    rtc::scoped_refptr<PeerConnectionInterface> pc_;
//    ffiRtpSender* sender_ = nullptr;
//    ffiSctpTransport* sctpTransportRef_ = nullptr;
    void (*cj_func_call_OnIceCandidateError_)(int64_t id, CJ_RTCPeerConnectionIceErrorEvent ptr) = nullptr;
    void (*cj_func_call_OnTrack_)(int64_t id, CJ_RTCTrackEvent ptr) = nullptr;
    void (*cj_func_call_OnSignalingChange_)(int64_t id, CJ_Event ptr) = nullptr;
    void (*cj_func_call_OnDataChannel_)(int64_t id, int64_t ptr) = nullptr;
    void (*cj_func_call_OnRenegotiationNeeded_)(int64_t id, CJ_Event ptr) = nullptr;
    void (*cj_func_call_OnStandardizedIceConnectionChange_)(int64_t id, CJ_Event ptr) = nullptr;
    void (*cj_func_call_OnConnectionChange_)(int64_t id, CJ_Event ptr) = nullptr;
    void (*cj_func_call_OnIceGatheringChange_)(int64_t id, CJ_Event ptr) = nullptr;
    void (*cj_func_call_OnIceCandidate_)(int64_t id, CJ_RTCPeerConnectionIceEvent ptr) = nullptr;
};

}

#endif // WEBRTC4CJ_FFI_PEER_CONNECTION_H
