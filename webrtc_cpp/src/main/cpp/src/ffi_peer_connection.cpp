//
// Created on 2025/8/7.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".


#include "ffi_peer_connection.h"
#include "ffi_exception.h"
#include "peer_connection_factory.h"
#include <cstdint>
#include "rtc_base/rtc_certificate_generator.h"

const char kEnumIceTransportPolicyAll[] = "all";
const char kEnumIceTransportPolicyRelay[] = "relay";
const char kEnumBundlePolicyBalanced[] = "balanced";
const char kEnumBundlePolicyMaxBundle[] = "max-bundle";
const char kEnumBundlePolicyMaxCompact[] = "max-compat";
const char kEnumRtcpMuxPolicyRequire[] = "require";

using namespace webrtc;

bool CangjieToNativeIceServer(CJ_RTCIceServer cjrs, webrtc::PeerConnectionInterface::IceServer& iceServer){
    if (cjrs.urls_size) {
        for (int64_t i = 0; i < cjrs.urls_size; i++) {
            iceServer.urls.emplace_back(cjrs.urls[i]);
        }
    } else {
        RTC_LOG(LS_WARNING) << "urls is not string nor array";
    }
//    if (cjrs.username_size) {
//        std::string username(cjrs.username, cjrs.username_size);
//        iceServer.username = username;
//    } else {
//        RTC_LOG(LS_WARNING) << "username is not string";
//    }
//    if (cjrs.credential_size) {
//        std::string password(cjrs.credential, cjrs.credential_size);
//        iceServer.password = password;
//    } else {
//        RTC_LOG(LS_WARNING) << "credential is not string";
//    }
    return true;
}

bool CangjieToNativeConfiguration(
    const CJ_RTCConfiguration& cjConfiguration, PeerConnectionInterface::RTCConfiguration& configuration){
    RTC_LOG(LS_VERBOSE) << __FUNCTION__;
    if (cjConfiguration.iceServers_size) {
        for (int64_t i = 0; i<cjConfiguration.iceServers_size; i++) {
            CJ_RTCIceServer cjrs = cjConfiguration.iceServers[i];
            PeerConnectionInterface::IceServer iceServer;
            CangjieToNativeIceServer(cjrs, iceServer);
            configuration.servers.push_back(iceServer);
        }
    }
    
    if (cjConfiguration.iceTransportPolicy_size) {
        if(strncmp(cjConfiguration.iceTransportPolicy, kEnumIceTransportPolicyAll, cjConfiguration.iceTransportPolicy_size) == 0) {
            configuration.bundle_policy = PeerConnectionInterface::kBundlePolicyBalanced;
        } else if (strncmp(cjConfiguration.iceTransportPolicy, kEnumIceTransportPolicyRelay, cjConfiguration.iceTransportPolicy_size) == 0) {
            configuration.bundle_policy = PeerConnectionInterface::kBundlePolicyBalanced;
        } else{
            RTC_LOG(LS_WARNING) << "Invalid iceTransportPolicy";
        }
    }
    
    if (cjConfiguration.bundlePolicy_size) {
        if(strncmp(cjConfiguration.bundlePolicy, kEnumBundlePolicyBalanced, cjConfiguration.bundlePolicy_size) == 0) {
            configuration.bundle_policy = PeerConnectionInterface::kBundlePolicyBalanced;
        } else if (strncmp(cjConfiguration.bundlePolicy, kEnumBundlePolicyMaxCompact, cjConfiguration.bundlePolicy_size) == 0) {
            configuration.bundle_policy = PeerConnectionInterface::kBundlePolicyMaxCompat;
        } else if (strncmp(cjConfiguration.bundlePolicy, kEnumBundlePolicyMaxBundle, cjConfiguration.bundlePolicy_size) == 0) {
            configuration.bundle_policy = PeerConnectionInterface::kBundlePolicyMaxBundle;
        } else{
            RTC_LOG(LS_WARNING) << "Invalid iceTransportPolicy";
        }
    }
    
    if (cjConfiguration.rtcpMuxPolicy_size) {
        if(strncmp(cjConfiguration.rtcpMuxPolicy, kEnumRtcpMuxPolicyRequire, cjConfiguration.rtcpMuxPolicy_size) == 0) {
            configuration.rtcp_mux_policy = PeerConnectionInterface::kRtcpMuxPolicyRequire;
        } else {
            RTC_LOG(LS_WARNING) << "Invalid rtcpMuxPolicy";
        }
    }
    
    if (cjConfiguration.certificates_size) {
        for (int64_t i = 0; i<cjConfiguration.certificates_size; i++) {
            CJ_RTCCertificate cjrc = cjConfiguration.certificates[i];
            rtc::RTCCertificate* certificate = CangjieToNativeCertificate(cjrc);  // TODO 
            configuration.certificates.push_back(rtc::scoped_refptr<rtc::RTCCertificate>(certificate));
        }
    }
    
    if (cjConfiguration.iceCandidatePoolSize) {
        configuration.ice_candidate_pool_size = cjConfiguration.iceCandidatePoolSize;
    }
    return true;
}

