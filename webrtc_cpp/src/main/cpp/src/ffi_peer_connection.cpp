//
// Created on 2025/8/7.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".


#include "ffi_peer_connection.h"
#include "ffi_data_channel.h"
#include "ffi_exception.h"
#include "peer_connection_factory.h"
#include <cstdint>
#include <string>
#include "rtc_base/rtc_certificate_generator.h"

const char kEnumIceTransportPolicyAll[] = "all";
const char kEnumIceTransportPolicyRelay[] = "relay";
const char kEnumBundlePolicyBalanced[] = "balanced";
const char kEnumBundlePolicyMaxBundle[] = "max-bundle";
const char kEnumBundlePolicyMaxCompact[] = "max-compat";
const char kEnumRtcpMuxPolicyRequire[] = "require";

namespace webrtc{
rtc::scoped_refptr<rtc::RTCCertificate> ffiPeerConnection::certificate_ = rtc::scoped_refptr<rtc::RTCCertificate>();

bool CangjieToNativeIceServer(CJ_RTCIceServer cjrs, webrtc::PeerConnectionInterface::IceServer& iceServer){
    if (cjrs.urls_size) {
        // for (int64_t i = 0; i < cjrs.urls_size; i++) {
            // std::string tmp(cjrs.urls);
            // iceServer.urls.push_back(tmp);
        // }
    } else {
        RTC_LOG(LS_WARNING) << "urls is not string nor array";
    }
    if (cjrs.username_size) {
        std::string username(cjrs.username, cjrs.username_size);
        iceServer.username = username;
    } else {
        RTC_LOG(LS_WARNING) << "username is not string";
    }
    if (cjrs.credential_size) {
        std::string password(cjrs.credential, cjrs.credential_size);
        iceServer.password = password;
    } else {
        RTC_LOG(LS_WARNING) << "credential is not string";
    }
    return true;
}

bool CangjieToNativeConfiguration(
    const CJ_RTCConfiguration& cjConfiguration, PeerConnectionInterface::RTCConfiguration& configuration){
    RTC_LOG(LS_VERBOSE) << __FUNCTION__;
    if (cjConfiguration.iceServers_size) {
        for (int64_t i = 0; i < cjConfiguration.iceServers_size; i++) {
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
//            rtc::RTCCertificate* certificate = CangjieToNativeCertificate(cjrc);  // TODO 
//            configuration.certificates.push_back(rtc::scoped_refptr<rtc::RTCCertificate>(certificate));
        }
    }
    
    if (cjConfiguration.iceCandidatePoolSize) {
        configuration.ice_candidate_pool_size = cjConfiguration.iceCandidatePoolSize;
    }
    return true;
}

ffiPeerConnection::ffiPeerConnection(CJ_RTCConfiguration config, std::shared_ptr<PeerConnectionFactoryWrapper> factory)  {
    if(factory) {
        factory_ = factory;
    } else {
        CANGJIE_THROW("---");
    }
    PeerConnectionDependencies deps(this);
    
    PeerConnectionInterface::RTCConfiguration configuration;
    CangjieToNativeConfiguration(config, configuration);
    auto result = factory_->GetFactory()->CreatePeerConnectionOrError(configuration, std::move(deps));
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
    ffiPeerConnection::certificate_ = rtc::RTCCertificateGenerator::GenerateCertificate(key_params, absl::nullopt);
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
    cj_RTCSessionDescription* desc = new cj_RTCSessionDescription();  // TODO free
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
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__;

    if (!candidate) {
        RTC_LOG(LS_ERROR) << "The candidate is nullptr";
        return;
    }

    std::string sdp;
    if (!candidate->ToString(&sdp)) {
        RTC_LOG(LS_ERROR) << "Failed to convert candidate to string, got so far: " << sdp;
        return;
    }

    auto sdpMid = candidate->sdp_mid();
    auto sdpMLineIndex = candidate->sdp_mline_index();
    auto can = candidate->candidate();
    
//    Dispatch(
//        CallbackEvent<ffiPeerConnection>::Create([this, sdp, sdpMid, sdpMLineIndex, can](ffiPeerConnection& target) {
//            RTC_DCHECK_EQ(this, &target);
//
//            auto env = target.Env();
//            Napi::HandleScope scope(env);
//            auto jsEvent = Object::New(env);
//            jsEvent.Set("type", String::New(env, kEventIceCandidate));
//            jsEvent.Set("candidate", NativeToJsCandidate(env, sdpMid, sdpMLineIndex, sdp, can));
//            target.MakeCallback(kEventIceCandidate, {jsEvent});
//        })); // TODO 
}
void ffiPeerConnection::SetOnIceCandidateError(void (*pe)(int64_t id, CJ_RTCPeerConnectionIceErrorEvent ptr)){
    this->cj_func_call_OnIceCandidateError_= pe;
}
void ffiPeerConnection::OnIceCandidateError(
    const std::string& address, int port, const std::string& url, int errorCode,
    const std::string& errorText) {
        RTC_DLOG(LS_VERBOSE) << __FUNCTION__;

    Dispatch(CallbackEvent<ffiPeerConnection>::Create(
        [this, address, port, url, errorCode, errorText](ffiPeerConnection& target) {
            RTC_DCHECK_EQ(this, &target);

            if (this->cj_func_call_OnIceCandidateError_) {
                this->cj_func_call_OnIceCandidateError_(this->cj_class_key, CJ_RTCPeerConnectionIceErrorEvent{
                    type : "icecandidateerror",
                    address : address.data(),
                    port : port,
                    url : url.data(),
                    errorCode : errorCode,
                    errorText : errorText.data()
                });
            }
        }));
}
void ffiPeerConnection::OnIceCandidatesRemoved(const std::vector<cricket::Candidate>& candidates) {
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
}

void ffiPeerConnection::SetOnSignalingChange(void (*pe)(int64_t id, CJ_Event ptr)) {
    this->cj_func_call_OnSignalingChange_ = pe;
}
void ffiPeerConnection::OnSignalingChange(PeerConnectionInterface::SignalingState newState) {
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__ << " newState=" << newState;

    Dispatch(CallbackEvent<ffiPeerConnection>::Create([this, newState](ffiPeerConnection& target) {
        RTC_DCHECK_EQ(this, &target);
        if (this->cj_func_call_OnSignalingChange_) {
            this->cj_func_call_OnSignalingChange_(this->cj_class_key, CJ_Event{type: "signalingstatechange"});
        }
        if (newState == webrtc::PeerConnectionInterface::kClosed) {
            Stop();
        }
    }));
}

void ffiPeerConnection::OnIceConnectionChange(PeerConnectionInterface::IceConnectionState newState) {
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__ << " newState=" << newState;
}

void ffiPeerConnection::SetOnStandardizedIceConnectionChange(void (*pe)(int64_t id, CJ_Event ptr)) {
    cj_func_call_OnStandardizedIceConnectionChange_ = pe;
}
void ffiPeerConnection::OnStandardizedIceConnectionChange(PeerConnectionInterface::IceConnectionState newState) {
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__ << " newState=" << newState;
    Dispatch(CallbackEvent<ffiPeerConnection>::Create([this, newState](ffiPeerConnection& target) {
        RTC_DCHECK_EQ(this, &target);
        if(cj_func_call_OnStandardizedIceConnectionChange_) {
            cj_func_call_OnStandardizedIceConnectionChange_(this->cj_class_key, CJ_Event{type: "iceconnectionstatechange"});
        }
    }));
}
void ffiPeerConnection::SetOnConnectionChange(void (*pe)(int64_t id, CJ_Event ptr)) {
    cj_func_call_OnConnectionChange_ = pe;
}
void ffiPeerConnection::OnConnectionChange(PeerConnectionInterface::PeerConnectionState newState) {
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__ << " newState=" << newState;
    Dispatch(CallbackEvent<ffiPeerConnection>::Create([this, newState](ffiPeerConnection& target) {
        RTC_DCHECK_EQ(this, &target);
        if(cj_func_call_OnConnectionChange_) {
            cj_func_call_OnConnectionChange_(this->cj_class_key, CJ_Event{type: "connectionstatechange"});
        }
    }));
}
void ffiPeerConnection::OnIceConnectionReceivingChange(bool receiving) {
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
}
void ffiPeerConnection::SetOnIceGatheringChange(void (*pe)(int64_t id, CJ_Event ptr)) {
    cj_func_call_OnIceGatheringChange_ = pe;
}
void ffiPeerConnection::OnIceGatheringChange(PeerConnectionInterface::IceGatheringState newState) {
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__ << " newState=" << newState;
    Dispatch(CallbackEvent<ffiPeerConnection>::Create([this, newState](ffiPeerConnection& target) {
        RTC_DCHECK_EQ(this, &target);
        if(cj_func_call_OnIceGatheringChange_) {
            cj_func_call_OnIceGatheringChange_(this->cj_class_key, CJ_Event{type: "icegatheringstatechange"});
        }
    }));
}

void ffiPeerConnection::OnIceSelectedCandidatePairChanged(const cricket::CandidatePairChangeEvent& event) {
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
}
void ffiPeerConnection::OnAddStream(rtc::scoped_refptr<MediaStreamInterface> stream) {
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
}
void ffiPeerConnection::OnRemoveStream(rtc::scoped_refptr<MediaStreamInterface> stream) {
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
}

void ffiPeerConnection::SetOnDataChannel(void (*pe)(int64_t that, int64_t ptr)) {
    this->cj_func_call_OnDataChannel_ = pe;
}

void ffiPeerConnection::OnDataChannel(rtc::scoped_refptr<DataChannelInterface> channel) { // TODO
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
    if (!channel) {
        RTC_LOG(LS_ERROR) << "The channel is nullptr";
        return;
    }
    auto observer = std::make_unique<ffiDataChannelObserverTemp>(channel);
    Dispatch(CallbackEvent<ffiPeerConnection>::Create(
        [this, obs = observer.release()]
        (ffiPeerConnection& target)
        {
            RTC_DCHECK_EQ(this, &target);
            if (this->cj_func_call_OnDataChannel_) {
                CJ_RTCDataChannelEvent* crdce = new CJ_RTCDataChannelEvent();
                crdce->channel = (int64_t)obs;
                this->cj_func_call_OnDataChannel_(this->cj_class_key, (int64_t)crdce);
                delete crdce;
            }
        }
    ));
}

void ffiPeerConnection::SetOnRenegotiationNeeded(void (*pe)(int64_t id, CJ_Event ptr)) {
    cj_func_call_OnRenegotiationNeeded_ = pe;
}
void ffiPeerConnection::OnRenegotiationNeeded() {
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
    Dispatch(CallbackEvent<ffiPeerConnection>::Create(
        [this]
        (ffiPeerConnection& target)
        {
            RTC_DCHECK_EQ(this, &target);
            if (this->cj_func_call_OnRenegotiationNeeded_) {
                this->cj_func_call_OnRenegotiationNeeded_(this->cj_class_key, CJ_Event{type: "negotiationneeded"});
            }
        }
    ));
}

void ffiPeerConnection::OnNegotiationNeededEvent(uint32_t eventId) {
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__ << " eventId=" << eventId;
}

void ffiPeerConnection::OnAddTrack(
    rtc::scoped_refptr<RtpReceiverInterface> receiver,
    const std::vector<rtc::scoped_refptr<MediaStreamInterface>>& streams) {
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
    // use OnTrack
}


void ffiPeerConnection::SetOnTrack(void (*pe)(int64_t that, CJ_RTCTrackEvent localVideoTrack)){
    cj_func_call_OnTrack_ = pe;
}

void ffiPeerConnection::OnTrack(rtc::scoped_refptr<RtpTransceiverInterface> transceiver) {
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
    Dispatch(CallbackEvent<ffiPeerConnection>::Create(
        [this, transceiver]
        (ffiPeerConnection& target)
        {
            auto receiver = transceiver->receiver();
            if (!receiver) {
                RTC_LOG(LS_ERROR) << "No receiver in the transceiver";
                return;
            }
            auto streams = receiver->streams();

            if (this->cj_func_call_OnTrack_){
                int64_t* result = new int64_t[streams.size()];
                for (uint32_t i = 0; i < streams.size(); i++) {
                    result[i] = (int64_t)streams[i].get();
                }
                this->cj_func_call_OnTrack_(this->cj_class_key, CJ_RTCTrackEvent{
                    type : "track",
                    streams : result,
                    streams_size : (int64_t)streams.size(),
                    MediaStreamTrack_ptr : (int64_t)new ffiMediaStreamTrack(this->factory_, receiver->track()),
                    RtpReceiver_ptr : (int64_t)ffiRtpReceiver::NewInstance(this->factory_, this->pc_, receiver),
                    RtpTransceiver_ptr : (int64_t)ffiRtpTransceiver::NewInstance(this->factory_, this->pc_, transceiver)
                });  // see SetOnTrack function.
            }
        }
    ));
}

void ffiPeerConnection::OnRemoveTrack(rtc::scoped_refptr<RtpReceiverInterface> receiver) {
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
}

}







