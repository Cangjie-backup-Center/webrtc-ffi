/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#include "ffi_peer_connection.h"
#include "ffi_data_channel.h"
#include "ffi_exception.h"
#include "peer_connection_factory.h"
#include <cstdint>
#include <string>
#include "rtc_base/rtc_certificate_generator.h"
#include "ffi_ice_candidate.h"
#include "webrtc_func.h"

const char kEnumIceTransportPolicyAll[] = "all";
const char kEnumIceTransportPolicyRelay[] = "relay";
const char kEnumBundlePolicyBalanced[] = "balanced";
const char kEnumBundlePolicyMaxBundle[] = "max-bundle";
const char kEnumBundlePolicyMaxCompact[] = "max-compat";
const char kEnumRtcpMuxPolicyRequire[] = "require";

namespace webrtc {

class FFISetLocalSdpObserver : public SetLocalDescriptionObserverInterface {
public:
    ffiPeerConnection* fpc_ = nullptr;
    void (*cj_func_callback_)(int64_t id, CJ_ErrorMessage msg) = nullptr;
    FFISetLocalSdpObserver(ffiPeerConnection* pc, void (*pe)(int64_t id, CJ_ErrorMessage msg))
    {
        fpc_ = pc;
        cj_func_callback_ = pe;
    }

protected:
    void OnSetLocalDescriptionComplete(RTCError error) override
    {
        RTC_DLOG(LS_INFO) << __FUNCTION__;
        if (!error.ok()) {
            RTC_LOG(LS_ERROR) << "Error: " << error.type() << ", " << error.message();
        }

        cj_func_callback_(this->fpc_->GetCJClassID(),
            CJ_ErrorMessage{rtcErrorDetailType: (int64_t)error.error_detail(), msg: error.message()});
    }
};

class FFISetRemoteSdpObserver : public SetRemoteDescriptionObserverInterface {
public:
    ffiPeerConnection* pc_ = nullptr;
    void (*cj_func_callback_)(int64_t id, CJ_ErrorMessage msg) = nullptr;
    FFISetRemoteSdpObserver(ffiPeerConnection* pc, void (*pe)(int64_t id, CJ_ErrorMessage msg))
    {
        pc_ = pc;
        cj_func_callback_ = pe;
    }

protected:
    void OnSetRemoteDescriptionComplete(RTCError error) override
    {
        RTC_DLOG(LS_INFO) << __FUNCTION__;
        if (!error.ok()) {
            RTC_LOG(LS_ERROR) << "Error: " << error.type() << ", " << error.message();
        }
        
        auto workerThread_ = std::thread([this, error]() {
            cj_func_callback_(this->pc_->GetCJClassID(),
            CJ_ErrorMessage{rtcErrorDetailType: (int64_t)error.error_detail(), msg: error.message()});
        });
        workerThread_.join();
    }
};

class FFICreateSdpObserver : public CreateSessionDescriptionObserver {
public:
    CJ_FFICreateSdpObserver_result ret;
    std::mutex mtx;
    std::condition_variable cv;

    FFICreateSdpObserver()
    {
        ret = CJ_FFICreateSdpObserver_result{};
    }

protected:
    void OnSuccess(SessionDescriptionInterface* desc) override
    {
        UNUSED std::unique_lock<std::mutex> lock(mtx);
        RTC_LOG(LS_INFO) << "CreateSessionDescription success: " << desc;

        std::string sdp;
        desc->ToString(&sdp);
        RTC_DLOG(LS_VERBOSE) << "sdp: " << sdp;
        std::string sdptype = webrtc::SdpTypeToString(desc->GetType());

        this->ret.isFail = false;
        this->ret.sdp = new char[sdp.size()+1];
        this->ret.RTCSdpType = new char[sdptype.size()+1];
        webrtc_scp(this->ret.sdp, sdp.size()+1, sdp.data(), sdp.size());
        webrtc_scp(this->ret.RTCSdpType, sdptype.size()+1, sdptype.data(), sdptype.size());
        // delete desc;
        cv.notify_one();
    }

