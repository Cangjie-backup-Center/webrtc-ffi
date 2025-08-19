//
// Created on 2025/8/6.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef WEBRTC4CJ_FFI_DEFINE_STRUCT_H
#define WEBRTC4CJ_FFI_DEFINE_STRUCT_H

#include <cstdint>

enum class FFIRTCErrorDetailType {
    DATA_CHANNEL_FAILURE,
    DTLS_FAILURE,
    FINGERPRINT_FAILURE,
    HARDWARE_ENCODER_ERROR,
    HARDWARE_ENCODER_NOT_AVAILABLE,
    SCTP_FAILURE,
    SDP_SYNTAX_ERROR
};
enum class FFIRTCIceProtocol { TCP, UDP };
enum class FFIRTCIceCandidateType { HOST, PRFLX, RELAY, SRFLX };
enum class FFIRTCIceTcpCandidateType { ACTIVE, PASSIVE, SO };
enum class FFIRTCIceComponent { RTP, RTCP };
enum class FFIRTCIceGathererState { COMPLETE, GATHERING, NEW };
enum class FFIRTCIceTransportState { CHECKING, CLOSED, COMPLETED, CONNECTED, DISCONNECTED, FAILED, NEW };
enum class FFIRTCIceRole { UNKNOWN, CONTROLLING, CONTROLLED };
enum class FFIRTCSdpType { OFFER, ANSWER, PRANSWER, ROLLBACK };
enum class FFIBinaryType { BLOB, ARRAYBUFFER };
enum class FFIDataChannelState { CLOSED, CLOSING, CONNECTING, OPEN };
enum class FFIRTCDtlsTransportState { NEW, CONNECTING, CONNECTED, CLOSED, FAILED };
enum class FFIRTCIceGatheringState { NEW, GATHERING, COMPLETE };
enum class FFIRTCIceConnectionState { CHECKING, CLOSED, COMPLETED, CONNECTED, DISCONNECTED, FAILED, NEW };
enum class FFIRTCSignalingState {
    CLOSED,
    HAVE_LOCAL_OFFER,
    HAVE_LOCAL_PRANSWER,
    HAVE_REMOTE_OFFER,
    HAVE_REMOTE_PRANSWER,
    STABLE
};
enum class FFIRTCPeerConnectionState { CLOSED, CONNECTED, CONNECTING, DISCONNECTED, FAILED, NEW };
enum class FFIRTCBundlePolicy { BALANCED, MAX_BUNDLE, MAX_COMPAT };
enum class FFIRTCRtcpMuxPolicy { REQUIRE };
enum class FFIRTCIceTransportPolicy { ALL, RELAY };
enum class FFIDegradationPreference { BALANCED, MAINTAIN_FRAMERATE, MAINTAIN_RESOLUTION };
// enum clasFFIs RTCPriorityType { HIGH, LOW, MEDIUM, VERY_LOW};
enum class FFIRTCRtpTransceiverDirection { INACTIVE, RECVONLY, SENDONLY, SENDRECV, STOPPED };
enum class FFIRTCSctpTransportState { CONNECTING, CONNECTED, CLOSED };
enum class FFIRTCStatsType {
    CANDIDATE_PAIR,
    CERTIFICATE,
    CODEC,
    DATA_CHANNEL,
    INBOUND_RTP,
    LOCAL_CANDIDATE,
    MEDIA_PLAYOUT,
    MEDIA_SOURCE,
    OUTBOUND_RTP,
    PEER_CONNECTION,
    REMOTE_CANDIDATE,
    REMOTE_INBOUND_RTP,
    REMOTE_OUTBOUND_RTP,
    TRANSPORT
};
enum class FFIrtcstatsicecandidatepairstate { FAILED, FROZEN, IN_PROGRESS, SUCCEEDED, WAITING };
enum class FFIMediaStreamTrackState { LIVE, ENDED };
enum class FFIMediaDeviceKind { AUDIOINPUT, AUDIOOUTPUT, VIDEOINPUT };
enum class FFIMediaSourceState { INITIALIZING, LIVE, ENDED, MUTED };
enum class FFIVideoFacingModeEnum { USER, ENVIRONMENT, LEFT, RIGHT };
enum class FFIVideoResizeModeEnum { NONE, CROP_AND_SCALE };
enum class FFIAudioErrorType { INIT, START_EXCEPTION, START_STATE_MISMATCH, GENERAL };
enum class FFIAudioState { START, STOP };
enum class FFIScreenCaptureMode { HOME_SCREEN, SPECIFIED_SCREEN, SPECIFIED_WINDOW };
enum class FFIScreenCaptureAudioFilterEnum { CURRENT_APP, NOTIFICATION };


