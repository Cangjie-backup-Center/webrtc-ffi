#include "ffi.h"

int64_t ffi_newNativeVideoRenderer(int64_t surfaceId) {
    webrtc::ffiNativeVideoRenderer* ffiNVR = new webrtc::ffiNativeVideoRenderer();
    ffiNVR->ffiNativeVideoRendererInit(surfaceId);
    return (int64_t)ffiNVR;
}

void ffi_setVideoTrack(int64_t ffiNVR,int64_t ffiMST) {
    webrtc::ffiNativeVideoRenderer* ffiNVR_ptr = (webrtc::ffiNativeVideoRenderer*)ffiNVR;
    ffiNVR_ptr->setVideoTrack(ffiMST);
}

void ffi_setMirror(int64_t ffiNVR,bool mirrorBool) {
    webrtc::ffiNativeVideoRenderer* ffiNVR_ptr = (webrtc::ffiNativeVideoRenderer*)ffiNVR;
    ffiNVR_ptr->setMirror(mirrorBool);
}

void ffi_setMirrorVertically(int64_t ffiNVR,bool mirrorVerticallyBool) {    
    webrtc::ffiNativeVideoRenderer* ffiNVR_ptr = (webrtc::ffiNativeVideoRenderer*)ffiNVR;
    ffiNVR_ptr->setMirrorVertically(mirrorVerticallyBool);
}

void ffi_setScalingMode(int64_t ffiNVR,int32_t scalingMode) {
    webrtc::ffiNativeVideoRenderer* ffiNVR_ptr = (webrtc::ffiNativeVideoRenderer*)ffiNVR;
    ffiNVR_ptr->setScalingMode(scalingMode);
}

void ffi_release(int64_t ffiNVR) {
    webrtc::ffiNativeVideoRenderer* ffiNVR_ptr = (webrtc::ffiNativeVideoRenderer*)ffiNVR;
    ffiNVR_ptr->release();
}

int64_t ffi_newAudioDeviceModule(bool useStereoInput,bool useStereoOutput){
    webrtc::ffiAudioDeviceModule* ffiADM = new webrtc::ffiAudioDeviceModule(useStereoInput,useStereoOutput);
    return (int64_t)ffiADM;
}

int64_t ffi_newHardwareVideoEncoderFactory(){
    webrtc::ffiHardwareVideoEncoderFactory* ffiHVEF = new webrtc::ffiHardwareVideoEncoderFactory();
    return (int64_t)ffiHVEF;
}

int64_t ffi_newHardwareVideoDecoderFactory(){
    webrtc::ffiHardwareVideoDecoderFactory* ffiHVDF = new webrtc::ffiHardwareVideoDecoderFactory();
    return (int64_t)ffiHVDF;
}

int64_t ffi_newPeerConnectionFactory(int64_t ffiADM_int64 , int64_t ffiHVEF_int64 , int64_t ffiHVDF_int64) {
    webrtc::ffiAudioDeviceModule* ffiADM_ptr = (webrtc::ffiAudioDeviceModule*)ffiADM_int64;
    webrtc::ffiHardwareVideoEncoderFactory* ffiHVEF_ptr = (webrtc::ffiHardwareVideoEncoderFactory*)ffiHVEF_int64;
    webrtc::ffiHardwareVideoDecoderFactory* ffiHVDF_ptr = (webrtc::ffiHardwareVideoDecoderFactory*)ffiHVDF_int64;

    webrtc::ffiPeerConnectionFactory* ffiPCF = new webrtc::ffiPeerConnectionFactory(ffiADM_ptr,ffiHVEF_ptr,ffiHVDF_ptr);
    return (int64_t)ffiPCF;
}

int64_t ffi_createAudioSource(int64_t ffiPCF_int64 , ffiAudioOptions ffiao) {
    webrtc::ffiPeerConnectionFactory* ffiPCF_ptr = (webrtc::ffiPeerConnectionFactory*)ffiPCF_int64;
    return ffiPCF_ptr->ffiCreateAudioSource(ffiao);
}

int64_t ffi_createAudioTrack(int64_t ffiPCF_int64, char* ffi_audioId) {
    webrtc::ffiPeerConnectionFactory* ffiPCF_ptr = (webrtc::ffiPeerConnectionFactory*)ffiPCF_int64;
    std::string ffi_id_str(ffi_audioId);
    return ffiPCF_ptr->ffiCreateAudioTrack(ffi_id_str);
}

int64_t ffi_createVideoSource(int64_t ffiPCF_int64 , ffiCreateVideoSourceParameters fficvsp) {
    webrtc::ffiPeerConnectionFactory* ffiPCF_ptr = (webrtc::ffiPeerConnectionFactory*)ffiPCF_int64;
    return ffiPCF_ptr->ffiCreateVideoSource(fficvsp);
} 

int64_t ffi_createVideoTrack(int64_t ffiPCF_int64 , char* ffi_videoId) {
    webrtc::ffiPeerConnectionFactory* ffiPCF_ptr = (webrtc::ffiPeerConnectionFactory*)ffiPCF_int64;
    std::string ffi_videoId_str(ffi_videoId);
    int64_t ffiMST = ffiPCF_ptr->ffiCreateVideoTrack(ffi_videoId_str);
    return ffiMST;
}

void ffi_StopAecDump(int64_t ffiPCF_int64) {
    webrtc::ffiPeerConnectionFactory* ffiPCF_ptr = (webrtc::ffiPeerConnectionFactory*)ffiPCF_int64;
    ffiPCF_ptr->StopAecDump();
}

void ffi_SetSurfaceId(int64_t surfaceId) {
    PluginManager::SetSurfaceId(surfaceId);
}

void ffi_ChangeSurface(int64_t surfaceId, double width, double height) {
    PluginManager::ChangeSurface(surfaceId, width, height);
}

void ffi_DrawPattern(int64_t surfaceId) {
    PluginManager::DrawPattern(surfaceId);
}
void ffi_ChangeColor(int64_t surfaceId) {
    PluginManager::ChangeColor(surfaceId);
}

void ffi_DestroySurface(int64_t surfaceId) {
    PluginManager::DestroySurface(surfaceId);
}

bool ffi_GetXComponentHasDraw(int64_t surfaceId) {
    return PluginManager::GetXComponentHasDraw(surfaceId);
}

bool ffi_XComponentHasChangeColor(int64_t surfaceId) {
    return PluginManager::GetXComponentHasChangeColor(surfaceId);
}
