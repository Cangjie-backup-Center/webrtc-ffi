#include "ffi.h"
#include "ffi_data_channel.h"

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


/*
TODO 
export interface PeerConnectionFactoryOptions {
  adm?: AudioDeviceModule;
  videoEncoderFactory?: VideoEncoderFactory;
  videoDecoderFactory?: VideoDecoderFactory;
  audioProcessing?: AudioProcessing;  // TODO 待确认需要如何传递参数
}
*/
int64_t ffi_newPeerConnectionFactory(int64_t ffiADM_int64 , int64_t ffiHVEF_int64 , int64_t ffiHVDF_int64) {  // TODO 
    webrtc::ffiAudioDeviceModule* ffiADM_ptr = (webrtc::ffiAudioDeviceModule*)ffiADM_int64;
    webrtc::ffiHardwareVideoEncoderFactory* ffiHVEF_ptr = (webrtc::ffiHardwareVideoEncoderFactory*)ffiHVEF_int64;
    webrtc::ffiHardwareVideoDecoderFactory* ffiHVDF_ptr = (webrtc::ffiHardwareVideoDecoderFactory*)ffiHVDF_int64;

    webrtc::ffiPeerConnectionFactory* ffiPCF = new webrtc::ffiPeerConnectionFactory(ffiADM_ptr,ffiHVEF_ptr,ffiHVDF_ptr);
    return (int64_t)ffiPCF;
}

int64_t ffi_createAudioSource(int64_t ffiPCF_int64 , FFIAudioOptions ffiao) {
    webrtc::ffiPeerConnectionFactory* ffiPCF_ptr = (webrtc::ffiPeerConnectionFactory*)ffiPCF_int64;
    return ffiPCF_ptr->ffiCreateAudioSource(ffiao);
}

int64_t ffi_createAudioTrack(int64_t ffiPCF_int64, char* ffi_audioId) {
    webrtc::ffiPeerConnectionFactory* ffiPCF_ptr = (webrtc::ffiPeerConnectionFactory*)ffiPCF_int64;
    std::string ffi_id_str(ffi_audioId);
    return ffiPCF_ptr->ffiCreateAudioTrack(ffi_id_str);
}

