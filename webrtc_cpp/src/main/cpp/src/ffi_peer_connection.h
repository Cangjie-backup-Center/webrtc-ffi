//
// Created on 2025/8/7.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef WEBRTC4CJ_FFI_PEER_CONNECTION_H
#define WEBRTC4CJ_FFI_PEER_CONNECTION_H

#include "api/peer_connection_interface.h"
#include "ffi_define_struct.h"
#include <cstdint>


namespace webrtc {
class PeerConnectionFactoryWrapper;

bool CangjieToNativeConfiguration(
    const CJ_RTCConfiguration& jsConfiguration, webrtc::PeerConnectionInterface::RTCConfiguration& configuration);

bool CangjieToNativeIceServer(CJ_RTCIceServer cjrs, webrtc::PeerConnectionInterface::IceServer& iceServer); // TODO

rtc::RTCCertificate* CangjieToNativeCertificate(CJ_RTCCertificate cjrc); // TODO




class ffiPeerConnection : public PeerConnectionObserver {
    
    /*
  readonly canTrickleIceCandidates?: boolean;
  readonly signalingState: RTCSignalingState;
  readonly iceGatheringState: RTCIceGatheringState;
  readonly iceConnectionState: RTCIceConnectionState;
  readonly connectionState: RTCPeerConnectionState;
  readonly localDescription?: RTCSessionDescription;
  readonly remoteDescription?: RTCSessionDescription;
  readonly currentLocalDescription?: RTCSessionDescription;
  readonly currentRemoteDescription?: RTCSessionDescription;
  readonly pendingLocalDescription?: RTCSessionDescription;
  readonly pendingRemoteDescription?: RTCSessionDescription;
  readonly sctp?: RTCSctpTransport;

  onnegotiationneeded: ((this: RTCPeerConnection, ev: Event) => any) | null;
  onicecandidate: ((this: RTCPeerConnection, ev: RTCPeerConnectionIceEvent) => any) | null;
  onicecandidateerror: ((this: RTCPeerConnection, ev: RTCPeerConnectionIceErrorEvent) => any) | null;
  oniceconnectionstatechange: ((this: RTCPeerConnection, ev: Event) => any) | null;
  onicegatheringstatechange: ((this: RTCPeerConnection, ev: Event) => any) | null;
  onsignalingstatechange: ((this: RTCPeerConnection, ev: Event) => any) | null;
  onconnectionstatechange: ((this: RTCPeerConnection, ev: Event) => any) | null;
  ontrack: ((this: RTCPeerConnection, ev: RTCTrackEvent) => any) | null;
  ondatachannel: ((this: RTCPeerConnection, ev: RTCDataChannelEvent) => any) | null;

  addTrack(track: MediaStreamTrack, ...streams: MediaStream[]): RTCRtpSender;
  removeTrack(sender: RTCRtpSender): void;
  setLocalDescription(description?: RTCSessionDescriptionInit): Promise<void>;
  setRemoteDescription(description: RTCSessionDescriptionInit): Promise<void>;
  createOffer(options?: RTCOfferOptions): Promise<RTCSessionDescriptionInit>;
  createAnswer(options?: RTCAnswerOptions): Promise<RTCSessionDescriptionInit>;
  createDataChannel(label: string, dataChannelDict?: RTCDataChannelInit): RTCDataChannel;
  addIceCandidate(candidate?: RTCIceCandidateInit): Promise<void>;
  getSenders(): RTCRtpSender[];
  getReceivers(): RTCRtpReceiver[];
  getTransceivers(): RTCRtpTransceiver[];
  getConfiguration(): RTCConfiguration;
  restartIce(): void;
  setConfiguration(configuration?: RTCConfiguration): void;
  addTransceiver(trackOrKind: MediaStreamTrack | string, init?: RTCRtpTransceiverInit): RTCRtpTransceiver;
  close(): void;
  getStats(selector?: MediaStreamTrack): Promise<RTCStatsReport>;
  setAudioRecording(recording: boolean): void;
  setAudioPlayout(playout: boolean): void;
    */
    
    
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
    
    ffiPeerConnection(CJ_RTCConfiguration config, rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> factory);
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
    void SetOnTrack(void (*pe)(int64_t that, int64_t localVideoTrack)) ;
private:
    rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> factory_;
    rtc::scoped_refptr<PeerConnectionInterface> pc_;
    cj_RTCSctpTransport* sctpTransportRef_ = nullptr;
    void (*cj_func_call_back1_)(int64_t that, int64_t localVideoTrack);
    void (*cj_func_call_back2_)(int64_t that, int64_t localVideoTrack);
    void (*cj_func_call_back3_)(int64_t that, int64_t localVideoTrack);
    void (*cj_func_call_back4_)(int64_t that, int64_t localVideoTrack);

public:
    static int64_t GenerateCertificate(std::string keyname);
    static rtc::scoped_refptr<rtc::RTCCertificate> certificate_;
    static std::unique_ptr<rtc::RTCCertificateGenerator> certificateGenerator;

};

}

#endif //WEBRTC4CJ_FFI_PEER_CONNECTION_H
