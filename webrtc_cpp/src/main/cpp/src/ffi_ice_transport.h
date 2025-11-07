/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#ifndef WEBRTC4CJ_FFI_ICE_TRANSPORT_H
#define WEBRTC4CJ_FFI_ICE_TRANSPORT_H

#include "api/ice_transport_interface.h"
#include "ffi_cj_class.h"
#include "p2p/base/ice_transport_internal.h"

#include "event/ffi_event_target.h"
//#include "ice_candidate.h"
#include "ffi_define_struct.h"
#include "peer_connection_factory.h"


namespace webrtc {

//class PeerConnectionFactoryWrapper;

class ffiIceTransport : public FFIEventTarget<ffiIceTransport>, public sigslot::has_slots<> ,
                        public CJ_CLASS_BASE::FFICangjieClassID {
public:

    static ffiIceTransport* NewInstance(std::shared_ptr<PeerConnectionFactoryWrapper> factory,
        rtc::scoped_refptr<IceTransportInterface> iceTransport) {
            return new ffiIceTransport(factory, iceTransport);
        }
    
    ffiIceTransport(std::shared_ptr<PeerConnectionFactoryWrapper> factory,
        rtc::scoped_refptr<IceTransportInterface> iceTransport){
        factory_ = factory;
        iceTransport_ = iceTransport;
        
        factory_->GetNetworkThread()->BlockingCall([this] {
            auto internal = iceTransport_->internal();
            if (internal) {
                internal->SignalIceTransportStateChanged.connect(this, &ffiIceTransport::OnStateChange);
                internal->SignalGatheringState.connect(this, &ffiIceTransport::OnGatheringStateChange);
                internal->SignalCandidatePairChanged.connect(this, &ffiIceTransport::OnSelectedCandidatePairChange);
    
                iceTransportState_ = internal->GetIceTransportState();
                iceGatheringState_ = internal->gathering_state();
            } else {
                iceTransportState_ = IceTransportState::kClosed;
                iceGatheringState_ = cricket::kIceGatheringComplete;
            }
    
            if (iceTransportState_ == IceTransportState::kClosed) {
                Stop();
            }
        });
    }
    
    ~ffiIceTransport() override;

public:
    FFIRTCIceRole GetRole();
    FFIRTCIceComponent GetComponent();
    FFIRTCIceTransportState GetState();
    FFIRTCIceGathererState GetGatheringState();
    
    void OnStateChange(cricket::IceTransportInternal* iceTransport);
    void OnGatheringStateChange(cricket::IceTransportInternal* iceTransport);
    void OnSelectedCandidatePairChange(const cricket::CandidatePairChangeEvent& event);

    void (*cj_func_call_OnSelectedCandidatePairChange_)(int64_t id, CJ_Event ptr) = nullptr;
    void (*cj_func_call_OnStateChange_)(int64_t id, CJ_Event ptr) = nullptr;
    void (*cj_func_call_OnGatheringStateChange_)(int64_t id, CJ_Event ptr) = nullptr;
    
private:

    std::shared_ptr<PeerConnectionFactoryWrapper> factory_;
    rtc::scoped_refptr<IceTransportInterface> iceTransport_;

    std::atomic<IceTransportState> iceTransportState_{IceTransportState::kNew};
    std::atomic<cricket::IceGatheringState> iceGatheringState_{cricket::kIceGatheringNew};
};


}

#endif //WEBRTC4CJ_FFI_ICE_TRANSPORT_H