typedef struct {
    double width;
    double height;
    double aspectRatio;
    double frameRate;
    char *facingMode;
    char *resizeMode;
    int64_t sampleRate;
    int64_t sampleSize;
    bool echoCancellation;
    bool autoGainControl;
    bool noiseSuppression;
    double latency;
    int64_t channelCount;
    char *deviceId;
    char *groupId;
    char *ohosScreenCaptureMode;
    int64_t ohosScreenCaptureDisplayId;
    char *ohosScreenCaptureMissionId;
    char *ohosScreenCaptureWindowFilter;
    char *ohosScreenCaptureAudioFilter;
    char *ohosScreenCaptureSkipPrivacyMode;
    bool ohosScreenCaptureAutoRotation;
} CJ_MediaTrackConstraintSet;


typedef struct {
    CJ_MediaTrackConstraintSet obj;
    bool boolean;
    bool isBool;
} CJ_TO_CPP_DisplayMediaStreamOptions;


typedef struct {
    const char *deviceId;
    const char *groupId;
    const char *label;
    const char *kind;
} CJ_EnumerateDevicesInfo;

typedef struct {
    const char *id;
    const char *kind;
    const char *readyState;
    bool enabled;
} CJ_ffiMediaStreamTrackJson;

typedef struct {
    const char *name;
    const bool isSupported;
} CJ_SupportedConstraints;

// c侧数组需要返回长度, 结构体
typedef struct {
    CJ_EnumerateDevicesInfo *ptr;
    int64_t size;
} CJ_ReturnEnumerateDevicesInfo;

typedef struct {
    int64_t *ptr;
    int64_t size;
} CJ_ReturnArray;

typedef struct {
    char **urls;
    int64_t urls_size;
    char *username;
    int64_t username_size;
    char *credential;
    int64_t credential_size;
} CJ_RTCIceServer;

typedef struct {
    int64_t expires;
    char *credential;
} CJ_RTCDtlsFingerprint;


typedef struct {
    int64_t expires;
//    CJ_RTCDtlsFingerprint* credential;
} CJ_RTCCertificate;

typedef struct {
    CJ_RTCIceServer *iceServers;
    int64_t iceServers_size;
    char *iceTransportPolicy;
    int64_t iceTransportPolicy_size;
    char *bundlePolicy;
    int64_t bundlePolicy_size;
    char *rtcpMuxPolicy;
    int64_t rtcpMuxPolicy_size;
    CJ_RTCCertificate *certificates;
    int64_t certificates_size;
    int64_t iceCandidatePoolSize;
} CJ_RTCConfiguration;

typedef struct {
    char *sdp;
    int64_t sdp_size;
    char *RTCSdpType;
    int64_t RTCSdpType_size;
    bool undefined = true; // 如果 true , 其他值就无效了
} CJ_RTCSessionDescription;

//typedef struct {
//    int64_t maxChannels;
//    int64_t maxMessageSize;
//    char *RTCSctpTransportState;
//    int64_t RTCSctpTransportState_size;
//    int64_t RTCDtlsTransport_ptr; // rtc::scoped_refptr<SctpTransportInterface>
//    bool undefined = true;        // 如果 true , 其他值就无效了
//} cj_RTCSctpTransport;

typedef struct {
    int64_t channel; // ffiDataChannelObserverTemp 指针地址
} CJ_RTCDataChannelEvent;

typedef struct {
    const char *type;
} CJ_Event;

typedef struct {
    const char *type;
    const char *candidate;
} CJ_RTCPeerConnectionIceEvent;

typedef struct {
    const char *type;
    int64_t *streams;
    int64_t streams_size;
    int64_t MediaStreamTrack_ptr; // ffiMediaStreamTrack
    int64_t RtpReceiver_ptr;      // ffiRtpReceiver
    int64_t RtpTransceiver_ptr;   // ffiRtpTransceiver
} CJ_RTCTrackEvent;

typedef struct {
    const char *type;
    const char *address;
    int64_t port;
    const char *url;
    int64_t errorCode;
    const char *errorText;
} CJ_RTCPeerConnectionIceErrorEvent;

typedef struct {
    const char *type;
    const uint8_t *data_arr;
    int64_t data_arr_size;
    const bool binary;
    const char *data_str;
} CJ_MessageEvent;

typedef struct {
    int32_t sdpMLineIndex;
    char* sdpMid;
    char* candidate;
    char* foundation;
    char* component;
    int32_t priority;
    char* address;
    char* protocol;
    uint16_t port;
    char* tcpType;
    char* relatedAddress;
    uint16_t relatedPort;
    char* usernameFragment;
    char* type;
    char* adapterType;
    char* serverUrl;
} CJToCppCandidateObject;

typedef struct {
    const char* type;
    CJToCppCandidateObject* candidate;
} CJ_OnIceCandidateEvent;

typedef struct {
    bool active;
    int64_t maxBitrate;
    int64_t maxFramerate;
    int64_t scaleResolutionDownBy;
} CJ_RTCRtpEncodingParameters;

typedef struct {
    CJ_RTCRtpEncodingParameters* encodings;
    int64_t encodings_size;
    char* transactionId;
} CJ_RTCRtpSendParameters;

typedef struct {
    char* mimeType;
    int64_t clockRate;
    int64_t channels;
    char* sdpFmtpLine;
} CJ_RTCRtpCodec;


#endif // WEBRTC4CJ_FFI_DEFINE_STRUCT_H