int64_t ffi_createVideoSource(int64_t ffiPCF_int64 , FFICreateVideoSourceParameters fficvsp) {
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

void peerConnection_set_class_key(int64_t cpp_ptr, int64_t classKey){
    ((webrtc::ffiPeerConnection*)cpp_ptr)->SetCJClassID(classKey);
}

void peerConnection_set_cj_func_call_OnDataChannel_(int64_t cpp_ptr, void (*pe)(int64_t id, int64_t ptr)) {
    ((webrtc::ffiPeerConnection*)cpp_ptr)->SetOnDataChannel(pe);
}

void peerConnection_set_cj_func_call_OnSignalingChange_(int64_t cpp_ptr, void (*pe)(int64_t id, CJ_Event ptr)){
    ((webrtc::ffiPeerConnection*)cpp_ptr)->SetOnSignalingChange(pe);
}
void peerConnection_set_cj_func_call_OnIceCandidateError_(int64_t cpp_ptr, void (*pe)(int64_t id, CJ_RTCPeerConnectionIceErrorEvent ptr)){
    ((webrtc::ffiPeerConnection*)cpp_ptr)->SetOnIceCandidateError(pe);
}
void peerConnection_set_cj_func_call_onTrack_(int64_t cpp_ptr, void (*pe)(int64_t id, CJ_RTCTrackEvent ptr)){
    ((webrtc::ffiPeerConnection*)cpp_ptr)->SetOnTrack(pe);
}
void peerConnection_set_cj_func_call_SetOnConnectionChange_(int64_t cpp_ptr, void (*pe)(int64_t id, CJ_Event ptr)) {
    ((webrtc::ffiPeerConnection*)cpp_ptr)->SetOnConnectionChange(pe);
}
void peerConnection_set_cj_func_call_SetOnRenegotiationNeeded_(int64_t cpp_ptr, void (*pe)(int64_t id, CJ_Event ptr)){
    ((webrtc::ffiPeerConnection*)cpp_ptr)->SetOnRenegotiationNeeded(pe);
}
void peerConnection_set_cj_func_call_SetOnStandardizedIceConnectionChange_(int64_t cpp_ptr, void (*pe)(int64_t id, CJ_Event ptr)){
    ((webrtc::ffiPeerConnection*)cpp_ptr)->SetOnStandardizedIceConnectionChange(pe);
}
void peerConnection_set_cj_func_call_SetOnIceGatheringChange_(int64_t cpp_ptr, void (*pe)(int64_t id, CJ_Event ptr)){
    ((webrtc::ffiPeerConnection*)cpp_ptr)->SetOnIceGatheringChange(pe);
}
void peerConnection_set_cj_func_call_SetOnIceCandidate_(int64_t cpp_ptr, void (*pe)(int64_t id, CJ_OnIceCandidateEvent ptr)){
    ((webrtc::ffiPeerConnection*)cpp_ptr)->SetOnIceCandidate(pe);
}
void peerConnection_set_cj_func_call_SetCallBackCreateOffer_(int64_t cpp_ptr, void (*pe)(int64_t id, bool isSuccess, CJ_RTCSessionDescription ptr, const char* msg)){
    ((webrtc::ffiPeerConnection*)cpp_ptr)->SetCallBackCreateOffer(pe);
}
void peerConnection_set_cj_func_call_SetCallBackCreateAnswer_(int64_t cpp_ptr, void (*pe)(int64_t id, bool isSuccess, CJ_RTCSessionDescription ptr, const char* msg)){
    ((webrtc::ffiPeerConnection*)cpp_ptr)->SetCallBackCreateAnswer(pe);
}
bool peerConnection_GetCanTrickleIceCandidates(int64_t cpp_ptr) {
    return ((webrtc::ffiPeerConnection*)cpp_ptr)->GetCanTrickleIceCandidates();
}
int64_t peerConnection_GetSignalingState(int64_t cpp_ptr) {
    return (int64_t)((webrtc::ffiPeerConnection*)cpp_ptr)->GetSignalingState();
}
int64_t peerConnection_GetIceGatheringState(int64_t cpp_ptr){
    return (int64_t)((webrtc::ffiPeerConnection*)cpp_ptr)->GetIceGatheringState();
}
int64_t peerConnection_GetIceConnectionState(int64_t cpp_ptr){
    return (int64_t)((webrtc::ffiPeerConnection*)cpp_ptr)->GetIceConnectionState();
}
int64_t peerConnection_GetConnectionState(int64_t cpp_ptr) {
    return (int64_t)((webrtc::ffiPeerConnection*)cpp_ptr)->GetConnectionState();
}

CJ_RTCSessionDescription peerConnection_GetLocalDescription(int64_t cpp_ptr) {
    return ((webrtc::ffiPeerConnection*)cpp_ptr)->GetLocalDescription();
}
CJ_RTCSessionDescription peerConnection_GetRemoteDescription(int64_t cpp_ptr) {
    return ((webrtc::ffiPeerConnection*)cpp_ptr)->GetRemoteDescription();
}
CJ_RTCSessionDescription peerConnection_GetCurrentLocalDescription(int64_t cpp_ptr) {
    return ((webrtc::ffiPeerConnection*)cpp_ptr)->GetCurrentLocalDescription();
}
CJ_RTCSessionDescription peerConnection_GetCurrentRemoteDescription(int64_t cpp_ptr) {
    return ((webrtc::ffiPeerConnection*)cpp_ptr)->GetCurrentRemoteDescription();
}
CJ_RTCSessionDescription peerConnection_GetPendingLocalDescription(int64_t cpp_ptr) {
    return ((webrtc::ffiPeerConnection*)cpp_ptr)->GetPendingLocalDescription();
}
CJ_RTCSessionDescription peerConnection_GetPendingRemoteDescription(int64_t cpp_ptr) {
    return ((webrtc::ffiPeerConnection*)cpp_ptr)->GetPendingRemoteDescription();
}
int64_t peerConnection_GetSctp(int64_t cpp_ptr){
    return ((webrtc::ffiPeerConnection*)cpp_ptr)->GetSctp();
}

int64_t peerConnection_static_GenerateCertificate(char* keyname){
    return webrtc::ffiPeerConnection::GenerateCertificate(keyname);
}

int64_t peerConnection_addTrack(int64_t cpp_ptr, int64_t ffiMST_ptr, CJ_ArrayMediaStream streamVec){
    std::vector<webrtc::FFIMediaStream*> arr;
    for (int i = 0; i < streamVec.size; i++) {
        arr.push_back((webrtc::FFIMediaStream*)streamVec.ptr[i]);
    }
    
    return ((webrtc::ffiPeerConnection*)cpp_ptr)->addTrack((webrtc::ffiMediaStreamTrack*)ffiMST_ptr, arr);
}

void peerConnection_setLocalDescription(int64_t cpp_ptr, CJ_RTCSessionDescription description, void (*pe)(int64_t cj_id, CJ_ErrorMessage msg)){
    ((webrtc::ffiPeerConnection*)cpp_ptr)->setLocalDescription(description, pe);
}

void peerConnection_setRemoteDescription(int64_t cpp_ptr, CJ_RTCSessionDescription description, void (*pe)(int64_t cj_id, CJ_ErrorMessage msg)){
    ((webrtc::ffiPeerConnection*)cpp_ptr)->setRemoteDescription(description, pe);
}

CJ_FFICreateSdpObserver_result peerConnection_createOffer(int64_t cpp_ptr, bool iceRestart){
    return ((webrtc::ffiPeerConnection*)cpp_ptr)->createOffer(iceRestart);
}

CJ_FFICreateSdpObserver_result peerConnection_createAnswer(int64_t cpp_ptr){
    return ((webrtc::ffiPeerConnection*)cpp_ptr)->createAnswer();
}

int64_t peerConnection_createDataChannel(int64_t cpp_ptr, char* label, CJ_RTCDataChannelInit dataChannelDict){
    return ((webrtc::ffiPeerConnection*)cpp_ptr)->createDataChannel(label, dataChannelDict);
}

void peerConnection_addIceCandidate(int64_t cpp_ptr, CJ_RTCIceCandidateInit candidate){
    ((webrtc::ffiPeerConnection*)cpp_ptr)->addIceCandidate(candidate);
}

void peerConnection_SetAddIceCandidate(int64_t cpp_ptr, void (*pe)(int64_t id,const  char* msg)){
    ((webrtc::ffiPeerConnection*)cpp_ptr)->SetAddIceCandidate(pe);
}

int64_t* peerConnection_getSenders(int64_t cpp_ptr){
    return ((webrtc::ffiPeerConnection*)cpp_ptr)->getSenders();
}

int64_t* peerConnection_getReceivers(int64_t cpp_ptr){
    return ((webrtc::ffiPeerConnection*)cpp_ptr)->getReceivers();
}

int64_t* peerConnection_getTransceivers(int64_t cpp_ptr){
    return ((webrtc::ffiPeerConnection*)cpp_ptr)->getTransceivers();
}

void peerConnection_restartIce(int64_t cpp_ptr){
    ((webrtc::ffiPeerConnection*)cpp_ptr)->restartIce();
}

void peerConnection_setConfiguration(int64_t cpp_ptr, CJ_RTCConfiguration configuration){
    ((webrtc::ffiPeerConnection*)cpp_ptr)->setConfiguration(configuration);
}

void peerConnection_close(int64_t cpp_ptr){
    ((webrtc::ffiPeerConnection*)cpp_ptr)->close();
}

void peerConnection_setAudioRecording(int64_t cpp_ptr, bool recording){
    ((webrtc::ffiPeerConnection*)cpp_ptr)->setAudioRecording(recording);
}

void peerConnection_setAudioPlayout(int64_t cpp_ptr, bool playout){
    ((webrtc::ffiPeerConnection*)cpp_ptr)->setAudioPlayout(playout);
}

// dataConnection
void dataConnection_set_class_key(int64_t cpp_ptr, int64_t classKey){
    ((webrtc::ffiDataChannelObserverTemp*)cpp_ptr)->SetCJClassID(classKey);
}
void dataConnection_set_cj_func_Onopen_(int64_t cpp_ptr, void (*pe)(int64_t id, CJ_Event event)){
    ((webrtc::ffiDataChannelObserverTemp*)cpp_ptr)->SetOnopen(pe);
}
void dataConnection_set_cj_func_Onclosing_(int64_t cpp_ptr, void (*pe)(int64_t id, CJ_Event event)){
    ((webrtc::ffiDataChannelObserverTemp*)cpp_ptr)->SetOnclosing(pe);
}
void dataConnection_set_cj_func_Onclose_(int64_t cpp_ptr, void (*pe)(int64_t id, CJ_Event event)){
    ((webrtc::ffiDataChannelObserverTemp*)cpp_ptr)->SetOnclose(pe);
}
void dataConnection_set_cj_func_Onmessage_(int64_t cpp_ptr, void (*pe)(int64_t id, CJ_MessageEvent event)){
    ((webrtc::ffiDataChannelObserverTemp*)cpp_ptr)->SetOnMessage(pe);
}
char * dataConnection_get_label_(int64_t cpp_ptr) {
    return ((webrtc::ffiDataChannelObserverTemp*)cpp_ptr)->GetLabel().data();
}
bool dataConnection_get_ordered_(int64_t cpp_ptr) {
    return ((webrtc::ffiDataChannelObserverTemp*)cpp_ptr)->GetOrdered();
}
int64_t dataConnection_get_maxPacketLifeTime_(int64_t cpp_ptr){
    return ((webrtc::ffiDataChannelObserverTemp*)cpp_ptr)->GetMaxPacketLifeTime();
}
int64_t dataConnection_get_maxRetransmits_(int64_t cpp_ptr) {
    return ((webrtc::ffiDataChannelObserverTemp*)cpp_ptr)->GetMaxRetransmits();
}
char* dataConnection_get_protocol_(int64_t cpp_ptr) {
    return ((webrtc::ffiDataChannelObserverTemp*)cpp_ptr)->GetProtocol().data();
}
bool dataConnection_get_negotiated_(int64_t cpp_ptr) {
    return ((webrtc::ffiDataChannelObserverTemp*)cpp_ptr)->GetNegotiated();
}
int64_t dataConnection_get_id_(int64_t cpp_ptr){
    return ((webrtc::ffiDataChannelObserverTemp*)cpp_ptr)->GetId();
}
int64_t dataConnection_get_readyState_(int64_t cpp_ptr){
    return (int64_t)((webrtc::ffiDataChannelObserverTemp*)cpp_ptr)->GetReadyState();
}
int64_t dataConnection_get_bufferedAmount_(int64_t cpp_ptr){
    return ((webrtc::ffiDataChannelObserverTemp*)cpp_ptr)->GetBufferedAmount();
}
int64_t dataConnection_get_bufferedAmountLowThreshold_(int64_t cpp_ptr){
    return ((webrtc::ffiDataChannelObserverTemp*)cpp_ptr)->GetBufferedAmountLowThreshold();
}
void dataConnection_set_bufferedAmountLowThreshold_(int64_t cpp_ptr, int64_t value){
    ((webrtc::ffiDataChannelObserverTemp*)cpp_ptr)->SetBufferedAmountLowThreshold(value);
}
int64_t dataConnection_get_binaryType_(int64_t cpp_ptr){
    return (int64_t)((webrtc::ffiDataChannelObserverTemp*)cpp_ptr)->GetBinaryType();
    
}
void dataConnection_set_binaryType_(int64_t cpp_ptr, int64_t value){
    return ((webrtc::ffiDataChannelObserverTemp*)cpp_ptr)->SetBinaryType((enum FFIBinaryType)value);
}

void dataConnection_Send_String(int64_t cpp_ptr, char* data){
    ((webrtc::ffiDataChannelObserverTemp*)cpp_ptr)->Send(data);
}
void dataConnection_Send_binary(int64_t cpp_ptr, uint8_t* data, int64_t size){
    ((webrtc::ffiDataChannelObserverTemp*)cpp_ptr)->Send(data, size);
}
void dataConnection_Close(int64_t cpp_ptr) {
    ((webrtc::ffiDataChannelObserverTemp*)cpp_ptr)->Close();
}

void RTCDataChannel_CPP_FREE(int64_t cpp_ptr){
    delete (webrtc::ffiDataChannelObserverTemp*)cpp_ptr;  //释放RTCDataChannel的C侧资源
}

void SctpTransport_set_class_key(int64_t cpp_ptr, int64_t classKey) {
    ((webrtc::ffiSctpTransport*)cpp_ptr)->SetCJClassID(classKey);
}

// ffiDtmfSender
void ffiDtmfSender_set_class_key(int64_t cpp_ptr, int64_t classKey) {
    ((webrtc::ffiDtmfSender*)cpp_ptr)->SetCJClassID(classKey);
}
bool ffiDtmfSender_GetCanInsertDTMF(int64_t cpp_ptr) {
    return ((webrtc::ffiDtmfSender*)cpp_ptr)->GetCanInsertDTMF();
} 
const char* ffiDtmfSender_GetToneBuffer(int64_t cpp_ptr){
    return ((webrtc::ffiDtmfSender*)cpp_ptr)->GetToneBuffer();
}
bool ffiDtmfSender_InsertDTMF(int64_t cpp_ptr, const char* tones, int64_t duration, int64_t interToneGap) {
    return ((webrtc::ffiDtmfSender*)cpp_ptr)->InsertDTMF(tones, duration,interToneGap );
} 
void ffiDtmfSender_set_OnToneChange(int64_t cpp_ptr, void (*pe)(int64_t id, const char* tone) ) {
    ((webrtc::ffiDtmfSender*)cpp_ptr)->cj_func_call_OnToneChange_ = pe;
}   


