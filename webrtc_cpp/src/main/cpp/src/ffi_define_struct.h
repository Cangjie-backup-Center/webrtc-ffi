//
// Created on 2025/8/6.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef WEBRTC4CJ_FFI_DEFINE_STRUCT_H
#define WEBRTC4CJ_FFI_DEFINE_STRUCT_H

#include <cstdint>

enum class FFIRTCSignalingState {CLOSED, HAVE_LOCAL_OFFER, HAVE_LOCAL_PRANSWER, HAVE_REMOTE_OFFER, HAVE_REMOTE_PRANSWER, STABLE};
enum class FFIRTCIceGatheringState {NEW, GATHERING, COMPLETE};
enum class FFIRTCIceConnectionState {CHECKING, CLOSED, COMPLETED, CONNECTED, DISCONNECTED, FAILED, NEW};
enum class FFIRTCPeerConnectionState {CLOSED, CONNECTED, CONNECTING, DISCONNECTED, FAILED, NEW};
enum class FFIDataChannelState {CLOSED, CLOSING, CONNECTING, OPEN};
enum class FFIBinaryType {BLOB, ARRAYBUFFER};

typedef struct {
    double width;
    double height;
    double aspectRatio;
    double frameRate;
    char* facingMode;
    char* resizeMode;
    int64_t sampleRate;
    int64_t sampleSize;
    bool echoCancellation;
    bool autoGainControl;
    bool noiseSuppression;
    double latency;
    int64_t channelCount;
    char* deviceId;
    char* groupId;
    char* ohosScreenCaptureMode;
    int64_t ohosScreenCaptureDisplayId;
    char* ohosScreenCaptureMissionId;
    char* ohosScreenCaptureWindowFilter;
    char* ohosScreenCaptureAudioFilter;
    char* ohosScreenCaptureSkipPrivacyMode;
    bool ohosScreenCaptureAutoRotation;
} CJ_MediaTrackConstraintSet;


typedef struct
{
    CJ_MediaTrackConstraintSet obj;
    bool boolean;
    bool isBool;
} CJ_TO_CPP_DisplayMediaStreamOptions;


typedef struct {
    const char* deviceId;
    const char* groupId;
    const char* label;
    const char* kind;
} CJ_EnumerateDevicesInfo;

typedef struct {
    const char* id;
    const char* kind;
    const char* readyState;
    bool enabled;
} CJ_ffiMediaStreamTrackJson;

typedef struct {
    const char* name;
    const bool isSupported;
} CJ_SupportedConstraints;

// c侧数组需要返回长度, 结构体
typedef struct {
    CJ_EnumerateDevicesInfo* ptr;
    int64_t size;
} CJ_ReturnEnumerateDevicesInfo;

typedef struct {
    int64_t* ptr;
    int64_t size;
} CJ_ReturnArray;

typedef struct {
    char** urls;
    int64_t urls_size;
    char* username;
    int64_t username_size;
    char* credential;
    int64_t credential_size;
} CJ_RTCIceServer;

typedef struct {
    int64_t expires;
    char* credential;
} CJ_RTCDtlsFingerprint;


typedef struct {
    int64_t expires;
//    CJ_RTCDtlsFingerprint* credential;
} CJ_RTCCertificate;

typedef struct {
    CJ_RTCIceServer* iceServers;
    int64_t iceServers_size;
    char* iceTransportPolicy;
    int64_t iceTransportPolicy_size;
    char* bundlePolicy;
    int64_t bundlePolicy_size;
    char* rtcpMuxPolicy;
    int64_t rtcpMuxPolicy_size;
    CJ_RTCCertificate* certificates;
    int64_t certificates_size;
    int64_t iceCandidatePoolSize;
} CJ_RTCConfiguration;

typedef struct {
    char* sdp;
    int64_t sdp_size;
    char* RTCSdpType;
    int64_t RTCSdpType_size;
    bool undefined = true;  // 如果 true , 其他值就无效了
} cj_RTCSessionDescription;

typedef struct {
    int64_t maxChannels;
    int64_t maxMessageSize;
    char* RTCSctpTransportState;
    int64_t RTCSctpTransportState_size;
    int64_t RTCDtlsTransport_ptr; // rtc::scoped_refptr<SctpTransportInterface>
    bool undefined = true;  // 如果 true , 其他值就无效了
} cj_RTCSctpTransport;

#endif //WEBRTC4CJ_FFI_DEFINE_STRUCT_H
