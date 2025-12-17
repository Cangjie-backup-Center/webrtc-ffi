/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#include "ffi.h"
#include "ffi_data_channel.h"

#include <cstdint>

int64_t ffi_newNativeVideoRenderer(char* surfaceId)
{
    webrtc::ffiNativeVideoRenderer* ffiNVR = new webrtc::ffiNativeVideoRenderer();
    ffiNVR->ffiNativeVideoRendererInit(surfaceId);
    return reinterpret_cast<int64_t>(ffiNVR);
}

void ffi_setVideoTrack(int64_t ffiNVR, int64_t ffiMST)
{
    auto ffiNVR_ptr = reinterpret_cast<webrtc::ffiNativeVideoRenderer*>(ffiNVR);
    ffiNVR_ptr->setVideoTrack(ffiMST);
}

void ffi_setMirror(int64_t ffiNVR, bool mirrorBool)
{
    auto ffiNVR_ptr = reinterpret_cast<webrtc::ffiNativeVideoRenderer*>(ffiNVR);
    ffiNVR_ptr->setMirror(mirrorBool);
}

void ffi_setMirrorVertically(int64_t ffiNVR, bool mirrorVerticallyBool)
{
    auto ffiNVR_ptr = reinterpret_cast<webrtc::ffiNativeVideoRenderer*>(ffiNVR);
    ffiNVR_ptr->setMirrorVertically(mirrorVerticallyBool);
}

void ffi_setScalingMode(int64_t ffiNVR, int32_t scalingMode)
{
    auto ffiNVR_ptr = reinterpret_cast<webrtc::ffiNativeVideoRenderer*>(ffiNVR);
    ffiNVR_ptr->setScalingMode(scalingMode);
}

void ffi_release(int64_t ffiNVR)
{
    auto ffiNVR_ptr = reinterpret_cast<webrtc::ffiNativeVideoRenderer*>(ffiNVR);
    ffiNVR_ptr->release();
}

int64_t ffi_newAudioDeviceModule(bool useStereoInput, bool useStereoOutput)
{
    auto ffiADM = new webrtc::ffiAudioDeviceModule(useStereoInput, useStereoOutput);
    return reinterpret_cast<int64_t>(ffiADM);
}

int64_t ffi_newHardwareVideoEncoderFactory()
{
    auto ffiHVEF = new webrtc::ffiVideoEncoderFactory();
    return reinterpret_cast<int64_t>(ffiHVEF);
}

int64_t ffi_newHardwareVideoDecoderFactory()
{
    auto ffiHVDF = new webrtc::ffiVideoDecoderFactory();
    return reinterpret_cast<int64_t>(ffiHVDF);
}

int64_t ffi_newPeerConnectionFactory(int64_t ffiADM_int64, int64_t ffiHVEF_int64, int64_t ffiHVDF_int64)
{
    auto ffiADM_ptr = reinterpret_cast<webrtc::ffiAudioDeviceModule*>(ffiADM_int64);
    auto ffiHVEF_ptr = reinterpret_cast<webrtc::ffiVideoEncoderFactory*>(ffiHVEF_int64);
    auto ffiHVDF_ptr = reinterpret_cast<webrtc::ffiVideoDecoderFactory*>(ffiHVDF_int64);

    auto ffiPCF = new webrtc::ffiPeerConnectionFactory(ffiADM_ptr, ffiHVEF_ptr, ffiHVDF_ptr);
    return reinterpret_cast<int64_t>(ffiPCF);
}

int64_t ffi_createAudioSource(int64_t ffiPCF_int64, FFIAudioOptions ffiao)
{
    auto ffiPCF_ptr = reinterpret_cast<webrtc::ffiPeerConnectionFactory*>(ffiPCF_int64);
    return ffiPCF_ptr->ffiCreateAudioSource(ffiao);
}

int64_t ffi_createAudioTrack(int64_t ffiPCF_int64, CHAR_PTR ffi_audioId)
{
    auto ffiPCF_ptr = reinterpret_cast<webrtc::ffiPeerConnectionFactory*>(ffiPCF_int64);
    std::string ffi_id_str(ffi_audioId);
    delete[] ffi_audioId;
    return ffiPCF_ptr->ffiCreateAudioTrack(ffi_id_str);
}