ffiPeerConnection::ffiPeerConnection(CJ_RTCConfiguration config, rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> factory)  {
    if(factory) {
        factory_ = factory;
    } else {
        CANGJIE_THROW("---");
    }
    PeerConnectionDependencies deps(this);
    
    PeerConnectionInterface::RTCConfiguration configuration;
    CangjieToNativeConfiguration(config, configuration);
    auto result = factory_->CreatePeerConnectionOrError(configuration, std::move(deps));
    if (!result.ok()) {
        RTC_LOG(LS_ERROR) << "Failed to create PeerConnection: " << result.error().message();
        CANGJIE_THROW(result.error().message());
    }

    pc_ = result.MoveValue();
}


int64_t ffiPeerConnection::GenerateCertificate(std::string keyParamsName) {
    rtc::KeyParams key_params;
    if (keyParamsName == "RSA" || keyParamsName == "rsa") {
        key_params = rtc::KeyParams::RSA();
    } else if (keyParamsName == "ECDSA" || keyParamsName == "ecdsa") {
        key_params = rtc::KeyParams::ECDSA();
    } else {
        RTC_DLOG(LS_ERROR) << "Unsupported key algorithm";
    }
    if (ffiPeerConnection::certificate_.get()) {
        free(ffiPeerConnection::certificate_.release());
    }
    ffiPeerConnection::certificate_ = certificateGenerator->GenerateCertificate(key_params, absl::nullopt);
    return (int64_t) &certificate_;  // TODO 
}

bool ffiPeerConnection::GetCanTrickleIceCandidates() {
    if (pc_->can_trickle_ice_candidates()) {
        return pc_->can_trickle_ice_candidates().value();
    }
    return false; // TODO Undefined
}

