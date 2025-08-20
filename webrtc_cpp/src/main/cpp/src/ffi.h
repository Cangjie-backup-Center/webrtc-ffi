#ifndef WEBRTC_FFI_H_
#define WEBRTC_FFI_H_

#include <cstdint>
#include <memory>

#include "render/ffi_native_video_renderer.h"
#include "audio_device/ffi_ohos_audio_device_module.h"
#include "ffi_video_encoder_factory.h"
#include "ffi_video_decoder_factory.h"
#include "ffi_peer_connection_factory.h"
#include "ffi_peer_connection.h"
#include "xcomponent/common/common.h"
#include "xcomponent/render/egl_core.h"
#include "xcomponent/render/plugin_render.h"
#include "xcomponent/manager/plugin_manager.h"

#include "ffi_define_struct.h"
#include "ffi_media_devices.h"

using namespace NativeXComponentSample;

extern "C" {
    int64_t ffi_newNativeVideoRenderer(int64_t surfaceId);
    void ffi_setVideoTrack(int64_t ffiNVR,int64_t ffiMST);
    void ffi_setMirror(int64_t ffiNVR,bool mirrorBool);
    void ffi_setMirrorVertically(int64_t ffiNVR,bool mirrorVerticallyBool);
    void ffi_setScalingMode(int64_t ffiNVR,int32_t scalingMode);
    void ffi_release(int64_t ffiNVR);

    int64_t ffi_newAudioDeviceModule(bool useStereoInput,bool useStereoOutput);
    int64_t ffi_newHardwareVideoEncoderFactory();
    int64_t ffi_newHardwareVideoDecoderFactory();
    int64_t ffi_newPeerConnectionFactory(int64_t ffiADM_int64 , int64_t ffiHVEF_int64 , int64_t ffiHVDF_int64);
    int64_t ffi_createAudioSource(int64_t ffiPCF_int64 , ffiAudioOptions ffiao);
    int64_t ffi_createAudioTrack(int64_t ffiPCF_int64 , char* ffi_audioId);
    int64_t ffi_createVideoSource(int64_t ffiPCF_int64 , ffiCreateVideoSourceParameters fficvsp);
    int64_t ffi_createVideoTrack(int64_t ffiPCF_int64 , char* ffi_videoId);
    void ffi_SetDefault(int64_t ffiPCF_int64);
    bool ffi_StartAecDump(int64_t ffiPCF_int64, int fd, int max_size_bytes);
    void ffi_StopAecDump(int64_t ffiPCF_int64);

    void ffi_SetSurfaceId(int64_t surfaceId);
    void ffi_ChangeSurface(int64_t surfaceId, double width, double height);
    void ffi_DrawPattern(int64_t surfaceId);
    void ffi_ChangeColor(int64_t surfaceId);
    void ffi_DestroySurface(int64_t surfaceId); 
    bool ffi_GetXComponentHasDraw(int64_t surfaceId);
    bool ffi_XComponentHasChangeColor(int64_t surfaceId);    

    // webrtc::MediaDevices
    int64_t ffi_webrtc_mediaDevices_create();
    void ffi_webrtc_mediaDevices_getDisplayMedia(int64_t mediaDevicesPtr, 
                                                  CJ_TO_CPP_DisplayMediaStreamOptions video, 
                                                  CJ_TO_CPP_DisplayMediaStreamOptions audio, 
                                                  CJ_TO_CPP_DisplayMediaStreamOptions systemAudio, 
                                                    int64_t id, void (*pe)(int64_t that, int64_t localVideoTrack));

    void ffi_webrtc_mediaDevices_getUserMedia(int64_t mediaDevicesPtr, 
                                               CJ_TO_CPP_DisplayMediaStreamOptions video, 
                                               CJ_TO_CPP_DisplayMediaStreamOptions audio, 
                                                    int64_t id, void (*pe)(int64_t that, int64_t localVideoTrack));

    CJ_ReturnEnumerateDevicesInfo ffi_webrtc_mediaDevices_enumerateDevices(int64_t mediaDevicesPtr);
    int64_t ffi_webrtc_mediaDevices_getSupportedConstraints(int64_t mediaDevicesPtr);
    
    // webrtc::FFIMediaStream
    void ffi_webrtc_FFIMediaStream_AddTrack(int64_t FFIMediaStreamPtr, int64_t mst);
    void ffi_webrtc_FFIMediaStream_RemoveTrack(int64_t FFIMediaStreamPtr, int64_t mst);
    int64_t ffi_webrtc_FFIMediaStream_GetTrackById(int64_t FFIMediaStreamPtr, char* trackId);
    CJ_ReturnArray ffi_webrtc_FFIMediaStream_GetTracks(int64_t FFIMediaStreamPtr);
    CJ_ReturnArray ffi_webrtc_FFIMediaStream_GetAudioTracks(int64_t FFIMediaStreamPtr);
    CJ_ReturnArray ffi_webrtc_FFIMediaStream_GetVideoTracks(int64_t FFIMediaStreamPtr);
    
    // webrtc::ffiMediaStreamTrack
    CJ_ffiMediaStreamTrackJson ffi_webrtc_ffiMediaStreamTrack_ToJson(int64_t ffiMediaStreamTrackPtr);
    int64_t ffi_webrtc_ffiMediaStreamTrack_GetSource(int64_t ffiMediaStreamTrackPtr);

    // peerConnection
    void peerConnection_set_class_key(int64_t cpp_ptr, int64_t classKey);  // 设置到对应的cpp类中仓颉类的randomid. 
    void peerConnection_set_cj_func_call_OnDataChannel_(int64_t cpp_ptr, void (*pe)(int64_t id, int64_t ptr));
    void peerConnection_set_cj_func_call_OnSignalingChange_(int64_t cpp_ptr, void (*pe)(int64_t id, CJ_Event ptr));
    void peerConnection_set_cj_func_call_OnIceCandidateError_(int64_t cpp_ptr, void (*pe)(int64_t id, CJ_RTCPeerConnectionIceErrorEvent ptr));
    void peerConnection_set_cj_func_call_onTrack_(int64_t cpp_ptr, void (*pe)(int64_t id, CJ_RTCTrackEvent ptr));
    bool peerConnection_GetCanTrickleIceCandidates(int64_t cpp_ptr);
    int64_t peerConnection_GetSignalingState(int64_t cpp_ptr);
    int64_t peerConnection_GetIceGatheringState(int64_t cpp_ptr);
    int64_t peerConnection_GetIceConnectionState(int64_t cpp_ptr);
    int64_t peerConnection_GetConnectionState(int64_t cpp_ptr);
    CJ_RTCSessionDescription peerConnection_GetLocalDescription(int64_t cpp_ptr);
    CJ_RTCSessionDescription peerConnection_GetRemoteDescription(int64_t cpp_ptr);
    CJ_RTCSessionDescription peerConnection_GetCurrentLocalDescription(int64_t cpp_ptr);
    CJ_RTCSessionDescription peerConnection_GetCurrentRemoteDescription(int64_t cpp_ptr);
    CJ_RTCSessionDescription peerConnection_GetPendingLocalDescription(int64_t cpp_ptr);
    CJ_RTCSessionDescription peerConnection_GetPendingRemoteDescription(int64_t cpp_ptr);
    int64_t peerConnection_GetSctp(int64_t cpp_ptr);
    int64_t peerConnection_static_GenerateCertificate(char* keyname);

    // DataChannel
    void dataConnection_set_class_key(int64_t cpp_ptr, int64_t classKey);  // 设置到对应的cpp类中仓颉类的randomid.
    void dataConnection_set_cj_func_Onopen_(int64_t cpp_ptr, void (*pe)(int64_t id, CJ_Event event));
    void dataConnection_set_cj_func_Onclosing_(int64_t cpp_ptr, void (*pe)(int64_t id, CJ_Event event));
    void dataConnection_set_cj_func_Onclose_(int64_t cpp_ptr, void (*pe)(int64_t id, CJ_Event event));
    void dataConnection_set_cj_func_Onmessage_(int64_t cpp_ptr, void (*pe)(int64_t id, CJ_Event event));
    char * dataConnection_get_label_(int64_t cpp_ptr);
    bool dataConnection_get_ordered_(int64_t cpp_ptr);
    int64_t dataConnection_get_maxPacketLifeTime_(int64_t cpp_ptr);
    int64_t dataConnection_get_maxRetransmits_(int64_t cpp_ptr);
    char* dataConnection_get_protocol_(int64_t cpp_ptr);
    bool dataConnection_get_negotiated_(int64_t cpp_ptr);
    int64_t dataConnection_get_id_(int64_t cpp_ptr);
    int64_t dataConnection_get_readyState_(int64_t cpp_ptr);
    int64_t dataConnection_get_bufferedAmount_(int64_t cpp_ptr);
    int64_t dataConnection_get_bufferedAmountLowThreshold_(int64_t cpp_ptr);
    void dataConnection_set_bufferedAmountLowThreshold_(int64_t cpp_ptr, int64_t value);
    int64_t dataConnection_get_binaryType_(int64_t cpp_ptr);
    void dataConnection_set_binaryType_(int64_t cpp_ptr, int64_t value);

    // sctp_transport
    void SctpTransport_set_class_key(int64_t cpp_ptr, int64_t classKey);


    // ffiDtmfSender
    void ffiDtmfSender_set_class_key(int64_t cpp_ptr, int64_t classKey);  // 设置到对应的cpp类中仓颉类的randomid.
    bool ffiDtmfSender_GetCanInsertDTMF(int64_t cpp_ptr);
    const char* ffiDtmfSender_GetToneBuffer(int64_t cpp_ptr); 
    bool ffiDtmfSender_InsertDTMF(int64_t cpp_ptr, const char* tones, int64_t duration, int64_t interToneGap);
    void ffiDtmfSender_set_OnToneChange(int64_t cpp_ptr, void (*pe)(int64_t id, const char* tone) ); 
    
    
}


#endif