int64_t ffi_createVideoSource(int64_t ffiPCF_int64, CJ_TO_CPP_DisplayMediaStreamOptions fficvsp, bool isScreencast)
{
    webrtc::ffiPeerConnectionFactory* ffiPCF_ptr = (webrtc::ffiPeerConnectionFactory*)ffiPCF_int64;
    return ffiPCF_ptr->ffiCreateVideoSource(fficvsp, isScreencast);
}

int64_t ffi_createVideoTrack(int64_t ffiPCF_int64, CHAR_PTR ffi_videoId)
{
    webrtc::ffiPeerConnectionFactory* ffiPCF_ptr = (webrtc::ffiPeerConnectionFactory*)ffiPCF_int64;
    std::string ffi_videoId_str(ffi_videoId);
    delete[] ffi_videoId;
    int64_t ffiMST = ffiPCF_ptr->ffiCreateVideoTrack(ffi_videoId_str);
    return ffiMST;
}

int64_t ffiPeerConnectionFactory_ffiCreatePeerConnection (int64_t ffiPCF_int64, CJ_RTCConfiguration config)
{
    auto ffiPCF_ptr = reinterpret_cast<webrtc::ffiPeerConnectionFactory*>(ffiPCF_int64);
    return ffiPCF_ptr->ffiCreatePeerConnection(config);
}

void ffi_SetDefault(int64_t ffiPCF_int64)
{
    webrtc::ffiPeerConnectionFactory* ffiPCF_ptr = (webrtc::ffiPeerConnectionFactory*)ffiPCF_int64;
    webrtc::ffiPeerConnectionFactory::SetDefault(ffiPCF_ptr);
}

bool ffi_StartAecDump(int64_t ffiPCF_int64, int fd, int max_size_bytes)
{
    webrtc::ffiPeerConnectionFactory* ffiPCF_ptr = (webrtc::ffiPeerConnectionFactory*)ffiPCF_int64;
    return ffiPCF_ptr->StartAecDump(fd, max_size_bytes);
}

void ffi_StopAecDump(int64_t ffiPCF_int64)
{
    webrtc::ffiPeerConnectionFactory* ffiPCF_ptr = (webrtc::ffiPeerConnectionFactory*)ffiPCF_int64;
    ffiPCF_ptr->StopAecDump();
}

int64_t ffi_webrtc_mediaDevices_create()
{
    auto ffiMediaDevicesPtr = new webrtc::FFIMediaDevices();
    return reinterpret_cast<int64_t>(ffiMediaDevicesPtr);
}

int64_t ffi_webrtc_mediaDevices_getDisplayMedia(int64_t mediaDevicesPtr,
    CJ_TO_CPP_DisplayMediaStreamOptions video,
    CJ_TO_CPP_DisplayMediaStreamOptions audio,
    CJ_TO_CPP_DisplayMediaStreamOptions systemAudio)
{
    auto mediaDevicesPtr_ = reinterpret_cast<webrtc::FFIMediaDevices*>(mediaDevicesPtr);
    return mediaDevicesPtr_->getDisplayMedia(video, audio, systemAudio);
}

void ffi_webrtc_mediaDevices_getUserMedia(int64_t mediaDevicesPtr,
    CJ_TO_CPP_DisplayMediaStreamOptions video,
    CJ_TO_CPP_DisplayMediaStreamOptions audio,
    int64_t id, void (*pe)(int64_t that, int64_t localVideoTrack))
{
    auto mediaDevicesPtr_ = reinterpret_cast<webrtc::FFIMediaDevices*>(mediaDevicesPtr);
    mediaDevicesPtr_->getUserMedia(&video, &audio, id, pe);
}

CJ_ReturnEnumerateDevicesInfo ffi_webrtc_mediaDevices_enumerateDevices(int64_t mediaDevicesPtr)
{
    auto mediaDevicesPtr_ = reinterpret_cast<webrtc::FFIMediaDevices*>(mediaDevicesPtr);
    return mediaDevicesPtr_->enumerateDevices();
}

int64_t ffi_webrtc_mediaDevices_getSupportedConstraints(int64_t mediaDevicesPtr)
{
    auto mediaDevicesPtr_ = reinterpret_cast<webrtc::FFIMediaDevices*>(mediaDevicesPtr);
    return mediaDevicesPtr_->getSupportedConstraints();
}

