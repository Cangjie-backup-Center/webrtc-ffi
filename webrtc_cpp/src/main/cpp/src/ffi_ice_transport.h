//
// Created on 2025/8/14.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef WEBRTC4CJ_FFI_ICE_TRANSPORT_H
#define WEBRTC4CJ_FFI_ICE_TRANSPORT_H

#include "api/ice_transport_interface.h"
#include "p2p/base/ice_transport_internal.h"

#include "event/ffi_event_target.h"
#include "ice_candidate.h"


namespace webrtc {

class ffiPeerConnectionFactory;

class ffiIceTransport : public FFIEventTarget<ffiIceTransport>, public sigslot::has_slots<> {
public:
    static void Init(Napi::Env env, Napi::Object exports);

    static Napi::Object NewInstance(
        Napi::Env env, std::shared_ptr<ffiPeerConnectionFactory> factory,
        rtc::scoped_refptr<IceTransportInterface> iceTransport);

    ~ffiIceTransport() override;

protected:

    explicit ffiIceTransport(const Napi::CallbackInfo& info);

public:
    // JS
//    Napi::Value GetRole(const Napi::CallbackInfo& info);
//    Napi::Value GetComponent(const Napi::CallbackInfo& info);
//    Napi::Value GetState(const Napi::CallbackInfo& info);
//    Napi::Value GetGatheringState(const Napi::CallbackInfo& info);
//
//    Napi::Value GetEventHandler(const Napi::CallbackInfo& info);
//    void SetEventHandler(const Napi::CallbackInfo& info, const Napi::Value& value);
//
//    Napi::Value GetLocalCandidates(const Napi::CallbackInfo& info);
//    Napi::Value GetLocalParameters(const Napi::CallbackInfo& info);
//    Napi::Value GetRemoteCandidates(const Napi::CallbackInfo& info);
//    Napi::Value GetRemoteParameters(const Napi::CallbackInfo& info);
//    Napi::Value GetSelectedCandidatePair(const Napi::CallbackInfo& info);
//    Napi::Value ToJson(const Napi::CallbackInfo& info);

    void OnStateChange(cricket::IceTransportInternal* iceTransport);
    void OnGatheringStateChange(cricket::IceTransportInternal* iceTransport);
    void OnSelectedCandidatePairChange(const cricket::CandidatePairChangeEvent& event);

private:

    std::shared_ptr<ffiPeerConnectionFactory> factory_;
    rtc::scoped_refptr<IceTransportInterface> iceTransport_;

    std::atomic<IceTransportState> iceTransportState_{IceTransportState::kNew};
    std::atomic<cricket::IceGatheringState> iceGatheringState_{cricket::kIceGatheringNew};
};


}

#endif //WEBRTC4CJ_FFI_ICE_TRANSPORT_H