FFIRTCSignalingState ffiPeerConnection::GetSignalingState(){
    switch (pc_->signaling_state()) {
        case PeerConnectionInterface::kStable:
            return FFIRTCSignalingState::STABLE;
        case PeerConnectionInterface::kHaveLocalOffer:
            return FFIRTCSignalingState::HAVE_LOCAL_OFFER;
        case PeerConnectionInterface::kHaveLocalPrAnswer:
            return FFIRTCSignalingState::HAVE_LOCAL_PRANSWER;
        case PeerConnectionInterface::kHaveRemoteOffer:
            return FFIRTCSignalingState::HAVE_REMOTE_OFFER;
        case PeerConnectionInterface::kHaveRemotePrAnswer:
            return FFIRTCSignalingState::HAVE_REMOTE_PRANSWER;
        case PeerConnectionInterface::kClosed:
            return FFIRTCSignalingState::CLOSED;
        default:
            RTC_LOG(LS_WARNING) << "Invalid value of signalingState";
            break;
    }
    CANGJIE_THROW("Invalid value");
}
FFIRTCIceGatheringState ffiPeerConnection::GetIceGatheringState(){
    switch (pc_->ice_gathering_state()) {
        case PeerConnectionInterface::kIceGatheringNew:
            return FFIRTCIceGatheringState::NEW;
        case PeerConnectionInterface::kIceGatheringGathering:
            return FFIRTCIceGatheringState::GATHERING;
        case PeerConnectionInterface::kIceGatheringComplete:
            return FFIRTCIceGatheringState::COMPLETE;
        default:
            RTC_LOG(LS_WARNING) << "Invalid value of iceGatheringState";
            break;
    }
    CANGJIE_THROW("Invalid value");
}
FFIRTCIceConnectionState ffiPeerConnection::GetIceConnectionState(){
    switch (pc_->ice_connection_state()) {
        case PeerConnectionInterface::kIceConnectionNew:
            return FFIRTCIceConnectionState::NEW;
        case PeerConnectionInterface::kIceConnectionChecking:
            return FFIRTCIceConnectionState::CHECKING;
        case PeerConnectionInterface::kIceConnectionConnected:
            return FFIRTCIceConnectionState::CONNECTED;
        case PeerConnectionInterface::kIceConnectionCompleted:
            return FFIRTCIceConnectionState::COMPLETED;
        case PeerConnectionInterface::kIceConnectionFailed:
            return FFIRTCIceConnectionState::FAILED;
        case PeerConnectionInterface::kIceConnectionDisconnected:
            return FFIRTCIceConnectionState::DISCONNECTED;
        case PeerConnectionInterface::kIceConnectionClosed:
            return FFIRTCIceConnectionState::CLOSED;
        default:
            RTC_LOG(LS_WARNING) << "Invalid value of iceConnectionState";
            break;
    }
    CANGJIE_THROW("Invalid value");
}
FFIRTCPeerConnectionState ffiPeerConnection::GetConnectionState(){
    switch (pc_->peer_connection_state()) {
        case PeerConnectionInterface::PeerConnectionState::kNew:
            return FFIRTCPeerConnectionState::NEW;
        case PeerConnectionInterface::PeerConnectionState::kConnecting:
            return FFIRTCPeerConnectionState::CONNECTED;
        case PeerConnectionInterface::PeerConnectionState::kConnected:
            return FFIRTCPeerConnectionState::CONNECTED;
        case PeerConnectionInterface::PeerConnectionState::kDisconnected:
            return FFIRTCPeerConnectionState::DISCONNECTED;
        case PeerConnectionInterface::PeerConnectionState::kFailed:
            return FFIRTCPeerConnectionState::FAILED;
        case PeerConnectionInterface::PeerConnectionState::kClosed:
            return FFIRTCPeerConnectionState::FAILED;
        default:
            RTC_LOG(LS_WARNING) << "Invalid value of connectionState";
            break;
    }
    CANGJIE_THROW("Invalid value");
}
cj_RTCSessionDescription ffiPeerConnection::GetLocalDescription(){
    // It's only safe to operate on SessionDescriptionInterface on the signaling thread
    std::string sdp;
    std::string type;
    pc_->signaling_thread()->BlockingCall([pc = pc_, &sdp, &type] {
        const SessionDescriptionInterface* desc = pc->local_description();
        if (desc) {
            if (desc->ToString(&sdp)) {
                type = desc->type();
            }
        }
    });
    cj_RTCSessionDescription* desc = new cj_RTCSessionDescription();
    if (sdp.empty()) {
        return *desc;
    }
    if (type.empty()) {
        CANGJIE_THROW("Invalid value");
    }
    desc->sdp = strdup(sdp.c_str());
    desc->sdp_size = sdp.size();
    desc->RTCSdpType = strdup(type.c_str());
    desc->RTCSdpType_size = type.size();
    desc->undefined = false;
    return *desc;
}

