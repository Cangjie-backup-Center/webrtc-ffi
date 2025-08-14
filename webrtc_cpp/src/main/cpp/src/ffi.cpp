#include "ffi.h"

#include <cstdint>

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

void ffi_SetDefault(int64_t ffiPCF_int64) {
    webrtc::ffiPeerConnectionFactory* ffiPCF_ptr = (webrtc::ffiPeerConnectionFactory*)ffiPCF_int64;
    webrtc::ffiPeerConnectionFactory::SetDefault(ffiPCF_ptr);
}

bool ffi_StartAecDump(int64_t ffiPCF_int64, int fd, int max_size_bytes) {
    webrtc::ffiPeerConnectionFactory* ffiPCF_ptr = (webrtc::ffiPeerConnectionFactory*)ffiPCF_int64;
    return ffiPCF_ptr->StartAecDump(fd, max_size_bytes);
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


int64_t ffi_webrtc_mediaDevices_create() {
    webrtc::FFIMediaDevices* s = new webrtc::FFIMediaDevices();
    return (int64_t)s;
}

void ffi_webrtc_mediaDevices_getDisplayMedia(int64_t mediaDevicesPtr, 
                                                  CJ_TO_CPP_DisplayMediaStreamOptions video, 
                                                  CJ_TO_CPP_DisplayMediaStreamOptions audio, 
                                                  CJ_TO_CPP_DisplayMediaStreamOptions systemAudio, 
                                                    int64_t id, void (*pe)(int64_t that, int64_t localVideoTrack)){
    ((webrtc::FFIMediaDevices*)mediaDevicesPtr)->getDisplayMedia(&video, &audio, &systemAudio, id, pe);
}

void ffi_webrtc_mediaDevices_getUserMedia(int64_t mediaDevicesPtr, 
                                           CJ_TO_CPP_DisplayMediaStreamOptions video, 
                                           CJ_TO_CPP_DisplayMediaStreamOptions audio, 
                                            int64_t id, void (*pe)(int64_t that, int64_t localVideoTrack)){
    ((webrtc::FFIMediaDevices*)mediaDevicesPtr)->getUserMedia(&video, &audio, id, pe);
}

CJ_ReturnEnumerateDevicesInfo ffi_webrtc_mediaDevices_enumerateDevices(int64_t mediaDevicesPtr){
    return ((webrtc::FFIMediaDevices*)mediaDevicesPtr)->enumerateDevices();
}

int64_t ffi_webrtc_mediaDevices_getSupportedConstraints(int64_t mediaDevicesPtr){
    return ((webrtc::FFIMediaDevices*)mediaDevicesPtr)->getSupportedConstraints();
}

void ffi_webrtc_FFIMediaStream_AddTrack(int64_t FFIMediaStreamPtr, int64_t mst){
    ((webrtc::FFIMediaStream*)FFIMediaStreamPtr)->AddTrack(mst);
}

void ffi_webrtc_FFIMediaStream_RemoveTrack(int64_t FFIMediaStreamPtr, int64_t mst){
    ((webrtc::FFIMediaStream*)FFIMediaStreamPtr)->RemoveTrack(mst);
}

int64_t ffi_webrtc_FFIMediaStream_GetTrackById(int64_t FFIMediaStreamPtr, char* trackId){
    return ((webrtc::FFIMediaStream*)FFIMediaStreamPtr)->GetTrackById(trackId);
}

CJ_ReturnArray ffi_webrtc_FFIMediaStream_GetTracks(int64_t FFIMediaStreamPtr){
    return ((webrtc::FFIMediaStream*)FFIMediaStreamPtr)->GetTracks();
}

CJ_ReturnArray ffi_webrtc_FFIMediaStream_GetAudioTracks(int64_t FFIMediaStreamPtr){
    return ((webrtc::FFIMediaStream*)FFIMediaStreamPtr)->GetAudioTracks();
}

CJ_ReturnArray ffi_webrtc_FFIMediaStream_GetVideoTracks(int64_t FFIMediaStreamPtr){
    return ((webrtc::FFIMediaStream*)FFIMediaStreamPtr)->GetVideoTracks();
}

CJ_ffiMediaStreamTrackJson ffi_webrtc_ffiMediaStreamTrack_ToJson(int64_t ffiMediaStreamTrackPtr){
    return ((webrtc::ffiMediaStreamTrack*)ffiMediaStreamTrackPtr)->ToJson();
}

int64_t ffi_webrtc_ffiMediaStreamTrack_GetSource(int64_t ffiMediaStreamTrackPtr){
    return ((webrtc::ffiMediaStreamTrack*)ffiMediaStreamTrackPtr)->GetSource();
}


void set_cj_func_call_OnDataChannel_(int64_t cpp_ptr, void (*pe)(int64_t id, int64_t ptr)) {
    ((webrtc::ffiPeerConnection*)cpp_ptr)->SetOnDataChannel(pe);
    return;
}

void set_peerConnection_class_key(int64_t cpp_ptr, int64_t classKey){
    ((webrtc::ffiPeerConnection*)cpp_ptr)->cj_class_key = classKey;
}