    void OnFailure(RTCError error) override
    {
        UNUSED std::unique_lock<std::mutex> lock(mtx);
        RTC_LOG(LS_ERROR) << "CreateSessionDescription failed";
        this->ret.isFail = true;
        std::string str = error.message();
        this->ret.msg = new char[str.size()+1];
        webrtc_scp(this->ret.msg, str.size()+1, str.data(), str.size());
        cv.notify_one();
    }
};

rtc::scoped_refptr<rtc::RTCCertificate> ffiPeerConnection::certificate_ = rtc::scoped_refptr<rtc::RTCCertificate>();

bool CangjieToNativeIceServer(CJ_RTCIceServer cjrs, webrtc::PeerConnectionInterface::IceServer& iceServer)
{
    if (cjrs.urls_size) {
         for (int64_t i = 0; i < cjrs.urls_size; i++) {
             std::string tmp(cjrs.urls[i]);
             iceServer.urls.push_back(tmp);
         }
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
        std::string p(cjrs.credential, cjrs.credential_size);
        iceServer.password = p;
    } else {
        RTC_LOG(LS_WARNING) << "credential is not string";
    }
    return true;
}

bool CangjieToNativeConfiguration(
    const CJ_RTCConfiguration& cjConfiguration, PeerConnectionInterface::RTCConfiguration& configuration)
{
    RTC_LOG(LS_VERBOSE) << __FUNCTION__;
    if (cjConfiguration.iceServers_size) {
        for (int64_t i = 0; i < cjConfiguration.iceServers_size; i++) {
            CJ_RTCIceServer cjrs = cjConfiguration.iceServers[i];
            PeerConnectionInterface::IceServer iceServer;
            CangjieToNativeIceServer(cjrs, iceServer);
            configuration.servers.push_back(iceServer);
        }
    }
    
    switch (static_cast<FFIRTCIceTransportPolicy>(cjConfiguration.iceTransportPolicy)) {
        case FFIRTCIceTransportPolicy::ALL:
            configuration.type = PeerConnectionInterface::kAll;
            break;
        case FFIRTCIceTransportPolicy::RELAY:
            configuration.type = PeerConnectionInterface::kRelay;
            break;
        default:
            RTC_LOG(LS_WARNING) << "Invalid iceTransportPolicy";
    }
    
    switch (static_cast<FFIRTCBundlePolicy>(cjConfiguration.bundlePolicy)) {
        case FFIRTCBundlePolicy::BALANCED:
            configuration.bundle_policy = PeerConnectionInterface::kBundlePolicyBalanced;
            break;
        case FFIRTCBundlePolicy::MAX_COMPAT:
            configuration.bundle_policy = PeerConnectionInterface::kBundlePolicyMaxCompat;
            break;
        case FFIRTCBundlePolicy::MAX_BUNDLE:
            configuration.bundle_policy = PeerConnectionInterface::kBundlePolicyMaxBundle;
            break;
        default:
            RTC_LOG(LS_WARNING) << "Invalid bundlePolicy";
    }
    
    switch (static_cast<FFIRTCRtcpMuxPolicy>(cjConfiguration.rtcpMuxPolicy)) {
        case FFIRTCRtcpMuxPolicy::REQUIRE:
            configuration.rtcp_mux_policy = PeerConnectionInterface::kRtcpMuxPolicyRequire;
            break;
        default:
            RTC_LOG(LS_WARNING) << "Invalid rtcpMuxPolicy";
    }
    
    if (cjConfiguration.certificates_size) {
        for (int64_t i = 0; i<cjConfiguration.certificates_size; i++) {
            CJ_RTCCertificate cjrc = cjConfiguration.certificates[i];
        }
    }
    
    if (cjConfiguration.iceCandidatePoolSize) {
        configuration.ice_candidate_pool_size = cjConfiguration.iceCandidatePoolSize;
    }
    return true;
}

ffiPeerConnection::ffiPeerConnection(CJ_RTCConfiguration config,
    std::shared_ptr<PeerConnectionFactoryWrapper> factory)
{
    if (factory.get()) {
        factory_ = factory;
    } else {
        factory_ = PeerConnectionFactoryWrapper::GetDefault();
    }
    PeerConnectionDependencies deps(this);
    
    PeerConnectionInterface::RTCConfiguration configuration;
    CangjieToNativeConfiguration(config, configuration);
    configuration.sdp_semantics = SdpSemantics::kUnifiedPlan;

    auto result = factory_->GetFactory()->CreatePeerConnectionOrError(configuration, std::move(deps));
    if (!result.ok()) {
        RTC_LOG(LS_ERROR) << "Failed to create PeerConnection: " << result.error().message();
        CANGJIE_THROW(result.error().message());
    }

    pc_ = result.MoveValue();
}


int64_t ffiPeerConnection::GenerateCertificate(std::string keyParamsName)
{
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
    return reinterpret_cast<int64_t>(&certificate_);  // 问题点1
}

bool ffiPeerConnection::GetCanTrickleIceCandidates()
{
    if (pc_->can_trickle_ice_candidates()) {
        return pc_->can_trickle_ice_candidates().value();
    }
    return false;
}

FFIRTCSignalingState ffiPeerConnection::GetSignalingState()
{
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

FFIRTCIceGatheringState ffiPeerConnection::GetIceGatheringState()
{
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

FFIRTCIceConnectionState ffiPeerConnection::GetIceConnectionState()
{
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

FFIRTCPeerConnectionState ffiPeerConnection::GetConnectionState()
{
    switch (pc_->peer_connection_state()) {
        case PeerConnectionInterface::PeerConnectionState::kNew:
            return FFIRTCPeerConnectionState::NEW;
        case PeerConnectionInterface::PeerConnectionState::kConnecting:
            return FFIRTCPeerConnectionState::CONNECTING;
        case PeerConnectionInterface::PeerConnectionState::kConnected:
            return FFIRTCPeerConnectionState::CONNECTED;
        case PeerConnectionInterface::PeerConnectionState::kDisconnected:
            return FFIRTCPeerConnectionState::DISCONNECTED;
        case PeerConnectionInterface::PeerConnectionState::kFailed:
            return FFIRTCPeerConnectionState::FAILED;
        case PeerConnectionInterface::PeerConnectionState::kClosed:
            return FFIRTCPeerConnectionState::CLOSED;
        default:
            RTC_LOG(LS_WARNING) << "Invalid value of connectionState";
            break;
    }
    CANGJIE_THROW("Invalid value");
}

CJ_RTCSessionDescription ffiPeerConnection::GetLocalDescription()
{
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
    CJ_RTCSessionDescription* desc = new CJ_RTCSessionDescription();
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

CJ_RTCSessionDescription ffiPeerConnection::GetRemoteDescription()
{
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
    CJ_RTCSessionDescription* desc = new CJ_RTCSessionDescription();
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

CJ_RTCSessionDescription ffiPeerConnection::GetCurrentLocalDescription()
{
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

    CJ_RTCSessionDescription* desc = new CJ_RTCSessionDescription();
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

CJ_RTCSessionDescription ffiPeerConnection::GetCurrentRemoteDescription()
{
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
    CJ_RTCSessionDescription* desc = new CJ_RTCSessionDescription();
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

CJ_RTCSessionDescription ffiPeerConnection::GetPendingLocalDescription()
{
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
    CJ_RTCSessionDescription* desc = new CJ_RTCSessionDescription();
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

CJ_RTCSessionDescription ffiPeerConnection::GetPendingRemoteDescription()
{
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
    CJ_RTCSessionDescription* desc = new CJ_RTCSessionDescription();
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

int64_t ffiPeerConnection::GetSctp()
{
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__;

    if (!sctpTransportRef_) {
        return (int64_t)sctpTransportRef_;
    }

    auto transport = pc_->GetSctpTransport();
    if (!transport) {
        return 0;
    }

    auto sctpTransport = ffiSctpTransport::NewInstance(factory_, transport);
    sctpTransportRef_ = sctpTransport;

    return reinterpret_cast<int64_t>(sctpTransport);
}

void ffiPeerConnection::SetOnIceCandidate(void (*pe)(int64_t id, CJ_RTCPeerConnectionIceEvent ptr))
{
    this->cj_func_call_OnIceCandidate_ = pe;
}

void ffiPeerConnection::SetCallBackCreateOffer(
    void (*pe)(int64_t id, bool isSuccess, CJ_RTCSessionDescription ptr, const char* msg))
{
    cj_func_call_CreateOffer_ = pe;
}

void ffiPeerConnection::SetCallBackCreateAnswer(
    void (*pe)(int64_t id, bool isSuccess, CJ_RTCSessionDescription ptr, const char* msg))
{
    cj_func_call_CreateAnswer_ = pe;
}

void ffiPeerConnection::OnIceCandidate(const IceCandidateInterface* candidate)
{
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
    
    Dispatch(
        CallbackEvent<ffiPeerConnection>::Create([this, sdp, sdpMid, sdpMLineIndex, can](ffiPeerConnection& target) {
            RTC_DCHECK_EQ(this, &target);
            if (cj_func_call_OnIceCandidate_) {
                this->cj_func_call_OnIceCandidate_(
                    this->cj_class_key, CJ_RTCPeerConnectionIceEvent{
                        type : "icecandidate",
                        candidate: CJToRTCPeerConnectionIceEvent(sdpMid, sdpMLineIndex, sdp, can)
                });
            }
        })
    );
}

void ffiPeerConnection::SetOnIceCandidateError(void (*pe)(int64_t id, CJ_RTCPeerConnectionIceErrorEvent ptr))
{
    this->cj_func_call_OnIceCandidateError_= pe;
}

void ffiPeerConnection::OnIceCandidateError(
    const std::string& address, int port, const std::string& url, int errorCode,
    const std::string& errorText)
{
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

void ffiPeerConnection::OnIceCandidatesRemoved(const std::vector<cricket::Candidate>& candidates)
{
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
}

void ffiPeerConnection::SetOnSignalingChange(void (*pe)(int64_t id, CJ_Event ptr))
{
    this->cj_func_call_OnSignalingChange_ = pe;
}

void ffiPeerConnection::OnSignalingChange(PeerConnectionInterface::SignalingState newState)
{
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

void ffiPeerConnection::OnIceConnectionChange(PeerConnectionInterface::IceConnectionState newState)
{
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__ << " newState=" << newState;
}

void ffiPeerConnection::SetOnStandardizedIceConnectionChange(void (*pe)(int64_t id, CJ_Event ptr))
{
    cj_func_call_OnStandardizedIceConnectionChange_ = pe;
}

void ffiPeerConnection::OnStandardizedIceConnectionChange(
    PeerConnectionInterface::IceConnectionState newState)
{
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__ << " newState=" << newState;
    Dispatch(CallbackEvent<ffiPeerConnection>::Create([this, newState](ffiPeerConnection& target) {
        RTC_DCHECK_EQ(this, &target);
        if (cj_func_call_OnStandardizedIceConnectionChange_) {
            cj_func_call_OnStandardizedIceConnectionChange_(
                this->cj_class_key, CJ_Event{type: "iceconnectionstatechange"});
        }
    }));
}

void ffiPeerConnection::SetOnConnectionChange(void (*pe)(int64_t id, CJ_Event ptr))
{
    cj_func_call_OnConnectionChange_ = pe;
}

void ffiPeerConnection::OnConnectionChange(PeerConnectionInterface::PeerConnectionState newState)
{
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__ << " newState=" << newState;
    Dispatch(CallbackEvent<ffiPeerConnection>::Create([this, newState](ffiPeerConnection& target) {
        RTC_DCHECK_EQ(this, &target);
        if (cj_func_call_OnConnectionChange_) {
            cj_func_call_OnConnectionChange_(this->cj_class_key,
                                             CJ_Event {
                                                type: "connectionstatechange"
                                             });
        }
    }));
}

void ffiPeerConnection::OnIceConnectionReceivingChange(bool receiving)
{
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
}

void ffiPeerConnection::SetOnIceGatheringChange(void (*pe)(int64_t id, CJ_Event ptr))
{
    cj_func_call_OnIceGatheringChange_ = pe;
}

void ffiPeerConnection::OnIceGatheringChange(PeerConnectionInterface::IceGatheringState newState)
{
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__ << " newState=" << newState;
    Dispatch(CallbackEvent<ffiPeerConnection>::Create([this, newState](ffiPeerConnection& target) {
        RTC_DCHECK_EQ(this, &target);
        if (cj_func_call_OnIceGatheringChange_) {
            cj_func_call_OnIceGatheringChange_(this->cj_class_key, CJ_Event{type: "icegatheringstatechange"});
        }
    }));
}

void ffiPeerConnection::OnIceSelectedCandidatePairChanged(const cricket::CandidatePairChangeEvent& event)
{
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
}

void ffiPeerConnection::OnAddStream(rtc::scoped_refptr<MediaStreamInterface> stream)
{
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
}

void ffiPeerConnection::OnRemoveStream(rtc::scoped_refptr<MediaStreamInterface> stream)
{
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
}

void ffiPeerConnection::SetOnDataChannel(void (*pe)(int64_t that, int64_t ptr))
{
    this->cj_func_call_OnDataChannel_ = pe;
}

void ffiPeerConnection::OnDataChannel(rtc::scoped_refptr<DataChannelInterface> channel)
{
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
    if (!channel) {
        RTC_LOG(LS_ERROR) << "The channel is nullptr";
        return;
    }
    auto observer = std::make_unique<ffiDataChannelObserverTemp>(channel);
    Dispatch(CallbackEvent<ffiPeerConnection>::Create(
        [this, obs = observer.release()]
        (ffiPeerConnection& target) {
            RTC_DCHECK_EQ(this, &target);
            if (this->cj_func_call_OnDataChannel_) {
                CJ_RTCDataChannelEvent* crdce = new CJ_RTCDataChannelEvent();
                crdce->channel = (int64_t)obs;
                this->cj_func_call_OnDataChannel_(this->cj_class_key, (int64_t)crdce);
            }
        }
    ));
}

void ffiPeerConnection::SetOnRenegotiationNeeded(void (*pe)(int64_t id, CJ_Event ptr))
{
    cj_func_call_OnRenegotiationNeeded_ = pe;
}

void ffiPeerConnection::OnRenegotiationNeeded()
{
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
    Dispatch(CallbackEvent<ffiPeerConnection>::Create(
        [this]
        (ffiPeerConnection& target) {
            RTC_DCHECK_EQ(this, &target);
            if (this->cj_func_call_OnRenegotiationNeeded_) {
                this->cj_func_call_OnRenegotiationNeeded_(this->cj_class_key, CJ_Event{type: "negotiationneeded"});
            }
        }
    ));
}

void ffiPeerConnection::OnNegotiationNeededEvent(uint32_t eventId)
{
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__ << " eventId=" << eventId;
}

void ffiPeerConnection::OnAddTrack(
    rtc::scoped_refptr<RtpReceiverInterface> receiver,
    const std::vector<rtc::scoped_refptr<MediaStreamInterface>>& streams)
{
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
    // use OnTrack
}


void ffiPeerConnection::SetOnTrack(void (*pe)(int64_t that, CJ_RTCTrackEvent localVideoTrack))
{
    cj_func_call_OnTrack_ = pe;
}

char* copyStringToChar(const std::string str)
{
    if (str.empty()) {
        CANGJIE_THROW("str is empty");
        return nullptr;
    }
    CHAR_PTR copy = new char[str.size() + 1];
    webrtc_scp(copy, str.size()+1, str.c_str(), str.size()+1);
    return copy;
}

void ffiPeerConnection::OnTrack(rtc::scoped_refptr<RtpTransceiverInterface> transceiver)
{
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
    Dispatch(CallbackEvent<ffiPeerConnection>::Create(
        [this, transceiver]
        (ffiPeerConnection& target) {
            auto receiver = transceiver->receiver();
            if (!receiver) {
                RTC_LOG(LS_ERROR) << "No receiver in the transceiver";
                return;
            }
            auto streams = receiver->streams();

            if (this->cj_func_call_OnTrack_) {
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

void ffiPeerConnection::OnRemoveTrack(rtc::scoped_refptr<RtpReceiverInterface> receiver)
{
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
}

int64_t ffiPeerConnection::addTrack(ffiMediaStreamTrack* track, std::vector<webrtc::FFIMediaStream*> streamVec)
{
    RTC_LOG(LS_INFO) << __FUNCTION__;

    std::vector<std::string> streamIds;
    if (streamVec.size() > 0) {
        for (uint32_t i = 0; i < streamVec.size(); i++) {
            auto stream = streamVec[i]->Get();
            if (stream) {
                streamIds.push_back(stream->id());
            }
        }
    } else {
        streamIds.push_back("stream_id");
    }

    auto peerconnection_track = track->Get();
    auto result = pc_->AddTrack(peerconnection_track, streamIds);
    if (!result.ok()) {
        CANGJIE_THROW(std::string("AddTrack error ") + result.error().message());
    }

    if (peerconnection_track && peerconnection_track->kind() == MediaStreamTrackInterface::kAudioKind) {
        auto source = factory_->GetAudioSource(peerconnection_track);
        auto adm = factory_->GetAudioDeviceModule();
        if (source && adm) {
            adm->AddAudioInput(source->GetAudioInput());
        }
    }

    sender_ = ffiRtpSender::NewInstance(this->factory_, this->pc_, result.value());
    return reinterpret_cast<int64_t>(sender_);
}

// void ffiPeerConnection::removeTrack(ffiRtpReceiver* receiver) {
//     RTC_LOG(LS_INFO) << __FUNCTION__;
// }

void ffiPeerConnection::setLocalDescription(
    CJ_RTCSessionDescription description,
    void (*pe)(int64_t cj_id, CJ_ErrorMessage msg))
{
    RTC_LOG(LS_INFO) << __FUNCTION__;
    std::unique_ptr<SessionDescriptionInterface> desc;
    
    if (!description.undefined) {
        std::string sdp = "";
        sdp = description.sdp;
        std::string type = description.RTCSdpType;
        auto sdpType = SdpTypeFromString(type);

        SdpParseError error;
        desc = CreateSessionDescription(*sdpType, sdp, &error);
        if (!desc) {
            CANGJIE_THROW("CreateSessionDescription error");
        }
    }

    auto observer = rtc::make_ref_counted<FFISetLocalSdpObserver>(this, pe);
    if (desc) {
        pc_->SetLocalDescription(std::move(desc), observer);
    } else {
        pc_->SetLocalDescription(observer);
    }
    return ;
}

void ffiPeerConnection::setRemoteDescription(
    CJ_RTCSessionDescription description,
    void (*pe)(int64_t cj_id, CJ_ErrorMessage msg))
{
    RTC_LOG(LS_INFO) << __FUNCTION__;
    std::string sdp = "";
    sdp = description.sdp;
    std::string type = description.RTCSdpType;
    auto sdpType = SdpTypeFromString(type);
    std::unique_ptr<SessionDescriptionInterface> desc;

    SdpParseError error;

    desc = CreateSessionDescription(*sdpType, sdp, &error);
    if (!desc) {
        CANGJIE_THROW("CreateSessionDescription error");
    }

    auto observer = rtc::make_ref_counted<FFISetRemoteSdpObserver>(this, pe);

    pc_->SetRemoteDescription(std::move(desc), observer);
}

CJ_FFICreateSdpObserver_result ffiPeerConnection::createOffer(bool iceRestart)
{
    PeerConnectionInterface::RTCOfferAnswerOptions options;
    options.ice_restart = iceRestart;
    auto observer = rtc::make_ref_counted<FFICreateSdpObserver>();
    auto obs = observer.get();
    std::unique_lock<std::mutex> lock(obs->mtx);
    pc_->CreateOffer(observer.get(), options);
    obs->cv.wait(lock);
    return observer.get()->ret;
}

CJ_FFICreateSdpObserver_result ffiPeerConnection::createAnswer()
{
    RTC_LOG(LS_INFO) << __FUNCTION__;
    auto observer = rtc::make_ref_counted<FFICreateSdpObserver>();
    auto obs = observer.get();
    std::unique_lock<std::mutex> lock(obs->mtx);
    PeerConnectionInterface::RTCOfferAnswerOptions options;
    pc_->CreateAnswer(observer.get(), options);
    obs->cv.wait(lock);
    return observer.get()->ret;
}

int64_t ffiPeerConnection::createDataChannel(CHAR_PTR label, CJ_RTCDataChannelInit dataChannelDict)
{
    RTC_LOG(LS_INFO) << __FUNCTION__;
    std::string label_ = label;

    if (label_.empty()) {
        CANGJIE_THROW("label is empty");
    }
    
    if (!dataChannelDict.isBuild) {
        auto result = pc_->CreateDataChannelOrError(label_, nullptr);
        if (!result.ok()) {
            auto& error = result.error();
            CANGJIE_THROW("CreateDataChannel error");
        }
        ffiDataChannelObserverTemp* observerPtr = new ffiDataChannelObserverTemp(result.value());
        return reinterpret_cast<int64_t>(observerPtr);
    }
    
    DataChannelInit options;
    auto result = pc_->CreateDataChannelOrError(label_, &options);
    if (!result.ok()) {
        auto& error = result.error();
        CANGJIE_THROW("CreateDataChannelOrError error");
    }

    ffiDataChannelObserverTemp* observerPtr = new ffiDataChannelObserverTemp(result.value());
    return (int64_t)observerPtr;
}

void ffiPeerConnection::SetAddIceCandidate(void (*pe)(int64_t id, const char* msg))
{
    this->cj_func_call_addIceCandidate = pe;
}


void ffiPeerConnection::addIceCandidate(CJ_RTCIceCandidateInit iceCandidate)
{
    RTC_LOG(LS_INFO) << __FUNCTION__;
    std::string sdp;
    std::string sdpMid;
    int sdpMLineIndex = 0;

    if (iceCandidate.isBuild) {
        sdp = iceCandidate.candidate;
        if (strcmp(iceCandidate.sdpMid, "")) {
            sdpMid = iceCandidate.sdpMid;
        }

        if (iceCandidate.sdpMLineIndex != 0) {
            sdpMLineIndex = iceCandidate.sdpMLineIndex;
        }
    }

    delete [] iceCandidate.candidate;
    delete [] iceCandidate.sdpMid;
    delete [] iceCandidate.usernameFragment;

    SdpParseError error;
    auto candidate = CreateIceCandidate(sdpMid, sdpMLineIndex, sdp, &error);
    if (!candidate) {
        CANGJIE_THROW("CreateIceCandidate error");
        return;
    }

    pc_->AddIceCandidate(std::unique_ptr<IceCandidateInterface>(candidate), [this](RTCError error) {
        RTC_DLOG(LS_INFO) << "AddIceCandidate complete: " << error.ok();
        auto type = error.type();
        auto message = error.message();
        if (this->cj_func_call_addIceCandidate)
            this->cj_func_call_addIceCandidate(this->cj_class_key, message);
    });
}


int64_t* ffiPeerConnection::getSenders()
{
    RTC_LOG(LS_VERBOSE) << __FUNCTION__;

    auto senders = pc_->GetSenders();
    int64_t* retSenders = new int64_t[senders.size()];
    for (uint32_t i = 0; i < senders.size(); i++) {
        auto ffiSenderPtr = ffiRtpSender::NewInstance(factory_, pc_, senders[i]);
        retSenders[i] = reinterpret_cast<int64_t>(ffiSenderPtr);
    }
    return retSenders;
}

int64_t* ffiPeerConnection::getReceivers()
{
    RTC_LOG(LS_VERBOSE) << __FUNCTION__;
    auto receivers = pc_->GetReceivers();
    int64_t* retReceivers = new int64_t[receivers.size()];
    for (uint32_t i = 0; i < receivers.size(); i++) {
        auto ffiReceiverPtr = ffiRtpReceiver::NewInstance(factory_, pc_, receivers[i]);
        retReceivers[i] = reinterpret_cast<int64_t>(ffiReceiverPtr);
    }
    return retReceivers;
}

int64_t* ffiPeerConnection::getTransceivers()
{
    RTC_LOG(LS_VERBOSE) << __FUNCTION__;
    auto transceivers = pc_->GetTransceivers();

    int64_t* retTransceivers = new int64_t[transceivers.size()];
    for (uint32_t i = 0; i < transceivers.size(); i++) {
        auto ffiTransceiverPtr = ffiRtpTransceiver::NewInstance(factory_, pc_, transceivers[i]);
        retTransceivers[i] = reinterpret_cast<int64_t>(ffiTransceiverPtr);
    }
    return retTransceivers;
}

void ffiPeerConnection::restartIce()
{
    RTC_LOG(LS_VERBOSE) << __FUNCTION__;
    pc_->RestartIce();
    return ;
}

void ffiPeerConnection::setConfiguration(CJ_RTCConfiguration cjConfig)
{
    RTC_LOG(LS_VERBOSE) << __FUNCTION__;
    PeerConnectionInterface::RTCConfiguration config;
    if (!CangjieToNativeConfiguration(cjConfig, config)) {
        LOGI("CangjieToNativeConfiguration error");
    }

    auto error = pc_->SetConfiguration(config);
    if (!error.ok()) {
        std::string message;
        switch (error.type()) {
            case RTCErrorType::INVALID_STATE:
                message = "Invalid state";
                break;
            case RTCErrorType::INVALID_MODIFICATION:
                message = "Invalid modification";
                break;
            case RTCErrorType::INVALID_RANGE:
                message = "Invalid range";
                break;
            case RTCErrorType::SYNTAX_ERROR:
                message = "Syntax error";
                break;
            case RTCErrorType::INVALID_PARAMETER:
                message = "Invalid argument";
                break;
            case RTCErrorType::INTERNAL_ERROR:
                message = "Internal error";
                break;
            default:
                message = "Unknown error";
                break;
        }
        CANGJIE_THROW("SetConfiguration error: " + message);
    }
}

// ffiRtpTransceiver* ffiPeerConnection::addTransceiver(const char* kind, const char* mid) {
//     RTC_LOG(LS_VERBOSE) << __FUNCTION__;

// }

void ffiPeerConnection::close()
{
    RTC_LOG(LS_VERBOSE) << __FUNCTION__;
    pc_->signaling_thread()->PostTask([pc = pc_] {
        RTC_DLOG(LS_INFO) << "Do Close";
        pc->Close();
    });
    return ;
}

void ffiPeerConnection::setAudioRecording(bool recording)
{
    RTC_LOG(LS_VERBOSE) << __FUNCTION__;
    pc_->SetAudioRecording(recording);
    return ;
}

void ffiPeerConnection::setAudioPlayout(bool playout)
{
    RTC_LOG(LS_VERBOSE) << __FUNCTION__;
    pc_->SetAudioPlayout(playout);
    return ;
}

}