void ffi_webrtc_FFIMediaStream_AddTrack(int64_t FFIMediaStreamPtr, int64_t mst)
{
    auto mediaStreamPtr_ = reinterpret_cast<webrtc::FFIMediaStream*>(FFIMediaStreamPtr);
    mediaStreamPtr_->AddTrack(mst);
}

void ffi_webrtc_FFIMediaStream_RemoveTrack(int64_t FFIMediaStreamPtr, int64_t mst)
{
    auto mediaStreamPtr_ = reinterpret_cast<webrtc::FFIMediaStream*>(FFIMediaStreamPtr);
    mediaStreamPtr_->RemoveTrack(mst);
}

int64_t ffi_webrtc_FFIMediaStream_GetTrackById(int64_t FFIMediaStreamPtr, CHAR_PTR trackId)
{
    auto mediaStreamPtr_ = reinterpret_cast<webrtc::FFIMediaStream*>(FFIMediaStreamPtr);
    std::string trackId_str(trackId);
    delete[] trackId;
    return mediaStreamPtr_->GetTrackById(trackId_str);
}

CJ_ReturnArray ffi_webrtc_FFIMediaStream_GetTracks(int64_t FFIMediaStreamPtr)
{
    auto mediaStreamPtr_ = reinterpret_cast<webrtc::FFIMediaStream*>(FFIMediaStreamPtr);
    return mediaStreamPtr_->GetTracks();
}

CJ_ReturnArray ffi_webrtc_FFIMediaStream_GetAudioTracks(int64_t FFIMediaStreamPtr)
{
    auto mediaStreamPtr_ = reinterpret_cast<webrtc::FFIMediaStream*>(FFIMediaStreamPtr);
    return mediaStreamPtr_->GetAudioTracks();
}

CJ_ReturnArray ffi_webrtc_FFIMediaStream_GetVideoTracks(int64_t FFIMediaStreamPtr)
{
    auto mediaStreamPtr_ = reinterpret_cast<webrtc::FFIMediaStream*>(FFIMediaStreamPtr);
    return mediaStreamPtr_->GetVideoTracks();
}

CJ_ffiMediaStreamTrackJson ffi_webrtc_ffiMediaStreamTrack_ToJson(int64_t ffiMediaStreamTrackPtr)
{
    auto ffiMediaStreamTrackPtr_ = reinterpret_cast<webrtc::ffiMediaStreamTrack*>(ffiMediaStreamTrackPtr);
    return ffiMediaStreamTrackPtr_->ToJson();
}

int64_t ffi_webrtc_ffiMediaStreamTrack_GetSource(int64_t ffiMediaStreamTrackPtr)
{
    auto ffiMediaStreamTrackPtr_ = reinterpret_cast<webrtc::ffiMediaStreamTrack*>(ffiMediaStreamTrackPtr);
    return ffiMediaStreamTrackPtr_->GetSource();
}

char* ffiMediaStreamTrack_getKind(int64_t cpp_ptr)
{
    auto ffiMediaStreamTrackPtr_ = reinterpret_cast<webrtc::ffiMediaStreamTrack*>(cpp_ptr);
    return ffiMediaStreamTrackPtr_->GetKind();
}

bool ffiMediaStreamTrack_getEnabled(int64_t cpp_ptr)
{
    auto ffiMediaStreamTrackPtr_ = reinterpret_cast<webrtc::ffiMediaStreamTrack*>(cpp_ptr);
    return ffiMediaStreamTrackPtr_->GetEnabled();
}

char* ffiMediaStreamTrack_getReadyState(int64_t cpp_ptr)
{
    auto ffiMediaStreamTrackPtr_ = reinterpret_cast<webrtc::ffiMediaStreamTrack*>(cpp_ptr);
    return ffiMediaStreamTrackPtr_->GetReadyState();
}

char* ffiMediaStreamTrack_getId(int64_t cpp_ptr)
{
    auto ffiMediaStreamTrackPtr_ = reinterpret_cast<webrtc::ffiMediaStreamTrack*>(cpp_ptr);
    return ffiMediaStreamTrackPtr_->GetId();
}

void ffiMediaStreamTrack_Stop(int64_t cpp_ptr)
{
    auto ffiMediaStreamTrackPtr_ = reinterpret_cast<webrtc::ffiMediaStreamTrack*>(cpp_ptr);
    ffiMediaStreamTrackPtr_->Stop();
}

