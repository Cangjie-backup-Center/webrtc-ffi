/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#include "ffi_ice_transport.h"

namespace webrtc {


FFIRTCIceRole ffiIceTransport::GetRole() {
    RTC_LOG(LS_VERBOSE) << __FUNCTION__;

    cricket::IceRole iceRole;
    factory_->GetNetworkThread()->BlockingCall([&iceRole, this] { iceRole = iceTransport_->internal()->GetIceRole(); });
    switch (iceRole) {
        case cricket::ICEROLE_CONTROLLING:
            return FFIRTCIceRole::CONTROLLING;
        case cricket::ICEROLE_CONTROLLED:
            return FFIRTCIceRole::CONTROLLED;
        case cricket::ICEROLE_UNKNOWN:
            return FFIRTCIceRole::UNKNOWN;
        default:
            break;
    }
    CANGJIE_THROW("Invalid role");
}
FFIRTCIceComponent ffiIceTransport::GetComponent() {
    RTC_LOG(LS_VERBOSE) << __FUNCTION__;

    int component = 0;

    factory_->GetNetworkThread()->BlockingCall(
        [&component, this] { component = iceTransport_->internal()->component(); });
    
    int32_t kComponentIdRtp = 1;
    int32_t kComponentIdRtcp = 2;
    
    if (component == kComponentIdRtp) {
        return FFIRTCIceComponent::RTP;
    }
    if (component == kComponentIdRtcp) {
        return FFIRTCIceComponent::RTCP;
    }
    CANGJIE_THROW("Invalid component");
    
}

FFIRTCIceTransportState ffiIceTransport::GetState() {
    RTC_LOG(LS_VERBOSE) << __FUNCTION__;

    IceTransportState iceTransportState = iceTransportState_;
    
    switch (iceTransportState) {
        case IceTransportState::kNew:
            return FFIRTCIceTransportState::NEW;
        case IceTransportState::kChecking:
            return FFIRTCIceTransportState::CHECKING;
        case IceTransportState::kConnected:
            return FFIRTCIceTransportState::CONNECTED;
        case IceTransportState::kCompleted:
            return FFIRTCIceTransportState::COMPLETED;
        case IceTransportState::kFailed:
            return FFIRTCIceTransportState::FAILED;
        case IceTransportState::kDisconnected:
            return FFIRTCIceTransportState::DISCONNECTED;
        case IceTransportState::kClosed:
            return FFIRTCIceTransportState::CLOSED;
        default:
            break;
    }
    CANGJIE_THROW("Invalid state");
}
FFIRTCIceGathererState ffiIceTransport::GetGatheringState() {
    RTC_LOG(LS_VERBOSE) << __FUNCTION__;

    cricket::IceGatheringState iceGatheringState = iceGatheringState_;
    switch (iceGatheringState) {
        case cricket::kIceGatheringNew:
            return FFIRTCIceGathererState::NEW;
        case cricket::kIceGatheringGathering:
            return FFIRTCIceGathererState::GATHERING;
        case cricket::kIceGatheringComplete:
            return FFIRTCIceGathererState::COMPLETE;
        default:
            break;
    }
    CANGJIE_THROW("Invalid gathering state");
    
}

void ffiIceTransport::OnStateChange(cricket::IceTransportInternal* iceTransport) {
    
    RTC_LOG(LS_VERBOSE) << __FUNCTION__;

    iceTransportState_ = iceTransport_->internal()->GetIceTransportState();
    
    this->Dispatch(CallbackEvent<ffiIceTransport>::Create([this, state = iceTransportState_.load()](ffiIceTransport& target) {
        RTC_DCHECK_EQ(this, &target);
        if (this->cj_func_call_OnStateChange_)
            this->cj_func_call_OnStateChange_(this->GetCJClassID(), CJ_Event{type: "statechange"});
        if (state == IceTransportState::kClosed) {
            target.Stop();
        }
    }));
}
void ffiIceTransport::OnGatheringStateChange(cricket::IceTransportInternal* iceTransport) {
    RTC_LOG(LS_VERBOSE) << __FUNCTION__;

    iceGatheringState_ = iceTransport->gathering_state();
    
    this->Dispatch(CallbackEvent<ffiIceTransport>::Create([this, state = iceTransportState_.load()](ffiIceTransport& target) {
        RTC_DCHECK_EQ(this, &target);
        if (this->cj_func_call_OnGatheringStateChange_) 
            this->cj_func_call_OnGatheringStateChange_(this->GetCJClassID(), CJ_Event{type: "gatheringstatechange"});
    }));
}
void ffiIceTransport::OnSelectedCandidatePairChange(const cricket::CandidatePairChangeEvent& event) {
    RTC_LOG(LS_VERBOSE) << __FUNCTION__;
    this->Dispatch(CallbackEvent<ffiIceTransport>::Create([this, state = iceTransportState_.load()](ffiIceTransport& target) {
        RTC_DCHECK_EQ(this, &target);
        if (this->cj_func_call_OnSelectedCandidatePairChange_)
            this->cj_func_call_OnSelectedCandidatePairChange_(this->GetCJClassID(), CJ_Event{type: "selectedcandidatepairchange"});
    }));
}


}
