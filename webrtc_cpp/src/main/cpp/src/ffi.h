#ifndef WEBRTC_FFI_H_
#define WEBRTC_FFI_H_

#include <memory>

#include "render/ffi_native_video_renderer.h"
#include "audio_device/ffi_ohos_audio_device_module.h"
#include "ffi_video_encoder_factory.h"
#include "ffi_video_decoder_factory.h"
#include "ffi_peer_connection_factory.h"
#include "xcomponent/common/common.h"
#include "xcomponent/render/egl_core.h"
#include "xcomponent/render/plugin_render.h"
#include "xcomponent/manager/plugin_manager.h"

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
    void ffi_StopAecDump(int64_t ffiPCF_int64);

    void ffi_SetSurfaceId(int64_t surfaceId);
    void ffi_ChangeSurface(int64_t surfaceId, double width, double height);
    void ffi_DrawPattern(int64_t surfaceId);
    void ffi_ChangeColor(int64_t surfaceId);
    void ffi_DestroySurface(int64_t surfaceId); 
    bool ffi_GetXComponentHasDraw(int64_t surfaceId);
    bool ffi_XComponentHasChangeColor(int64_t surfaceId);    
}


#endif