void peerConnection_set_class_key(int64_t cpp_ptr, int64_t classKey)
{
    auto peerConnectionPtr_ = reinterpret_cast<webrtc::ffiPeerConnection*>(cpp_ptr);
    peerConnectionPtr_->SetCJClassID(classKey);
}

void peerConnection_SetOnDataChannel_(int64_t cpp_ptr, void (*pe)(int64_t id, int64_t ptr))
{
    auto peerConnectionPtr_ = reinterpret_cast<webrtc::ffiPeerConnection*>(cpp_ptr);
    peerConnectionPtr_->SetOnDataChannel(pe);
}

void peerConnection_SetOnSignalingChange_(int64_t cpp_ptr, void (*pe)(int64_t id, CJ_Event ptr))
{
    auto peerConnectionPtr_ = reinterpret_cast<webrtc::ffiPeerConnection*>(cpp_ptr);
    peerConnectionPtr_->SetOnSignalingChange(pe);
}

void peerConnection_SetOnIceCandidateError_(int64_t cpp_ptr,
    void (*pe)(int64_t id, CJ_RTCPeerConnectionIceErrorEvent ptr))
{
    auto peerConnectionPtr_ = reinterpret_cast<webrtc::ffiPeerConnection*>(cpp_ptr);
    peerConnectionPtr_->SetOnIceCandidateError(pe);
}

void peerConnection_SetonTrack_(int64_t cpp_ptr, void (*pe)(int64_t id, CJ_RTCTrackEvent ptr))
{
    auto peerConnectionPtr_ = reinterpret_cast<webrtc::ffiPeerConnection*>(cpp_ptr);
    peerConnectionPtr_->SetOnTrack(pe);
}

void peerConnection_SetOnConnectionChange_(int64_t cpp_ptr, void (*pe)(int64_t id, CJ_Event ptr))
{
    auto peerConnectionPtr_ = reinterpret_cast<webrtc::ffiPeerConnection*>(cpp_ptr);
    peerConnectionPtr_->SetOnConnectionChange(pe);
}

void peerConnection_SetOnRenegotiationNeeded_(int64_t cpp_ptr, void (*pe)(int64_t id, CJ_Event ptr))
{
    auto peerConnectionPtr_ = reinterpret_cast<webrtc::ffiPeerConnection*>(cpp_ptr);
    peerConnectionPtr_->SetOnRenegotiationNeeded(pe);
}

void peerConnection_SetOnStandardizedIceConnectionChange_(int64_t cpp_ptr, void (*pe)(int64_t id, CJ_Event ptr))
{
    auto peerConnectionPtr_ = reinterpret_cast<webrtc::ffiPeerConnection*>(cpp_ptr);
    peerConnectionPtr_->SetOnStandardizedIceConnectionChange(pe);
}

void peerConnection_SetOnIceGatheringChange_(int64_t cpp_ptr, void (*pe)(int64_t id, CJ_Event ptr))
{
    auto peerConnectionPtr_ = reinterpret_cast<webrtc::ffiPeerConnection*>(cpp_ptr);
    peerConnectionPtr_->SetOnIceGatheringChange(pe);
}

void peerConnection_SetOnIceCandidate_(int64_t cpp_ptr, void (*pe)(int64_t id, CJ_RTCPeerConnectionIceEvent ptr))
{
    auto peerConnectionPtr_ = reinterpret_cast<webrtc::ffiPeerConnection*>(cpp_ptr);
    peerConnectionPtr_->SetOnIceCandidate(pe);
}

void peerConnection_SetCallBackCreateOffer_(int64_t cpp_ptr,
    void (*pe)(int64_t id, bool isSuccess, CJ_RTCSessionDescription ptr, const char* msg))
{
    auto peerConnectionPtr_ = reinterpret_cast<webrtc::ffiPeerConnection*>(cpp_ptr);
    peerConnectionPtr_->SetCallBackCreateOffer(pe);
}

void peerConnection_SetCallBackCreateAnswer_(int64_t cpp_ptr,
    void (*pe)(int64_t id, bool isSuccess, CJ_RTCSessionDescription ptr, const char* msg))
{
    auto peerConnectionPtr_ = reinterpret_cast<webrtc::ffiPeerConnection*>(cpp_ptr);
    peerConnectionPtr_->SetCallBackCreateAnswer(pe);
}