cj_RTCSessionDescription ffiPeerConnection::GetRemoteDescription(){
     // It's only safe to operate on SessionDescriptionInterface on the signaling thread
    std::string sdp;
    std::string type;
    pc_->signaling_thread()->BlockingCall([pc = pc_, &sdp, &type] {
        const SessionDescriptionInterface* desc = pc->remote_description();
        if (desc) {
            if (desc->ToString(&sdp)) {
                type = desc->type();
            }
        }
    });
    cj_RTCSessionDescription* desc = new cj_RTCSessionDescription();
    if (sdp.empty()) {
        return *desc;
    }
    desc->sdp = strdup(sdp.c_str());
    desc->sdp_size = sdp.size();
    desc->RTCSdpType = strdup(type.c_str());
    desc->RTCSdpType_size = type.size();
    desc->undefined = false;
    return *desc;
}
cj_RTCSessionDescription ffiPeerConnection::GetCurrentLocalDescription(){
     // It's only safe to operate on SessionDescriptionInterface on the signaling thread
    std::string sdp;
    std::string type;
    pc_->signaling_thread()->BlockingCall([pc = pc_, &sdp, &type] {
        const SessionDescriptionInterface* desc = pc->current_local_description();
        if (desc) {
            if (desc->ToString(&sdp)) {
                type = desc->type();
            }
        }
    });

    cj_RTCSessionDescription* desc = new cj_RTCSessionDescription();
    if (sdp.empty()) {
        return *desc;
    }
    desc->sdp = strdup(sdp.c_str());
    desc->sdp_size = sdp.size();
    desc->RTCSdpType = strdup(type.c_str());
    desc->RTCSdpType_size = type.size();
    desc->undefined = false;
    return *desc;
}
cj_RTCSessionDescription ffiPeerConnection::GetCurrentRemoteDescription(){
    // It's only safe to operate on SessionDescriptionInterface on the signaling thread
    std::string sdp;
    std::string type;
    pc_->signaling_thread()->BlockingCall([pc = pc_, &sdp, &type] {
        const SessionDescriptionInterface* desc = pc->current_remote_description();
        if (desc) {
            if (desc->ToString(&sdp)) {
                type = desc->type();
            }
        }
    });
    cj_RTCSessionDescription* desc = new cj_RTCSessionDescription();
    if (sdp.empty()) {
        return *desc;
    }
    desc->sdp = strdup(sdp.c_str());
    desc->sdp_size = sdp.size();
    desc->RTCSdpType = strdup(type.c_str());
    desc->RTCSdpType_size = type.size();
    desc->undefined = false;
    return *desc;
}
cj_RTCSessionDescription ffiPeerConnection::GetPendingLocalDescription(){
    // It's only safe to operate on SessionDescriptionInterface on the signaling thread
    std::string sdp;
    std::string type;
    pc_->signaling_thread()->BlockingCall([pc = pc_, &sdp, &type] {
        const SessionDescriptionInterface* desc = pc->pending_local_description();
        if (desc) {
            if (desc->ToString(&sdp)) {
                type = desc->type();
            }
        }
    });
    cj_RTCSessionDescription* desc = new cj_RTCSessionDescription();
    if (sdp.empty()) {
        return *desc;
    }
    desc->sdp = strdup(sdp.c_str());
    desc->sdp_size = sdp.size();
    desc->RTCSdpType = strdup(type.c_str());
    desc->RTCSdpType_size = type.size();
    desc->undefined = false;
    return *desc;
}
cj_RTCSessionDescription ffiPeerConnection::GetPendingRemoteDescription(){
    // It's only safe to operate on SessionDescriptionInterface on the signaling thread
    std::string sdp;
    std::string type;
    pc_->signaling_thread()->BlockingCall([pc = pc_, &sdp, &type] {
        const SessionDescriptionInterface* desc = pc->pending_remote_description();
        if (desc) {
            if (desc->ToString(&sdp)) {
                type = desc->type();
            }
        }
    });
    cj_RTCSessionDescription* desc = new cj_RTCSessionDescription();
    if (sdp.empty()) {
        return *desc;
    }
    desc->sdp = strdup(sdp.c_str());
    desc->sdp_size = sdp.size();
    desc->RTCSdpType = strdup(type.c_str());
    desc->RTCSdpType_size = type.size();
    desc->undefined = false;
    return *desc;
}