bool peerConnection_GetCanTrickleIceCandidates(int64_t cpp_ptr)
{
    auto peerConnectionPtr_ = reinterpret_cast<webrtc::ffiPeerConnection*>(cpp_ptr);
    return peerConnectionPtr_->GetCanTrickleIceCandidates();
}

int64_t peerConnection_GetSignalingState(int64_t cpp_ptr)
{
    auto cpp_ptr_ = reinterpret_cast<webrtc::ffiPeerConnection*>(cpp_ptr);
    return static_cast<int64_t>(cpp_ptr_->GetSignalingState());
}

int64_t peerConnection_GetIceGatheringState(int64_t cpp_ptr)
{
    auto cpp_ptr_ = reinterpret_cast<webrtc::ffiPeerConnection*>(cpp_ptr);
    return static_cast<int64_t>(cpp_ptr_->GetIceGatheringState());
}
int64_t peerConnection_GetIceConnectionState(int64_t cpp_ptr)
{
    auto cpp_ptr_ = reinterpret_cast<webrtc::ffiPeerConnection*>(cpp_ptr);
    return static_cast<int64_t>(cpp_ptr_->GetIceConnectionState());
}
int64_t peerConnection_GetConnectionState(int64_t cpp_ptr)
{
    auto cpp_ptr_ = reinterpret_cast<webrtc::ffiPeerConnection*>(cpp_ptr);
    return static_cast<int64_t>(cpp_ptr_->GetConnectionState());
}

CJ_RTCSessionDescription peerConnection_GetLocalDescription(int64_t cpp_ptr)
{
    auto cpp_ptr_ = reinterpret_cast<webrtc::ffiPeerConnection*>(cpp_ptr);
    return cpp_ptr_->GetLocalDescription();
}

CJ_RTCSessionDescription peerConnection_GetRemoteDescription(int64_t cpp_ptr)
{
    auto cpp_ptr_ = reinterpret_cast<webrtc::ffiPeerConnection*>(cpp_ptr);
    return cpp_ptr_->GetRemoteDescription();
}

CJ_RTCSessionDescription peerConnection_GetCurrentLocalDescription(int64_t cpp_ptr)
{
    auto cpp_ptr_ = reinterpret_cast<webrtc::ffiPeerConnection*>(cpp_ptr);
    return cpp_ptr_->GetCurrentLocalDescription();
}

CJ_RTCSessionDescription peerConnection_GetCurrentRemoteDescription(int64_t cpp_ptr)
{
    auto cpp_ptr_ = reinterpret_cast<webrtc::ffiPeerConnection*>(cpp_ptr);
    return cpp_ptr_->GetCurrentRemoteDescription();
}

CJ_RTCSessionDescription peerConnection_GetPendingLocalDescription(int64_t cpp_ptr)
{
    auto cpp_ptr_ = reinterpret_cast<webrtc::ffiPeerConnection*>(cpp_ptr);
    return cpp_ptr_->GetPendingLocalDescription();
}

CJ_RTCSessionDescription peerConnection_GetPendingRemoteDescription(int64_t cpp_ptr)
{
    auto cpp_ptr_ = reinterpret_cast<webrtc::ffiPeerConnection*>(cpp_ptr);
    return cpp_ptr_->GetPendingRemoteDescription();
}

int64_t peerConnection_GetSctp(int64_t cpp_ptr)
{
    auto cpp_ptr_ = reinterpret_cast<webrtc::ffiPeerConnection*>(cpp_ptr);
    return cpp_ptr_->GetSctp();
}

int64_t peerConnection_static_GenerateCertificate(CHAR_PTR keyname)
{
    return webrtc::ffiPeerConnection::GenerateCertificate(keyname);
}

int64_t peerConnection_addTrack(int64_t cpp_ptr, int64_t ffiMST_ptr, CJ_ArrayMediaStream streamVec)
{
    std::vector<webrtc::FFIMediaStream*> arr;
    for (int i = 0; i < streamVec.size; i++) {
        arr.push_back((webrtc::FFIMediaStream*)streamVec.ptr[i]);
    }
    auto ffiMST_ptr_ = reinterpret_cast<webrtc::ffiMediaStreamTrack*>(ffiMST_ptr);
    auto cpp_ptr_ = reinterpret_cast<webrtc::ffiPeerConnection*>(cpp_ptr);
    return cpp_ptr_->addTrack(ffiMST_ptr_, arr);
}

void peerConnection_setLocalDescription(int64_t cpp_ptr, CJ_RTCSessionDescription description,
    void (*pe)(int64_t cj_id, CJ_ErrorMessage msg))
{
    auto cpp_ptr_ = reinterpret_cast<webrtc::ffiPeerConnection*>(cpp_ptr);
    cpp_ptr_->setLocalDescription(description, pe);
}

void peerConnection_setRemoteDescription(int64_t cpp_ptr, CJ_RTCSessionDescription description,
    void (*pe)(int64_t cj_id, CJ_ErrorMessage msg))
{
    auto cpp_ptr_ = reinterpret_cast<webrtc::ffiPeerConnection*>(cpp_ptr);
    cpp_ptr_->setRemoteDescription(description, pe);
}

CJ_FFICreateSdpObserver_result peerConnection_createOffer(int64_t cpp_ptr, bool iceRestart)
{
    auto cpp_ptr_ = reinterpret_cast<webrtc::ffiPeerConnection*>(cpp_ptr);
    return cpp_ptr_->createOffer(iceRestart);
}

CJ_FFICreateSdpObserver_result peerConnection_createAnswer(int64_t cpp_ptr)
{
    auto cpp_ptr_ = reinterpret_cast<webrtc::ffiPeerConnection*>(cpp_ptr);
    return cpp_ptr_->createAnswer();
}

int64_t peerConnection_createDataChannel(int64_t cpp_ptr, CHAR_PTR label, CJ_RTCDataChannelInit dataChannelDict)
{
    auto cpp_ptr_ = reinterpret_cast<webrtc::ffiPeerConnection*>(cpp_ptr);
    return cpp_ptr_->createDataChannel(label, dataChannelDict);
}

void peerConnection_addIceCandidate(int64_t cpp_ptr, CJ_RTCIceCandidateInit candidate)
{
    auto cpp_ptr_ = reinterpret_cast<webrtc::ffiPeerConnection*>(cpp_ptr);
    cpp_ptr_->addIceCandidate(candidate);
}

void peerConnection_SetAddIceCandidate(int64_t cpp_ptr, void (*pe)(int64_t id, const char* msg))
{
    auto cpp_ptr_ = reinterpret_cast<webrtc::ffiPeerConnection*>(cpp_ptr);
    cpp_ptr_->SetAddIceCandidate(pe);
}

int64_t* peerConnection_getSenders(int64_t cpp_ptr)
{
    auto cpp_ptr_ = reinterpret_cast<webrtc::ffiPeerConnection*>(cpp_ptr);
    return cpp_ptr_->getSenders();
}

int64_t* peerConnection_getReceivers(int64_t cpp_ptr)
{
    auto cpp_ptr_ = reinterpret_cast<webrtc::ffiPeerConnection*>(cpp_ptr);
    return cpp_ptr_->getReceivers();
}

int64_t* peerConnection_getTransceivers(int64_t cpp_ptr)
{
    auto cpp_ptr_ = reinterpret_cast<webrtc::ffiPeerConnection*>(cpp_ptr);
    return cpp_ptr_->getTransceivers();
}

void peerConnection_restartIce(int64_t cpp_ptr)
{
    auto cpp_ptr_ = reinterpret_cast<webrtc::ffiPeerConnection*>(cpp_ptr);
    cpp_ptr_->restartIce();
}

void peerConnection_setConfiguration(int64_t cpp_ptr, CJ_RTCConfiguration configuration)
{
    auto cpp_ptr_ = reinterpret_cast<webrtc::ffiPeerConnection*>(cpp_ptr);
    cpp_ptr_->setConfiguration(configuration);
}

void peerConnection_close(int64_t cpp_ptr)
{
    auto cpp_ptr_ = reinterpret_cast<webrtc::ffiPeerConnection*>(cpp_ptr);
    cpp_ptr_->close();
}

void peerConnection_setAudioRecording(int64_t cpp_ptr, bool recording)
{
    auto cpp_ptr_ = reinterpret_cast<webrtc::ffiPeerConnection*>(cpp_ptr);
    cpp_ptr_->setAudioRecording(recording);
}

void peerConnection_setAudioPlayout(int64_t cpp_ptr, bool playout)
{
    auto cpp_ptr_ = reinterpret_cast<webrtc::ffiPeerConnection*>(cpp_ptr);
    cpp_ptr_->setAudioPlayout(playout);
}