void ffiPeerConnection::OnIceCandidate(const IceCandidateInterface* candidate) {
//    call_back_cangjie_func();
}
void ffiPeerConnection::OnIceCandidateError(
    const std::string& address, int port, const std::string& url, int errorCode,
    const std::string& errorText) {}
void ffiPeerConnection::OnIceCandidatesRemoved(const std::vector<cricket::Candidate>& candidates) {}
void ffiPeerConnection::OnSignalingChange(PeerConnectionInterface::SignalingState newState) {}
void ffiPeerConnection::OnIceConnectionChange(PeerConnectionInterface::IceConnectionState newState) {}
void ffiPeerConnection::OnStandardizedIceConnectionChange(PeerConnectionInterface::IceConnectionState newState) {}
void ffiPeerConnection::OnConnectionChange(PeerConnectionInterface::PeerConnectionState newState) {}
void ffiPeerConnection::OnIceConnectionReceivingChange(bool receiving) {}
void ffiPeerConnection::OnIceGatheringChange(PeerConnectionInterface::IceGatheringState newState) {}
void ffiPeerConnection::OnIceSelectedCandidatePairChanged(const cricket::CandidatePairChangeEvent& event) {
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
}
void ffiPeerConnection::OnAddStream(rtc::scoped_refptr<MediaStreamInterface> stream) {
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
}
void ffiPeerConnection::OnRemoveStream(rtc::scoped_refptr<MediaStreamInterface> stream) {
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
}
void ffiPeerConnection::OnDataChannel(rtc::scoped_refptr<DataChannelInterface> channel) {
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
    if (!channel) {
        RTC_LOG(LS_ERROR) << "The channel is nullptr";
        return;
    }
    
}
void ffiPeerConnection::OnRenegotiationNeeded() {}
void ffiPeerConnection::OnNegotiationNeededEvent(uint32_t eventId) {}
void ffiPeerConnection::OnAddTrack(
    rtc::scoped_refptr<RtpReceiverInterface> receiver,
    const std::vector<rtc::scoped_refptr<MediaStreamInterface>>& streams) {}

void ffiPeerConnection::OnTrack(rtc::scoped_refptr<RtpTransceiverInterface> transceiver) {
    cj_func_call_back1_(1,2); // TODO 1,2
}

void ffiPeerConnection::SetOnTrack(void (*pe)(int64_t that, int64_t localVideoTrack)){
    cj_func_call_back1_ = pe;
}

void ffiPeerConnection::OnRemoveTrack(rtc::scoped_refptr<RtpReceiverInterface> receiver) {}



/*
typedef struct {
    int64_t maxChannels;
    int64_t maxMessageSize;
    char* RTCSctpTransportState;
    int64_t RTCSctpTransportState_size;
    int64_t RTCDtlsTransport_ptr; // rtc::scoped_refptr<SctpTransportInterface>
    bool undefined = true;  // 如果 true , 其他值就无效了
} cj_RTCSctpTransport;
*/

//cj_RTCSctpTransport ffiPeerConnection::GetSctp(){
//    if (!sctpTransportRef_) {
//        return *sctpTransportRef_;
//    }
//    cj_RTCSctpTransport* transport_ = new cj_RTCSctpTransport();
//    rtc::scoped_refptr<SctpTransportInterface> transport = pc_->GetSctpTransport();
//    if (!transport) {
//        return *transport_;
//    }
//    
//}