void peerConnection_CPP_FREE(int64_t cpp_ptr)
{
    auto cpp_ptr_ = reinterpret_cast<webrtc::ffiPeerConnection*>(cpp_ptr);
    delete cpp_ptr_;
}

// dataConnection
void dataConnection_set_class_key(int64_t cpp_ptr, int64_t classKey)
{
    auto cpp_ptr_ = reinterpret_cast<webrtc::ffiDataChannelObserverTemp*>(cpp_ptr);
    cpp_ptr_->SetCJClassID(classKey);
}

void dataConnection_set_cj_func_Onopen_(int64_t cpp_ptr, void (*pe)(int64_t id, CJ_Event event))
{
    auto cpp_ptr_ = reinterpret_cast<webrtc::ffiDataChannelObserverTemp*>(cpp_ptr);
    cpp_ptr_->SetOnopen(pe);
}

void dataConnection_set_cj_func_Onclosing_(int64_t cpp_ptr, void (*pe)(int64_t id, CJ_Event event))
{
    auto cpp_ptr_ = reinterpret_cast<webrtc::ffiDataChannelObserverTemp*>(cpp_ptr);
    cpp_ptr_->SetOnclosing(pe);
}

void dataConnection_set_cj_func_Onclose_(int64_t cpp_ptr, void (*pe)(int64_t id, CJ_Event event))
{
    auto cpp_ptr_ = reinterpret_cast<webrtc::ffiDataChannelObserverTemp*>(cpp_ptr);
    cpp_ptr_->SetOnclose(pe);
}

void dataConnection_set_cj_func_Onmessage_(int64_t cpp_ptr, void (*pe)(int64_t id, CJ_MessageEvent event))
{
    auto cpp_ptr_ = reinterpret_cast<webrtc::ffiDataChannelObserverTemp*>(cpp_ptr);
    cpp_ptr_->SetOnMessage(pe);
}

char* dataConnection_get_label_(int64_t cpp_ptr)
{
    auto cpp_ptr_ = reinterpret_cast<webrtc::ffiDataChannelObserverTemp*>(cpp_ptr);
    return cpp_ptr_->GetLabel().data();
}

bool dataConnection_get_ordered_(int64_t cpp_ptr)
{
    auto cpp_ptr_ = reinterpret_cast<webrtc::ffiDataChannelObserverTemp*>(cpp_ptr);
    return cpp_ptr_->GetOrdered();
}

int64_t dataConnection_get_maxPacketLifeTime_(int64_t cpp_ptr)
{
    auto cpp_ptr_ = reinterpret_cast<webrtc::ffiDataChannelObserverTemp*>(cpp_ptr);
    return cpp_ptr_->GetMaxPacketLifeTime();
}

int64_t dataConnection_get_maxRetransmits_(int64_t cpp_ptr)
{
    auto cpp_ptr_ = reinterpret_cast<webrtc::ffiDataChannelObserverTemp*>(cpp_ptr);
    return cpp_ptr_->GetMaxRetransmits();
}

char* dataConnection_get_protocol_(int64_t cpp_ptr)
{
    auto cpp_ptr_ = reinterpret_cast<webrtc::ffiDataChannelObserverTemp*>(cpp_ptr);
    return cpp_ptr_->GetProtocol().data();
}

bool dataConnection_get_negotiated_(int64_t cpp_ptr)
{
    auto cpp_ptr_ = reinterpret_cast<webrtc::ffiDataChannelObserverTemp*>(cpp_ptr);
    return cpp_ptr_->GetNegotiated();
}

int64_t dataConnection_get_id_(int64_t cpp_ptr)
{
    auto cpp_ptr_ = reinterpret_cast<webrtc::ffiDataChannelObserverTemp*>(cpp_ptr);
    return cpp_ptr_->GetId();
}

int64_t dataConnection_get_readyState_(int64_t cpp_ptr)
{
    auto cpp_ptr_ = reinterpret_cast<webrtc::ffiDataChannelObserverTemp*>(cpp_ptr);
    return static_cast<int64_t>(cpp_ptr_->GetReadyState());
}

int64_t dataConnection_get_bufferedAmount_(int64_t cpp_ptr)
{
    auto cpp_ptr_ = reinterpret_cast<webrtc::ffiDataChannelObserverTemp*>(cpp_ptr);
    return cpp_ptr_->GetBufferedAmount();
}

int64_t dataConnection_get_bufferedAmountLowThreshold_(int64_t cpp_ptr)
{
    auto cpp_ptr_ = reinterpret_cast<webrtc::ffiDataChannelObserverTemp*>(cpp_ptr);
    return cpp_ptr_->GetBufferedAmountLowThreshold();
}

void dataConnection_set_bufferedAmountLowThreshold_(int64_t cpp_ptr, int64_t value)
{
    auto cpp_ptr_ = reinterpret_cast<webrtc::ffiDataChannelObserverTemp*>(cpp_ptr);
    cpp_ptr_->SetBufferedAmountLowThreshold(value);
}

int64_t dataConnection_get_binaryType_(int64_t cpp_ptr)
{
    auto cpp_ptr_ = reinterpret_cast<webrtc::ffiDataChannelObserverTemp*>(cpp_ptr);
    return static_cast<int64_t>(cpp_ptr_->GetBinaryType());
}

void dataConnection_set_binaryType_(int64_t cpp_ptr, int64_t value)
{
    auto cpp_ptr_ = reinterpret_cast<webrtc::ffiDataChannelObserverTemp*>(cpp_ptr);
    cpp_ptr_->SetBinaryType((enum FFIBinaryType)value);
}

void dataConnection_Send_String(int64_t cpp_ptr, CHAR_PTR data)
{
    auto cpp_ptr_ = reinterpret_cast<webrtc::ffiDataChannelObserverTemp*>(cpp_ptr);
    std::string dataStr(data);
    delete[] data;
    cpp_ptr_->Send(dataStr);
}

void dataConnection_Send_binary(int64_t cpp_ptr, uint8_t* data, int64_t size)
{
    auto cpp_ptr_ = reinterpret_cast<webrtc::ffiDataChannelObserverTemp*>(cpp_ptr);
    cpp_ptr_->Send(data, size);
}

void dataConnection_Close(int64_t cpp_ptr)
{
    auto cpp_ptr_ = reinterpret_cast<webrtc::ffiDataChannelObserverTemp*>(cpp_ptr);
    cpp_ptr_->Close();
}

void RTCDataChannel_CPP_FREE(int64_t cpp_ptr)
{
    auto cpp_ptr_ = reinterpret_cast<webrtc::ffiDataChannelObserverTemp*>(cpp_ptr);
    delete cpp_ptr_;
}

void SctpTransport_set_class_key(int64_t cpp_ptr, int64_t classKey)
{
    auto cpp_ptr_ = reinterpret_cast<webrtc::ffiSctpTransport*>(cpp_ptr);
    cpp_ptr_->SetCJClassID(classKey);
}

// ffiDtmfSender
void ffiDtmfSender_set_class_key(int64_t cpp_ptr, int64_t classKey)
{
    auto cpp_ptr_ = reinterpret_cast<webrtc::ffiDtmfSender*>(cpp_ptr);
    cpp_ptr_->SetCJClassID(classKey);
}

bool ffiDtmfSender_GetCanInsertDTMF(int64_t cpp_ptr)
{
    auto cpp_ptr_ = reinterpret_cast<webrtc::ffiDtmfSender*>(cpp_ptr);
    return cpp_ptr_->GetCanInsertDTMF();
}

const char* ffiDtmfSender_GetToneBuffer(int64_t cpp_ptr)
{
    auto cpp_ptr_ = reinterpret_cast<webrtc::ffiDtmfSender*>(cpp_ptr);
    return cpp_ptr_->GetToneBuffer();
}

bool ffiDtmfSender_InsertDTMF(int64_t cpp_ptr, const char* tones, int64_t duration, int64_t interToneGap)
{
    auto cpp_ptr_ = reinterpret_cast<webrtc::ffiDtmfSender*>(cpp_ptr);
    return cpp_ptr_->InsertDTMF(tones, duration, interToneGap);
}

void ffiDtmfSender_set_OnToneChange(int64_t cpp_ptr, void (*pe)(int64_t id, const char* tone))
{
    auto cpp_ptr_ = reinterpret_cast<webrtc::ffiDtmfSender*>(cpp_ptr);
    cpp_ptr_->cj_func_call_OnToneChange_ = pe;
}
